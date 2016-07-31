#include "light.h"
#include "MemoryUtil.hpp"

namespace light
{

/// ���μ��� ���� LFH ����
bool LFH::ApplyProcessHeap()
{
	return ApplyHeap(GetProcessHeap());
}

/// CRT ���� LFH ����
bool LFH::ApplyCrtHeap()
{
	intptr_t hCrtHeap = _get_heap_handle();	
	return ApplyHeap((PVOID)hCrtHeap);
}

/// ���μ����� ��� ���� ����
bool LFH::ApplyAllHeap()
{
	HANDLE Heaps[1025];
	DWORD Count = GetProcessHeaps( 1024, Heaps );
	for( DWORD i = 0; i < Count; ++i )
	{
		if( false == ApplyHeap(Heaps[i]) )
		{
			return false;
		}
	}
	return true;
}

bool LFH::ApplyHeap(HANDLE hHeap)
{
#ifdef _DEBUG
	LOG_ERROR(L"DebugMode is can't ApplyHeap. %p", hHeap);
	return false;
#else // _DEBUG
	// ����� attach ���̸�, �̹� ����� ��ó�� �����Ѵ�.
	if( TRUE == IsDebuggerPresent() )
	{
		return true;
	}

	// http://www.gpgstudy.com/forum/viewtopic.php?p=119181
	// MSDN : HeapQueryInformation http://msdn.microsoft.com/en-us/library/aa366703%28v=vs.85%29.aspx
	ULONG HeapInfo = 0;
	if( FALSE == HeapQueryInformation(hHeap, HeapCompatibilityInformation, &HeapInfo, sizeof(HeapInfo), NULL))
	{
		LOG_ERROR(L"HeapQueryInformation() Failed. Err[%u] Handle[%p]", GetLastError(), hHeap);
		return false;
	}

	const ULONG HEAP_LFH = 2;
	if( HEAP_LFH == HeapInfo )
	{
		// already used LFH
		return true;
	}

	// MSDN : HeapSetInformation http://msdn.microsoft.com/en-us/library/aa366705%28v=vs.85%29.aspx
	ULONG ulEnableLFH = 2;
	if ( FALSE == HeapSetInformation(hHeap, HeapCompatibilityInformation, &ulEnableLFH, sizeof(ulEnableLFH)))
	{
		LOG_ERROR(L"HeapSetInformation() Failed. Err[%u] Handle[%p]", GetLastError(), hHeap);
		return false;
	}
	return true;
#endif //_DEBUG
}

} //namespace light
