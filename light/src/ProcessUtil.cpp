#include "light.h"
#include "ProcessUtil.h"

#include "DirectoryUtil.h"
#include "Util.h"

#include "FileUtil.h"

#include <ShellAPI.h>
#include <tlhelp32.h>   // CreateToolhelp32Snapshot() �� ����ϱ� ���� �ش�����  
#include <Psapi.h>

#pragma comment( lib, "psapi" )

#include "Mutex.h"

namespace light
{

Process::Process(const std::wstring& application_name, const LPSECURITY_ATTRIBUTES process_security_attributes, const LPSECURITY_ATTRIBUTES thread_security_attributes)
: m_process_security_attributes(process_security_attributes)
, m_thread_security_attributes(thread_security_attributes)
, m_process(INVALID_HANDLE_VALUE)
{
	std::wstring directory = Directory::get_current_directory() + L"\\" + get_path_without_file_name(application_name);

	WCHAR path[MAX_PATH] = {0, };
	BOOL ret = ::PathCanonicalize(path, directory.c_str());
	if( FALSE == ret )
	{
		LOG_ERROR(L"[%d]", GetLastError());
		return;
	}

	m_appication_path = path + get_file_name_without_path(application_name);
	m_current_directory = path;

	m_startup_info.cb = sizeof(m_startup_info);
}

BOOL Process::create(WCHAR* commandline)
{
	STRUCT_MEMSET_THIS<PROCESS_INFORMATION> ProcessInformation;
	if(m_process != INVALID_HANDLE_VALUE)
	{
		LOG_INFO(L"Already Opened Process. Path[%s] Directory[%d] Handle[%d]", m_appication_path.c_str(), m_current_directory.c_str(), m_process);
		return FALSE;
	}

	if( FALSE == ::CreateProcess(m_appication_path.c_str()
		, commandline
		, m_process_security_attributes.get()
		, m_thread_security_attributes.get()
		, FALSE
		, CREATE_NEW_CONSOLE /* dwCreationFlag values*/
		, NULL
		, m_current_directory.empty() ? NULL : m_current_directory.c_str()
		, &m_startup_info
		, &ProcessInformation))
	{
		m_process = INVALID_HANDLE_VALUE;
		LOG_ERROR(L"[%d]", GetLastError());
		return FALSE;
	}

	m_process = ProcessInformation.hProcess;

	DWORD dwRet = ::WaitForInputIdle(m_process, INFINITE);
	if(0 != dwRet && dwRet != WAIT_FAILED) //WAIT_FAILED�� �ܼ� ���α׷��� �� �׷���.
	{
		LOG_ERROR(L"[%u] [%d]", dwRet, GetLastError());
		release();
		return FALSE;
	}
	return TRUE;
}

BOOL Process::observe()
{
	if( INVALID_HANDLE_VALUE == m_process)
	{
		m_process = find_process(m_appication_path);
		if( INVALID_HANDLE_VALUE == m_process )
		{
			return FALSE;
		}
	}

	DWORD dwExitCode;
	if( FALSE == ::GetExitCodeProcess(m_process, &dwExitCode) )
	{
		return FALSE;
	}

	if( STILL_ACTIVE != dwExitCode)
	{
		release();
		return FALSE;
	}
	return TRUE;
}

Process::~Process()
{
}

void Process::release()
{
	if(m_process != INVALID_HANDLE_VALUE)
	{
		::WaitForSingleObject(m_process, INFINITE); 
		SAFE_CLOSE_HANDLE(m_process);
	}
}

bool Process::kill()
{
	return TRUE == TerminateProcess(m_process, 0) ? true : false;
}

bool Process::execute(const std::wstring& path, const std::wstring& param, const bool wait)
{
    std::wstring absolute_path = Directory::path_canonicalize(path);

	STRUCT_MEMSET_THIS<SHELLEXECUTEINFO> ShellExecuteInfo;
	ShellExecuteInfo.cbSize = sizeof(SHELLEXECUTEINFO); //cbSize�� �������־�� ��.
	ShellExecuteInfo.nShow = SW_SHOW; // ������ ���α׷��� ���������� ����.
	ShellExecuteInfo.fMask = SEE_MASK_NOCLOSEPROCESS;	
	ShellExecuteInfo.lpVerb = L"open"; // ���μ��� ���� ���
	ShellExecuteInfo.lpFile = L"cmd"; // cmd�� ���� ����

    std::wstring command = L"/C "; // ���� �Ϸ� �� ���Ḧ ���� �Ķ����
	command = command + get_file_name_without_path(absolute_path) + L" " + param;
	ShellExecuteInfo.lpParameters = command.c_str(); //�Ķ���͸� ���� ��ų ���α׷� ���ڿ��� �Ѱܾ� �Ѵ�.

    std::wstring dir = get_path_without_file_name(absolute_path);
	ShellExecuteInfo.lpDirectory = dir.c_str(); //����� ������ �Է�

	/// ���� ����
	if ( FALSE == ShellExecuteEx(&ShellExecuteInfo))
	{
		LOG_ERROR(L"ShellExecuteEx Failed [%d]", GetLastError());
		return false;
	}

    if (wait == false)
        return true;

	DWORD dwErrorCode = WAIT_FAILED;
	do //���α׷� ����ñ��� ����ϴ� �ڵ�
	{
		if ( FALSE == GetExitCodeProcess( ShellExecuteInfo.hProcess, &dwErrorCode ) )
		{
			LOG_ERROR(L"GetExitCodeProcess Failed [Err:%d] [Process:%d, %s]", GetLastError(), ShellExecuteInfo.hProcess, absolute_path.c_str());
			return false;
		}

		Sleep(1);
	} while( dwErrorCode == STILL_ACTIVE );
	return true;
}

HWND Process::pid_to_hwnd(DWORD dwPid)
{
	HWND tempHwnd = FindWindow(NULL,NULL); // �ֻ��� ������ �ڵ� ã��  
	while( tempHwnd != NULL )  
	{  
		if( GetParent(tempHwnd) == NULL ) // �ֻ��� �ڵ����� üũ, ��ư � �ڵ��� ���� �� �����Ƿ� �����ϱ� ����  
		{
			DWORD dwTempPid;
			::GetWindowThreadProcessId(tempHwnd, &dwTempPid);
			if( dwPid ==  dwTempPid)  
			{
				return tempHwnd;  
			}
		}

		tempHwnd = GetWindow(tempHwnd, GW_HWNDNEXT); // ���� ������ �ڵ� ã��  
	}  
	return NULL;  
}

HANDLE Process::find_process(const std::wstring& app_path)
{
	HANDLE   hProcess = NULL;
	PROCESSENTRY32 pe32 = {0};
	hProcess = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
	pe32.dwSize = sizeof( PROCESSENTRY32 );
	if( FALSE == Process32First( hProcess, &pe32 ) )
	{
		LOG_ERROR(L"Not find [%s]", app_path.c_str());
	}

	do 
	{
		if( 0 == pe32.th32ProcessID )
			continue;

		HANDLE hOpenProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
		if( NULL == hOpenProcess)
		{
			LOG_DEBUG(L"OpenProcess() Failed [%u] PID [%u]", GetLastError(), pe32.th32ProcessID);
			continue;
		}

		HMODULE hModule;
		DWORD dwBytesWritten = 0;
		WCHAR path[MAX_PATH] = L"";
		if( FALSE == EnumProcessModules(hOpenProcess, &hModule, sizeof(hModule), &dwBytesWritten))
		{
			DWORD err = GetLastError();
			if( ERROR_PARTIAL_COPY != err) //ERROR_PARTIAL_COPY�� �̹� ���μ����� ����� ����� �� �ִ�.
			{
				LOG_ERROR(L"%EnumProcessModules() Failed [%u] ProcessHandle [%p] PID [%u]", err, hOpenProcess, pe32.th32ProcessID);
			}
			CloseHandle(hOpenProcess);
			continue;
		}

		if( 0 == ::GetModuleFileNameEx(hOpenProcess, hModule, path, MAX_PATH) )
		{
			LOG_ERROR(L"GetModuleFileNameEx() Failed [%u] ProcessHandle [%p] ModuleHandle [%p]", GetLastError(), hOpenProcess, hModule);
			CloseHandle(hOpenProcess);
			continue;
		}

		if( _tcsicmp(app_path.c_str(), path) == 0 )
		{
			return hOpenProcess;
		}

		CloseHandle(hOpenProcess);
	} 
	while ( Process32Next( hProcess, &pe32 ) );
	CloseHandle (hProcess);
	return INVALID_HANDLE_VALUE;
}

HWND Process::find_process_by_name(const std::wstring& class_name, const std::wstring& window_name)
{
	static std::unique_ptr<Mutex> mutex(new Mutex(NULL, TRUE, window_name.c_str()));
	DWORD dwLastError = ::GetLastError();
	if(dwLastError != ERROR_ALREADY_EXISTS)
	{
		return NULL;
	}

	return ::FindWindow(class_name.c_str(), window_name.c_str());
}

} // namespace light
