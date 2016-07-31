#include "light.h"
#include "Icon.h"
#include <ShellAPI.h>

namespace light
{

/**
@brief ������
@param ������ �̸�
*/
Icon::Icon(const std::wstring& name) 
	: m_hLarge(NULL)
	, m_hSmall(NULL)
	, m_name(name)
{
	::ExtractIconEx(name.c_str(), 0, &m_hLarge, &m_hSmall, 1);
}

/**
@brief �Ҹ���
*/
Icon::~Icon()
{
	::DestroyIcon(m_hLarge);
	::DestroyIcon(m_hSmall);
}

/**
@brief ������ �ڵ� ������ �޼ҵ�
@return ������ �ڵ�
*/
HICON Icon::Large()
{
	return m_hLarge;
}

/**
@brief ������ �ڵ� ������ �޼ҵ�
@return ������ �ڵ�
*/
HICON Icon::Small()
{
	return m_hSmall;
}

} // namespace light