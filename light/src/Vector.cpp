#include "light.h"
#include "Vector.hpp"

namespace light
{

Vector::Vector()
: x(0.0f)
, y(0.0f)
{
}

Vector::Vector(float fX, float fY)
: x(fX)
, y(fY)
{
}

Vector::Vector(const Vector& rhs)
: x(rhs.x)
, y(rhs.y)
{
}

Vector::~Vector()
{

}

// ������ ���� - ���� ���Ϳ� rhs ���Ͱ��� ������ �����Ѵ�.
float Vector::Dot(const Vector& rhs)
{
	return (x * rhs.x + y * rhs.y);
}

// ���Ϳ� ��Į�� k �� ���� ���͸� �����Ѵ�.
Vector Vector::Scale(float k)
{
	return Vector(k*x, k*y);
}

float Vector::get_length()
{
	return float(sqrt(x*x + y*y));
}

Vector Vector::Normalize()
{
	return Scale(1.0f/get_length());
}

Vector Vector::operator+(const Vector& rhs)
{
	return Vector(x+rhs.x , y+rhs.y);
}

Vector Vector::operator-(const Vector& rhs)
{
	return Vector(x-rhs.x , y-rhs.y);
}

void Vector::operator=(const Vector& rhs)
{
	x = rhs.x;
	y = rhs.y;
}

bool Vector::operator ==(const Vector& rhs) const
{
	return x == rhs.x && y == rhs.y;
}

Vector3D::Vector3D()
: x(0.0f)
, y(0.0f)
, z(0.0f)
{
}

Vector3D::Vector3D(float fX, float fY, float fZ)
: x(fX)
, y(fY)
, z(fZ)
{
}

Vector3D::Vector3D(const Vector3D& rhs)
: x(rhs.x)
, y(rhs.y)
, z(rhs.z)
{
}

Vector3D::~Vector3D()
{

}

// ������ ���� - ���� ���Ϳ� rhs ���Ͱ��� ������ �����Ѵ�.
float Vector3D::Dot(const Vector3D& rhs)
{
	return (x * rhs.x + y * rhs.y + z * rhs.z);
}

// ������ ���� - u ���Ϳ� v ���Ͱ��� ���� ���͸� ���� ���ͷ� ����.  
//     (this = u X v )
void Vector3D::Cross(const Vector3D& u, const Vector3D& v)
{
	x = u.y * v.z - u.z * v.y;
	y = u.z * v.x - u.x * v.z;
	z = u.x * v.y - u.y * v.x;
}

// ���Ϳ� ��Į�� k �� ���� ���͸� �����Ѵ�.
Vector3D Vector3D::Scale(float k)
{
	return Vector3D(k*x, k*y, k*z);
}

float Vector3D::get_length()
{
	return float(sqrt(x*x + y*y + z*z));
}

Vector3D Vector3D::Normalize()
{
	return Scale(1.0f/get_length());
}

Vector3D Vector3D::operator+(const Vector3D& rhs)
{
	return Vector3D(x+rhs.x , y+rhs.y , z+rhs.z);
}


Vector3D Vector3D::operator-(const Vector3D& rhs)
{
	return Vector3D(x-rhs.x , y-rhs.y , z-rhs.z);
}

void Vector3D::operator=(const Vector3D& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
}

bool Vector3D::operator ==(const Vector3D& rhs) const
{
	return x == rhs.x && y == rhs.y && z == rhs.z;
}

} //namespace light
