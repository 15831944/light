#pragma once

#include "Position.h"

namespace light
{

class Registry
{


/*********************************************************************************************
/* Parameters 
/*  bAutoExec[in]     : TRUE�̸� �������α׷� ������Ʈ���� ���, FALSE�� ����
/*  lpValueName[in]   : ������ ���� �̸�
/*  lpExeFileName[in] : �����ų ���α׷� Full ��� (NULL �ϼ� ����, ��, bAutoExec���� FALSE�̿��� ��)
/*
/* Return Values
/*  �������α׷� ������Ʈ���� ���/���� �����̸� TRUE, ���и� FALSE
*********************************************************************************************/
BOOL StartProgram(BOOL bAutoExec, LPCSTR lpValueName, LPCSTR lpExeFileName)
{
	BOOL _result;
	HKEY hKey;
    LONG lRes;

    if(bAutoExec)
    {
        if(lpValueName == NULL || lpExeFileName == NULL)
            return FALSE;

        lRes = ::RegOpekeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\on_update", 0L, KEY_WRITE, &hKey);
        if( lRes == ERROR_SUCCESS )
        {
            lRes = ::RegSetValueEx(hKey, lpValueName,
                                   0, REG_SZ, (BYTE*)lpExeFileName, lstrlen(lpExeFileName)); 
            ::RegCloseKey(hKey);
            if(lRes == ERROR_SUCCESS) 
                _result = TRUE;
            else
            {
                AfxMessageBox("Error");
                _result = FALSE;
            }
        }
        else if(lRes == ERROR_ACCESS_DENIED)
        {
            AfxMessageBox("������ �����ϴ�!!");
            _result = FALSE;
        }
        else
        {
            AfxMessageBox("Error");
            _result = FALSE;
        }
    }
    else                 // on_update ���� ����
    {
        lRes = ::RegOpekeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\on_update", 0 , KEY_ALL_ACCESS, &hKey);
        if( lRes != ERROR_SUCCESS )
            _result = FALSE;

        lRes = RegDeleteValue(hKey, lpValueName);      
        RegCloseKey(hKey);
        if(lRes == ERROR_SUCCESS)
            _result = TRUE;
        else if(lRes == ERROR_FILE_NOT_FOUND)
            _result = FALSE;
        else
        {
            AfxMessageBox("���� ���α׷����� �������� ���߽��ϴ�.");
            _result = FALSE;
        }
    }
    return _result;
}

};

} //namespace light
