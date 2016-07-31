#pragma once

#include "light.h"

namespace light
{

class LFH
{
public:
	/// ���μ��� ���� LFH ����
	static bool ApplyProcessHeap();

	/// CRT ���� LFH ����
	static bool ApplyCrtHeap();

	/// ���μ����� ��� ���� ����
	static bool ApplyAllHeap();

private:
	static bool ApplyHeap(HANDLE hHeap);
};

} //namespace light
