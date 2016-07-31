#include "stdafx.h"
#include "PerformanceCounter.h"

void Blah()
{
	// 1ms ��ŭ ����.
	Sleep(1);
}

const int LOOP_COUNT = 10;
const double END_TIME = 100;

TEST(PerfomanceCounter, Test1)
{
	light::PerfomanceCounter counter;
	counter.begin();
	for(int i = 0; i < LOOP_COUNT; ++i)
	{
		Blah();
		Sleep((DWORD)(END_TIME / LOOP_COUNT));
	}
	counter.end();

	EXPECT_LE(END_TIME, counter.GetElapsedMilisecond());
}

TEST(PerfomanceCounter, Test2)
{
	light::PerfomanceCounter counter, loopcounter;
	counter.begin();
	for(int i = 0; i < LOOP_COUNT; ++i)
	{
		loopcounter.begin();
		Blah();
		loopcounter.end();	

		Sleep((DWORD)(ceil(END_TIME / LOOP_COUNT) - floor(loopcounter.GetElapsedSecond()))); // Blah���� �Һ�� �ð���ŭ �� ����.
	}

	counter.end();
	EXPECT_LE(END_TIME, counter.GetElapsedMilisecond());
}
