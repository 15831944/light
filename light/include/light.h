#pragma once

/// ���� �ڵ� ������ ��� ����
#pragma warning(disable:4819) 

#pragma warning(disable:4091) 

#pragma warning(disable:4996) 

// �̸� �߸��� ���
#pragma warning (disable:4503) 

// �̻�� ���� �Լ� ����
#pragma warning (disable:4505) 

#include "Macro.h" 

#include "Util.h"

#define WIN32_LEAN_AND_MEAN

#ifndef WINVER				
#define WINVER 0x0601 // ��� ������ �ּ� OS ������ �������ּ���.
#endif //WINVER
         
#ifndef _WIN32_WINNT		
#define _WIN32_WINNT 0x0601 // ��� ������ �ּ� OS ������ �������ּ���.
#endif //_WIN32_WINNT

#pragma warning ( push )
#pragma warning ( disable:4005 ) 
#include <boost/asio.hpp>
#pragma warning ( pop )

///#include <windows.h> ���� ���� ����Ǿ����. Winsock �浹�� ���� ����~
#ifndef _WINSOCKAPI_ 
#define _WINSOCKAPI_
#endif //_WINSOCKAPI_

/// _WINSOCKAPI_ ��ũ�� �����ϰ� ���� ������ ��� ����~
#include <WindowsX.h> 

#include "str.h"

/// �α� ���
#include "LogHelper.h" 
