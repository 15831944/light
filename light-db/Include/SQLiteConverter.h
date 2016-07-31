#pragma once

namespace light
{
	
namespace db
{

namespace SQLite
{

/// ��ȯ�� Ÿ��
enum TYPE
{
	DENIED,
	BOOL,
	CHAR,
	UCHAR,
	SHORT,
	USHORT,
	LONG,
	ULONG,
	LONGLONG,
	ULONGLONG,
	FLOAT,
	DOUBLE,
	TSTRING,
	NULL_TERMINATED_STRING,
};

/**
@brief ���ڿ��� Ư�� Ÿ������ ��ȯ�ؼ� ���� ������ �����ϴ� ����ü
*/
struct CONVERT_INFO
{
public:
	/// ��ȯ�� ��� Ÿ��
	TYPE Type;

	/// ���� ũ��
	size_t Length;

	/// ���� ������
	void* Ptr;

public:
	/**
	@brief ������. �⺻ �����ڴ� �������� �ʴ´�.
	@param type ��ȯ�� Ÿ��
	@param length ���� ũ��
	@param ptr ���� ������
	*/
	CONVERT_INFO(const TYPE type, const size_t length, void* ptr)
		: Type(type)
		, Length(length)
		, Ptr(ptr)
	{
	}
};

/// enum���� �������� ���� ���� �� ������ Ÿ�� ������ ���� ���� template ����ü ����
template <bool> struct Enumerator;

/// enum���� �������� �־ true�� ��ȯ �� ���� ������ ������ ó���ϱ� ���� template ����ü
template <> struct Enumerator<true>
{
	static const TYPE c_type_value = DENIED;
};

template <typename T> inline TYPE ConvertType(T)        { return Enumerator<std::tr1::is_enum<T>::value>::c_type_value; }
template <> inline TYPE ConvertType(char)               { return CHAR; }   
template <> inline TYPE ConvertType(unsigned char)      { return UCHAR; }
template <> inline TYPE ConvertType(bool)               { return BOOL; }
template <> inline TYPE ConvertType(short)              { return SHORT; }
template <> inline TYPE ConvertType(unsigned short)     { return USHORT; }
template <> inline TYPE ConvertType(int)                { return LONG; }
template <> inline TYPE ConvertType(unsigned int)       { return ULONG; }
template <> inline TYPE ConvertType(long)               { return LONG; }
template <> inline TYPE ConvertType(unsigned long)      { return ULONG; }
template <> inline TYPE ConvertType(__int64)            { return LONGLONG; }
template <> inline TYPE ConvertType(unsigned __int64)   { return ULONGLONG; }

template <> inline TYPE ConvertType(float)              { return FLOAT; }
template <> inline TYPE ConvertType(double)             { return DOUBLE; }

template <> inline TYPE ConvertType(std::wstring)       { return TSTRING; }
template <> inline TYPE ConvertType(const std::wstring&){ return TSTRING; }
template <> inline TYPE ConvertType(std::wstring&)      { return TSTRING; }
template <> inline TYPE ConvertType(TCHAR*)             { return NULL_TERMINATED_STRING; }
template <> inline TYPE ConvertType(const TCHAR*)       { return NULL_TERMINATED_STRING; }
//////////////////////////////////////////////////////////////////////////

static bool ToString(const std::wstring& str, const CONVERT_INFO& info)
{
	std::wstring& dest = cast<std::wstring>(info.Ptr);
	dest = str;
	return true;
}

static bool ToInteger(const std::wstring& str, const CONVERT_INFO& info)
{
	int& dest = cast<int>(info.Ptr);
	dest = _ttoi(str.c_str());
	return true;
}

static bool ToInteger64(const std::wstring& str, const CONVERT_INFO& info)
{
	__int64& dest = cast<__int64>(info.Ptr);
	dest = _ttoi64(str.c_str());
	return true;
}

static bool ToShort(const std::wstring& str, const CONVERT_INFO& info)
{
	short& dest = cast<short>(info.Ptr);
	dest = static_cast<short>(_ttoi(str.c_str()));
	return true;
}

static bool ToChar(const std::wstring& str, const CONVERT_INFO& info)
{
	char& dest = cast<char>(info.Ptr);
	dest = static_cast<char>(_ttoi(str.c_str()));
	return true;
}

static bool ToDouble(const std::wstring& str, const CONVERT_INFO& info)
{
	double& dest = cast<double>(info.Ptr);
	dest = _ttof(str.c_str());
	return true;
}

static bool ToFloat(const std::wstring& str, const CONVERT_INFO& info)
{
	float& dest = cast<float>(info.Ptr);
	dest = static_cast<float>(_ttof(str.c_str()));
	return true;
}

static bool ToNullTerminatedString(const std::wstring& str, const CONVERT_INFO& info)
{
	TCHAR* dest = cast_ptr<TCHAR>(info.Ptr);
	_tcsncpy_s(dest, info.Length, str.c_str(), _TRUNCATE);
	return true;
}

/**
@breif ��ȯ �޼ҵ�
@param str ���ڿ���
@param info ��ȯ�� ���� ��ü
@return ���� ����
*/
static bool Convert(const std::wstring& str, const CONVERT_INFO& info)
{
	switch(info.Type)
	{
	case BOOL:
	case CHAR:
	case UCHAR:
		return ToChar(str, info);
	case SHORT:
	case USHORT:
		return ToShort(str, info);
	case LONG:
	case ULONG:
		return ToInteger(str, info);
	case LONGLONG:
	case ULONGLONG:
		return ToInteger64(str, info);
	case FLOAT:
		return ToFloat(str, info);
	case DOUBLE:
		return ToDouble(str, info);
	case TSTRING:
		return ToString(str, info);
	case NULL_TERMINATED_STRING:
		return ToNullTerminatedString(str, info);
	}
	return false;
}

} //namespace SQLite

} //namespace db

} //namespace light