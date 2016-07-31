#include "stdafx.h"
#include "Matrix.hpp"

TEST(Matrix4, Test)
{
	//      [  2  1  3  4 ]       [  1  0 -2  1 ]
	//  A = [  1  2 -1  5 ]   B = [  3  1 -1  2 ]
	//      [  2 -1  3  6 ]       [  0  4 -2  3 ]
	//      [ -2  1  2  0 ]       [  0  4  2  4 ]

	float array1[] = { 2.0f, 1.0f, 2.0f, -2.0f, 1.0f, 2.0f, -1.0f, 1.0f, 3.0f, -1.0f, 3.0f, 2.0f, 4.0f, 5.0f, 6.0f, 0.0f };
	float array2[] = { 1.0f, 3.0f, 0.0f, 0.0f, 0.0f, 1.0f, 4.0f, 4.0f, -2.0f, -1.0f, -2.0f, 2.0f, 1.0f, 2.0f, 3.0f, 4.0f };
	light::Matrix4 matA(array1), matB(array2);
	light::Matrix4 result; 

	result = matA; //�������, I
	result.Identity();

	result = matA;
	result.Transpose(); //��ġ���, A^T

	result = matA + matB; //����� ����, A + B

	result = matA - matB; //����� ����, A - B

	result = matA * matB; //����� ����, A * B

	result = matA;
	result.Scalar(3.0f); //��İ� ��Į���� ��, 3 * A

	float det = matA.Det(); //��Ľ�, det(A)
	UNREFERENCED_PARAMETER(det);

	result = matB.Inverse(); //������� ����, B^-1
}
