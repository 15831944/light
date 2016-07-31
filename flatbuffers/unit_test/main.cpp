#include "stdafx.h"

#include "DirectoryUtil.h"

int _tmain(int argc, _TCHAR* argv[])
{
	light::Directory::set_current_directory(light::get_module_path()); // ���̳ʸ� ���� ��θ� ���� ���丮�� ��������.

	::testing::InitGoogleMock(&argc, argv);
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
