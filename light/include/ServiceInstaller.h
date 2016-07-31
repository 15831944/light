#pragma once

#include "Str.h"
#include <Windows.h>

namespace light
{

/**
@brief ���� ��Ʈ�ѷ�
*/
class ServiceInstaller
{
public:
	/// ���� ��ġ �޼ҵ�
	static bool Install(const std::wstring& program_name, DWORD dwServiceStartType);

	/// ���� ���� �޼ҵ�
	static bool Uninstall(const std::wstring& program_name);
};

} //namespace light

///���� �ڵ� �������� ��ġ
#define SERVICE_INSTALL_AUTOSTART(szProgramName) light::ServiceInstaller::Install(szProgramName, SERVICE_BOOT_START | SERVICE_AUTO_START)

///���� ���� �������� ��ġ
#define SERVICE_INSTALL_MANUALSTART(szProgramName) light::ServiceInstaller::Install(szProgramName, SERVICE_DEMAND_START)

///���� ����
#define SERVICE_UNINSTALL(szProgramName) light::ServiceInstaller::Uninstall(szProgramName)
