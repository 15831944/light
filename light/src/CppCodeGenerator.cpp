#include "light.h"
#include "CppCodeGenerator.h"
#include "FileUtil.h"

#include <boost/range/adaptor/reversed.hpp>

namespace light
{

bool CppCodeGenerator::FileWrite(const std::wstring& file_name, const std::wstring& str)
{
	std::wofstream fileStream;
	fileStream.open(file_name.c_str(), std::ios_base::app);
	if ( true == fileStream.fail())
		return false;

	/// �� �����̹�~
	std::streamoff size = fileStream.rdbuf()->pubseekoff(0, std::ios_base::end);;
	if( 0 == size )
	{
		fileStream << L"#pragma once" << std::endl;
		fileStream << std::endl;
	}

	fileStream << str;
	fileStream.close();
	return true;
}

bool CppCodeGenerator::Open(const std::wstring& name, const std::wstring& ClassName, const std::wstring& NameSpace)
{
	m_ClassName = ClassName;
	m_FileName = name; 

	m_NameSpace = NameSpace;

	if ( false == m_NameSpace.empty() )
	{
		NameSpaceBegin(m_Stream, m_NameSpace);
		EndLine(m_Stream);
	}

	/// Ŭ���� ���� ����
	ClassBegin(m_Stream, ClassName);
	return true;
}

bool CppCodeGenerator::End()
{
	if( false == Write() )
	{
		LOG_ERROR(L"Write() Failed.");
		return false;
	}

	if ( false == m_NameSpace.empty() )
	{
		EndLine(m_Stream);
		NameSpaceEnd(m_Stream, m_NameSpace);
	}
	return true;
}

bool CppCodeGenerator::Write()
{
	std::map<std::wstring, INT> vector_infos;
	std::vector<std::wstring> variables;

	// �������� ����ͷ� ������ ������, ������ ������ ���� ������ ������ ��� �̸� std::vectorȭ ��Ű�µ�, �� �������� ���� ū ������ Declare���ֱ� �����̴�.
	for each(auto& val in boost::adaptors::reverse(m_Variable))
	{
		auto info = val.second;
		std::wstring method_name = info.NAME;
		const std::wstring& type = info.TYPE;
		std::wstring member_variable;
		std::wstring variable = info.NAME;

		// ������ �������� �������� Ȯ���Ѵ�.
		// ���ڰ� ���ԵǾ��ִٸ�, std::vector�� �ǵ� �Ѵ�.
		INT at = method_name.size() - 1;
		if( 0 != isdigit( method_name.at(at) ) )
		{
			std::wstring strNumber = method_name.substr(at);
			variable.erase(at);

			// ���� ��ġ�� access�ϴ� �迭 ���� �ڵ带 GetMethod�� ����
			member_variable = L"m_" + variable + L"[" + strNumber + L"]";
			GetMethod(m_StreamMethod, ToParameterType(type), method_name + L"Reference", member_variable);

			INT size = _wtoi(strNumber.c_str());
			vector_infos[variable] = std::max(vector_infos[variable], size + 1);

			if(m_setUsedVariable.find(variable) == m_setUsedVariable.end()) // ���� �̸����� �� ��� �õ��ϸ� ĵ���ϱ� ���� �˻� �ڵ�
			{
				m_setUsedVariable.insert(variable);

				member_variable = L"m_" + variable;

				Declare(m_StreamVariable, ToVector(type), member_variable);
				GetMethod(m_StreamMethod, ToVectorReference(type), L"Vector" + variable, L"m_" + variable);
			}
		}
		else
		{
			member_variable = L"m_" + info.NAME;
			GetMethod(m_StreamMethod, ToParameterType(type), method_name + L"Reference", member_variable);
			ConstGetMethod(m_StreamMethod, type, method_name, member_variable);

			if( info.TYPE == L"WCHAR" )
			{
				SizeMethod(m_StreamMethod, method_name, member_variable);
				Declare(m_StreamVariable, type, member_variable, info.SIZE);
			}
			else
			{
				SetMethod(m_StreamMethod, type, method_name, member_variable);
				Declare(m_StreamVariable, type, member_variable);
			}

			variables.push_back(member_variable);
			m_setUsedVariable.insert(variable);
		}
	}

	// method declaration & implements.
	Public(m_Stream);
	ConstructorBegin(m_Stream, m_ClassName);
	for each(auto& val in vector_infos)
	{
		VectorResize(m_Stream, L"m_" + val.first, val.second);
	}

	for each(auto& variable in variables)
	{
		Memset(m_Stream, variable);
	}

	ConstructorEnd(m_Stream);
	m_Stream << m_StreamMethod.str();

	// variable declaration
	Private(m_Stream);
	m_Stream << m_StreamVariable.str();

	// end of class declaration
	ClassEnd(m_Stream);
	EndLine(m_Stream);
	return true;
}

bool CppCodeGenerator::Variable(const std::wstring& type, const std::wstring& name, const DWORD size)
{
    m_Variable.insert({ name, VARIABLE_INFO(type, name, size) });
	return true;
}

} //namespace light
