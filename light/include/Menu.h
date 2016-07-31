#pragma once

#include <Windows.h>
#include "Dispatcher.hpp"

namespace light
{

/**
@brief �˾� �޴� Ŭ����
*/
class Popup
{
public:
	typedef boost::function<bool ()> func_t;

public:
	/// ������
	Popup(const HWND& hWnd);
	
	/// �Ҹ���
	~Popup();

	///�˾� �߰�
	bool Add(const std::wstring& name, func_t func);
	
	/// ������ �߰�
	bool Seperate();
	
	/// �����ֱ�
	bool Show();

	/// �����
	bool Hide();
	
	/// Ŀ�ǵ� �ݹ�
	BOOL command(WORD nID);

private:
	///������ �ڵ� ������
	const HWND& m_hWnd;
	
	///�˾� �޴� �ڵ�
	HMENU m_hPopup;
	
	///�ĺ� �ε���
	WORD m_AccIdx;

	///�ݹ� ��
	Dispatcher<WORD> m_dispatcher; 
};

} //namespace light  

