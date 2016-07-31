#pragma once

namespace light
{

/**
@brief ���ػ� �����ս� ������
*/
class PerfomanceCounter
{
public:
	///������
	PerfomanceCounter();

	///�Ҹ���
	~PerfomanceCounter();
	
	void begin();

	void end();

	double GetElapsedSecond();

	DWORD GetElapsedMilisecond();

private:
	LARGE_INTEGER m_begin_counter;

	LARGE_INTEGER m_end_counter;
	
	LARGE_INTEGER m_frequency;

};

} //namespace light
