#include "stdafx.h"
#include "Macro.h"

TEST(Macro, Redefinition)
{
	CLASS_DEFINITION(Test);
	//CLASS_DEFINITION(Test); // �ߺ� �����ϸ� ������ ������.
}

TEST(Macro, StatckCheck)
{
	STATIC_CHECK(sizeof(DWORD) <= sizeof(int), logical_test); //������ �˻� �׽�Ʈ. typedef �� �ڷ����鿡 ���� �˻縦 �̸� �س����� ���� ���̴�.
}

TEST(Macro, Assert)
{
	ASSERT_MSG(0 < 1, "0 < 1 is true."); //ASSERT�� MSG �����ؼ� �ߴ��� Ȯ����...
}

TEST(Macro, WhileLimit)
{
	int n = 0;
	while_limit(1000, n < 1000)
	{
		++n;
	}

	EXPECT_EQ(n, 1000);
}

enum TEST_ENUM
{
	TESTENUM_NONE = -1,
	TESTENUM_SUCCESS = 0,
};

TEST(Macro, ToString)
{
	EXPECT_TRUE(_tcscmp(_T("TESTENUM_SUCCESS"), TO_STRING(TESTENUM_SUCCESS)) == 0);
}
