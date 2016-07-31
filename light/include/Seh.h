#pragma once

// ������Ʈ ����. ������Ʈ �Ӽ� > C/C++ > �ڵ� ���� > C++ ���� ó�� ����. /EHa (��, SEH ���� ����(/EHa)) ����
#include <malloc.h>

namespace light
{

// ����� ���� �ڵ�� ��ġ�� �ʰ� �����϶�. 0x60000000 �̻��� �����ؾ���
const DWORD EXCEPTION_USER_RAISED = 0XE0000001;

class CustomExceptionHandler
{
public:
	static BOOL Install();
};

class Seh
{
public:
	static void Install();

	static void RaiseException(const char* msg, ULONG_PTR arg1, ULONG_PTR arg2);

	DWORD GetErrorCode() const;

private:
	Seh(const DWORD exceptionCode);

	static void Translator(unsigned, EXCEPTION_POINTERS* info);

private:
	DWORD m_xception_code;
};

} // namespace light

#define SEH_TRY bool __stack_overflow = false; \
	bool __exception_occured = false; \
	try

#define SEH_CATCH catch(const light::Seh& seh) \
	{ \
		__exception_occured = true; \
		__stack_overflow = (seh.GetErrorCode() == EXCEPTION_STACK_OVERFLOW); \
	} \
	\
	if (__stack_overflow) \
		_resetstkoflw();\
	if (__exception_occured)