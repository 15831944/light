#pragma once

#include <typeinfo.h>

namespace light
{

class RTTITypeID
{
public:
	/**
	@brief ������. 
	@param type ���ø� ���� �޾Ƴ��� �Ⱦ��� ������, ���ø� ���� �߷��� ���ؼ���.
	*/
	template<typename Type>
	RTTITypeID(const Type* type)
	 : name(typeid(Type).name())
	{
		UNREFERENCED_PARAMETER(type);
	}

	RTTITypeID()
	: name("")
	{
	}

public:
	static RTTITypeID FromName(const char* name)
	{
		RTTITypeID typeID;
		typeID.name = name;
		return typeID;
	}

public:
	const char* get_name() const
	{
		return name;
	}

public:
	void operator = (RTTITypeID& rhs)
	{
		name = rhs.name;
	}

	int operator == (const RTTITypeID& typeID) const
	{
		return name == typeID.name;
	}

	bool operator < (const RTTITypeID& typeID) const
	{
		return name < typeID.name;
	}

private:
	const char* name;
};

} //namespace light
