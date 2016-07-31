#include "stdafx.h"

#include "DirectoryUtil.h"
#include "ProcessUtil.h"

int _tmain(int argc, _TCHAR* argv[])
{
	light::Directory::set_current_directory(light::get_module_path()); // ���̳ʸ� ���� ��θ� ���� ���丮�� ��������.

    light::Process::execute(L"..\\redis\\redis-server.exe", L"", false);

	::testing::InitGoogleMock(&argc, argv);
	::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();
    light::Process::execute(L"taskkill /F /IM redis-server.exe");
    return ret;
}
