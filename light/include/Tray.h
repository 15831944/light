#pragma once

#define WM_TRAYICON_MSG		WM_USER + 100

namespace light
{

/**
@brief Ʈ���� ������ Ŭ����
*/
class Tray
{
public:
	/**
	@brief ��� �޼ҵ�
	@param hWnd ������ �ڵ�
	@param hIcon ������ �ڵ�
	@param strTip ���� �ؽ�Ʈ
	*/
	static void set(HWND hWnd, HICON hIcon, const std::wstring& strTip)
	{
		// Ʈ���̿� ������ ���
		NOTIFYICONDATA  NotifyIconData;
		NotifyIconData.cbSize = sizeof(NotifyIconData);
		NotifyIconData.hWnd = hWnd; // ���� ������ �ڵ�
		NotifyIconData.uID = IDR_MAINFRAME;  // ������ ���ҽ� ID
		NotifyIconData.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP; // �÷��� ����
		NotifyIconData.uCallbackMessage = WM_TRAYICON_MSG; // �ݹ�޽��� ����
		NotifyIconData.hIcon = hIcon; // ������ �ε� 

		lstrcpy(NotifyIconData.szTip, strTip.c_str()); 
		Shell_NotifyIcon(NIM_ADD, &NotifyIconData);
		::SendMessage(hWnd, WM_SETICON, (WPARAM)TRUE, (LPARAM)NotifyIconData.hIcon);

		ShowWindow(hWnd, SW_HIDE);
	}

	/**
	@brief ���� �޼ҵ�
	@param hWnd ������ �ڵ�
	@param hIcon ������ �ڵ�
	@param strTip ���� �ؽ�Ʈ
	*/
	static void Change(HWND hWnd, HICON hIcon, const std::wstring& strTip)
	{
		// ����
		NOTIFYICONDATA NotifyIconData;
		NotifyIconData.cbSize = sizeof(NotifyIconData);
		NotifyIconData.hWnd = hWnd;
		NotifyIconData.uID = IDR_MAINFRAME;
		NotifyIconData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		NotifyIconData.uCallbackMessage = WM_TRAYICON_MSG;
		_tcscpy_s( NotifyIconData.szTip, _countof(NotifyIconData.szTip), strTip.c_str() );
		NotifyIconData.hIcon = hIcon;
		Shell_NotifyIcon( NIM_MODIFY, &NotifyIconData );
		::SendMessage(hWnd, WM_SETICON, (WPARAM)TRUE, (LPARAM)NotifyIconData.hIcon);
	}

	/**
	@brief ���� �޼ҵ�
	@param hWnd ������ �ڵ�
	*/
	static void Delete(HWND hWnd)
	{
		Release(hWnd);
		ShowWindow(hWnd, SW_SHOW);
	}

	/**
	@brief ������ �޼ҵ�
	@param hWnd ������ �ڵ�
	*/
	static void Release(HWND hWnd)
	{
		NOTIFYICONDATA NotifyIconData;
		NotifyIconData.cbSize = sizeof(NotifyIconData);
		NotifyIconData.hWnd = hWnd;
		NotifyIconData.uID = IDR_MAINFRAME;
		Shell_NotifyIcon( NIM_DELETE, &NotifyIconData );
	}
};

} //namespace light
