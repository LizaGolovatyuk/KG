#pragma once
#ifndef AFFINE_TRANSF3D_H
#define AFFINE_TRANSF3D_H
#include "Matrix_.h"

Matrix<> Translation(double x, double y, double z)//������������ �������
{
	double T[16] = {
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	};
	return Matrix<>(4, 4, T);
}

// ����� ��������� ����������� �������, ������������ ������� ������� ��:
Matrix<> Identity() //������������� ��;
{
	double I[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	return Matrix<>(4, 4, I);

}
Matrix<> RotationZ(double t) //������� �� ���� t ������ ��� z;
{
	double c = cos(t);
	double s = sin(t);
	double R[16] = {
		c, -s, 0, 0,
		s, c, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	return Matrix<>(4, 4, R);
}
Matrix<> RotationZ(double c, double s) //������� �� ���� t ������ ��� z;
{
	double R[16] = {
		c, -s, 0, 0,
		s, c, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	return Matrix<>(4, 4, R);
}
Matrix<> RotationX(double c, double s) //������� �� ���� t ������ ��� x;
{
	double R[16] = {
		1, 0, 0, 0,
		0, c, -s, 0,
		0, s, c, 0,
		0, 0, 0, 1
	};
	return Matrix<>(4, 4, R);
}

Matrix<> RotationX(double t) //������� �� ���� t ������ ��� x;
{
	double c = cos(t);
	double s = sin(t);
	double R[16] = {
		1, 0, 0, 0,
		0, c, -s, 0,
		0, s, c, 0,
		0, 0, 0, 1
	};
	return Matrix<>(4, 4, R);
}
Matrix<> RotationY(double t) //������� �� ���� t ������ ��� y;
{
	double c = cos(t);
	double s = sin(t);
	double R[16] = {
		c, 0, s, 0,
		0, 1, 0, 0,
		-s, 0, c, 0,
		0, 0, 0, 1
	};
	return Matrix<>(4, 4, R);
}

Matrix<> Scaling(double kx, double ky, double kz) //���������������;
{
	double S[16] = {
		kx, 0, 0, 0,
		0, ky, 0, 0,
		0, 0, kz, 0,
		0, 0, 0, 1
	};
	return Matrix<>(4, 4, S);
}

Matrix<> MapingYZ()
{
	double R[16] = {
	-1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1
	};

	return Matrix<>(4, 4, R);
}

Matrix<> MapingZX()
{
	double R[16] = {
	1,0,0,0,
	0,-1,0,0,
	0,0,1,0,
	0,0,0,1
	};

	return Matrix<>(4, 4, R);
}
Matrix<> MapingXY()
{
	double R[16] = {
	1,0,0,0,
	0,1,0,0,
	0,0,-1,0,
	0,0,0,1
	};

	return Matrix<>(4, 4, R);
}

Matrix<> MapingX()
{
	double R[16] = {
	1,0,0,0,
	0,-1,0,0,
	0,0,-1,0,
	0,0,0,1
	};

	return Matrix<>(4, 4, R);
}

Matrix<> MapingY()
{
	double R[16] = {
	-1,0,0,0,
	0,1,0,0,
	0,0,-1,0,
	0,0,0,1
	};

	return Matrix<>(4, 4, R);
}
Matrix<> MapingZ()
{
	double R[16] = {
	-1,0,0,0,
	0,-1,0,0,
	0,0,1,0,
	0,0,0,1
	};

	return Matrix<>(4, 4, R);
}
Matrix<> MapingO()
{
	double R[16] = {
	-1,0,0,0,
	0,-1,0,0,
	0,0,1,0,
	0,0,0,1
	};

	return Matrix<>(4, 4, R);
}


#endif AFFINE_TRANSF3D_H