#include "stdafx.h"
#include "Vector.hpp"

light::Vector3D vec1(1.0f, 2.0f, 3.0f);
light::Vector3D vec2(0.5f, 0.8f, 0.2f);

TEST(Vector3D, Addition)
{
	light::Vector3D vec_result =  vec1 + vec2; //������ ����
	EXPECT_TRUE(vec_result == light::Vector3D(vec1.X() + vec2.X(), vec1.Y() + vec2.Y(), vec1.Z() + vec2.Z()));
}

TEST(Vector3D, Subtract)
{
	light::Vector3D vec_result =  vec1 - vec2; //������ ����
	EXPECT_TRUE(vec_result == light::Vector3D(vec1.X() - vec2.X(), vec1.Y() - vec2.Y(), vec1.Z() - vec2.Z()));
}

TEST(Vector3D, Normalize)
{
	float fLength = vec1.get_length(); //������ ����: v1�� ����
	EXPECT_EQ(fLength, sqrt(vec1.X()*vec1.X() + vec1.Y() * vec1.Y() + vec1.Z() * vec1.Z()));
	light::Vector3D vNormalize = vec1.Normalize(); //������ ��������: v1�� ��������
	EXPECT_TRUE(light::equals(vNormalize.X(), vec1.X() / fLength) && light::equals(vNormalize.Y(), vec1.Y() / fLength) && light::equals(vNormalize.Z(), vec1.Z() / fLength));
}

TEST(Vector3D, Multiply)
{
	light::Vector3D vScale = vec1.Scale(3.0f); //v1�� ��Į�� 3.0�� ���� ���� : k*v1
	EXPECT_TRUE(vScale.X() == vec1.X() * 3.0f && vScale.Y() == vec1.Y() * 3.0f && vScale.Z() == vec1.Z() * 3.0f);
}

TEST(Vector3D, Dot)
{
	float fDot = vec1.Dot(vec2); //������ ����: v1 . v2
	EXPECT_EQ(fDot, (vec1.X() * vec2.X() + vec1.Y() * vec2.Y() + vec1.Z() * vec2.Z()));
}

TEST(Vector3D, Disjoint)
{
	light::Vector3D vec_result = vec2.Scale( vec1.Dot(vec2) / ( vec2.get_length()*vec2.get_length() )); //���� ���� :  v2�� ������ v1������ ���غ���
}

TEST(Vector3D, Cross)
{
	light::Vector3D vec_result = vec1; //���� 1�� ����.
	vec_result.Cross(vec1, vec2); //������ ����: v1 x v2
}
