#pragma once
#ifndef AFFINE_TRANSFORM_H
#define AFFINE_TRANSFORM_H

#include "Matrix_.h"

Matrix<> Translation2(double x, double y)//перенос на x,y
{
	double T[9] = {
		1, 0, x,
		0, 1, y,
		0, 0, 1 };
	return Matrix<>(3, 3, T);
}

Matrix<> Identity2() //тождественное АП;
{
	double I[9] = {
		1,0,0,
		0,1,0,
		0,0,1 };

	return Matrix<>(3, 3, I);
}

Matrix<> Rotation2(double t) //поворот на угол t;
{
	double c = cos(t);
	double s = sin(t);
	double R[9] = {
		c,-s,0,
		s,c,0,
		0,0,1 };
	return Matrix<>(3, 3, R);
}

Matrix<> Rotation2(double c, double s) // поворот на угол, косинус и синус которого пропорциональны величинам c и s;
{
	double x = sqrt(c * c + s * s);
	c = c / x;
	s = s / x;
	double R[9] = {
		c,-s,0,
		s,c,0,
		0,0,1 };
	return Matrix<>(3, 3, R);
}

Matrix<> Scaling2(double kx, double ky) //масштабирование;
{
	double S[9] = {
		kx,0,0,
		0,ky,0,
		0,0,1 };
	return Matrix<>(3, 3, S);
}

Matrix<> MapingX2()
{
	double R[9] = {
		1,0,0,
		0,-1,0,
		0,0,1 };

	return Matrix<>(3, 3, R);
}

Matrix<> MapingY2()
{
	double R[9] = {
		-1,0,0,
		0,1,0,
		0,0,1 };

	return Matrix<>(3, 3, R);
}

Matrix<> Maping02()
{
	double R[9] = {
		-1,0,0,
		0,-1,0,
		0,0,1 };

	return Matrix<>(3, 3, R);
}


#endif AFFINE_TRANSFORM_H