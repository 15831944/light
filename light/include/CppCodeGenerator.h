#pragma once

#include "CodeGenerateUtil.h"
#include <set>

namespace light
{

class CppCodeGenerator
	: public CodeGenrateUtil
{
protected:
	struct VARIABLE_INFO
	{
	public:
		/// ���� Ÿ��
		std::wstring TYPE;

		/// ���� �̸�
		std::wstring NAME;

		DWORD SIZE;

	public:
		/**
		@brief ������.
		*/
		VARIABLE_INFO()
			: SIZE(0)
		{
		}

		/**
		@brief ������. 
		@param type Ÿ��
		@param name �̸�
		@param size ũ��
		*/
		VARIABLE_INFO(const std::wstring& type, const std::wstring& name, const DWORD size = 0)
			: TYPE(type)
			, NAME(name)
			, SIZE(size)
		{
		}
	};

protected:
	typedef std::map<std::wstring, VARIABLE_INFO> MAP_VARIABLE;


public:
	virtual bool Open(const std::wstring& name, const std::wstring& ClassName, const std::wstring& NameSpace);

	bool End();

	virtual bool Variable(const std::wstring& Type, const std::wstring& Name, const DWORD size = 0);

	std::wstring Doc()
	{
		return m_Stream.str();
	}

	bool FileWrite(const std::wstring& file_name, const std::wstring& str);

protected:
	virtual bool Write();

protected:
	MAP_VARIABLE m_Variable;

	std::wstring m_ClassName;

	std::wstring m_FileName;

	std::wstring m_NameSpace;

	std::set<std::wstring> m_setUsedVariable;

private:
	std::wstringstream m_StreamMethod;

	std::wstringstream m_StreamVariable;

protected:
	std::wstringstream m_Stream;
};

} //namespace light
