#include "stdafx.h"

#include "Profiler.h"

#include <boost/bind.hpp>

#define VA_ARGS(STR, ...) STR,##__VA_ARGS__

class MockProfiler : public light::Profiler
{
public:
	MockProfiler(const TCHAR* name, const DWORD baseline)
		: light::Profiler(name, baseline)
	{
	}

	virtual ~MockProfiler()
	{
	}

public:
	const bool profile(const TCHAR* message, ...) const
	{
		return __super::profile( VA_ARGS(message) );
	}

	const double elapsed() const
	{
		return __super::elapsed();
	}

	const DWORD baseline() const
	{
		return m_baseline;
	}
};

TEST(Profiler, ProfileMethodTest)
{
 	MockProfiler profiler(_T("UnitTest"), 100); // ����ġ�� 100�̰�, 0~19 * 10 ��ŭ Sleep�ϴ� �뷫 50%�� ������ �����ؾ� ��
 	for(int n = 0; n < 10 ; ++n)
 	{
 		int nRand = rand() % 20;
 		Sleep(nRand);
 	}
 
 	if(profiler.baseline() <= profiler.elapsed() )
 	{
 		ASSERT_TRUE(profiler.profile(__FUNCTIONW__));
 	}
 	else
 	{
 		ASSERT_FALSE(profiler.profile(__FUNCTIONW__));
 	}
}

 
TEST(Profiler, HaveToSuccessTest) // �ݵ�� ���� �ؾ� �Ǵ� �׽�Ʈ
{
 	MockProfiler profiler(_T("HaveToSuccessTest"), 200); // ����ġ 200. 300��ŭ Sleep�ϴ� �ݵ�� true�� ��ȯ�Ǿ�� ��
 	Sleep(300);
 
	ASSERT_TRUE(profiler.profile(__FUNCTIONW__));
}