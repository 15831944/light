#pragma once

#include <list>
#include <fstream>

namespace light
{

/// ��ü ��ο��� ���ϸ� ������ �޼ҵ�
std::wstring get_file_name(const std::wstring& name);

/// ��ü ��ο��� Ȯ���ڸ� ������ �޼ҵ�
std::wstring get_file_ext(const std::wstring& name);

/// ���� �������� ���ϸ��� ������ �޼ҵ�
std::wstring get_module_name();

/// ��ü ��ο��� ���ϸ� ������ �޼ҵ� (Ȯ���� ����)
std::wstring get_file_name_without_ext(const std::wstring& name, const std::wstring& delimeters = L"\\");

/// ���� �������� ���Ͽ��� Ȯ���ڸ� ���� ������ �޼ҵ�
std::wstring get_module_name_without_ext();

class FileUtil
{
public:
	typedef std::list<std::wstring> LIST_FILENAME;

public:	
	static bool copy(const std::wstring& src, const std::wstring& dest);

	static bool move(const std::wstring& src, const std::wstring& dest);

	static bool rename(const std::wstring& name, const std::wstring& dest);

	static bool remove(const std::wstring& name);

	static bool close(FILE*& fp);

	static bool is_exist(const std::wstring& name);

	static FILE* open(const std::wstring& name, const WCHAR* mode);

    static void search(const std::wstring& filter, LIST_FILENAME& list);

    static void search(LIST_FILENAME& list, const std::wstring& Path, const std::wstring& filter = L"*.*");

	static bool create_time(const std::wstring& src, time_t& time);

	static bool modify_time(const std::wstring& src, time_t& time);

	static bool access_time(const std::wstring& src, time_t& time);

private:
	static bool stat(const std::wstring& src, struct _stat& buf);
};

} //namespace light
