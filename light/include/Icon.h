#pragma once

namespace light
{

/**
@brief ������ Ŭ����
*/
class Icon
{
public:
	/// ������
	Icon(const std::wstring& name);

	/// �Ҹ���
	~Icon();

	/// ������ ū�� �ڵ� ������ �޼ҵ�
	HICON Large();

	/// ������ ������ �ڵ� ������ �޼ҵ�
	HICON Small();

private:
	/// ������ �̸�
	const std::wstring m_name;

	/// ������ �ڵ�
	HICON m_hLarge;

	/// ������ �ڵ�
	HICON m_hSmall;
};

} //namespace light
