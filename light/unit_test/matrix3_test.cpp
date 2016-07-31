#include "stdafx.h"
#include "Matrix.hpp"

TEST(Matrix3, Test)
{

	//      [  2  1  3  ]       [  1  0 -2  ]
	//  A = [  1  2 -1  ]   B = [  3  1 -1  ]
	//      [  2 -1  3  ]       [  0  4 -2  ]
	float array1[] = { 2.0f, 1.0f, 2.0f, 1.0f, 2.0f, -1.0f, 3.0f, -1.0f, 3.0f };
	float array2[] = { 1.0f, 3.0f, 0.0f, 0.0f, 1.0f, 4.0f, -2.0f, -1.0f, -2.0f };
	light::Matrix3 matA(array1), matB(array2);
	light::Matrix3 result; 

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
