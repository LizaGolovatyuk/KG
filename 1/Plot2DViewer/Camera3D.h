#pragma once
#ifndef CAMERA_3D_H
#define CAMERA_3D_H
#include "Camera2D.h"
#include "Triad.h"

class Camera3D {
	Triad Ov; //мировые координаты точки мировой плоскости, расположенной напротив наблюдателя
	Triad T; //мировые координаты вектора задающего вертикальное направление для наблюдателя
	Triad N; //мировые координаты вектора нормали к экранной плоскости (от Ov к набл)
	double F; //расстояние от набл. до экрвнной плоскости

	Matrix<double> Swv;
	Matrix<double> Svp;

public:
	Matrix<double> Swp;

public:
	Camera3D() {};

	Camera3D(Triad Ov, Triad T, Triad N, double F) 
	{
		this->Ov = Ov;
		this->T = T;
		this->N = N;
		this->F = F;

		UpdateCamera();
	}


	void setOv(Triad Ov) { this->Ov = Ov; }
	void setT(Triad T) { this->T = T; }
	void setN(Triad N) { this->N = N; }
	void setF(double F) { this->F = F; }


	Triad i_v()
	{
		Triad I(T.vect(N));
		return I / I.weight();
	}
	Triad j_v()
	{
		return k_v().vect(i_v());
	}
	Triad k_v()
	{
		return N / N.weight();
	}

	void UpdateCamera()
	{
		createSwv();
		createSvp();
		createSwp();
	}

	void createSvp()
	{
		double param = -1 / F;
		double R[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,param,1
		};
		Matrix<double> S(3, 4, R);
		Svp = S;

	}
	void createSwp()
	{
		Swp = Swv * Svp;
	}
	void createSwv()
	{
		Triad X = i_v();
		Triad Y = j_v();
		Triad Z = k_v();

		double x_i = X.getX();
		double x_j = X.getY();
		double x_k = X.getZ();

		double y_i = Y.getX();
		double y_j = Y.getY();
		double y_k = Y.getZ();

		double z_i = Z.getX();
		double z_j = Z.getY();
		double z_k = Z.getZ();

		double param1 = -(x_i * Ov.getX() + x_j * Ov.getY() + x_k * Ov.getZ());
		double param2 = -(y_i * Ov.getX() + y_j * Ov.getY() + y_k * Ov.getZ());
		double param3 = -(z_i * Ov.getX() + z_j * Ov.getY() + z_k * Ov.getZ());

		double R[16] = {
		x_i,y_i,z_i,param1,
		x_j,y_j,z_j,param2,
		x_k,y_k,z_k,param3,
		0,0,0,1
		};
		Matrix<double> S(3, 4, R);
		Swv = S;
	}

	Matrix<double> getSwp()
	{
		return Swp;
	}
};
#endif CAMERA_3D_H
