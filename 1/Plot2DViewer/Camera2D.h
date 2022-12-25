#ifndef CAMERA_2D_H
#define CAMERA_2D_H
#include <cmath>
#include "Model2D.h"
#include <windows.h>
#include <map>
using namespace std;

class Camera2D
{
protected:
	double X0, Y0;						// Экранные координаты начала мировой системы координат
	double px, py;						// Единицы масштаба мировой системы координат, выраженные в пикселях
	int W, H;							// Разрешение рабочей области окна
	bool drag;
	pair <double, double> phi = { 0, 2 * M_PI };


	int WorldToScreenX(double X)		// Переход от мировых координат к экранным 
	{
		return X0 + px * X;
	}
	int WorldToScreenY(double Y)		// Переход от мировых координат к экранным 
	{
		return Y0 + py * Y;
	}
public:
	double ScreenToWorldX(double X)		// Переход от экранных координат к мировым 
	{
		double tmp = X - X0 + 0.5;
		tmp = tmp / px;
		return tmp;
	}
	double ScreenToWorldY(double Y)		// Переход от экранных координат к мировым 
	{
		double tmp = -Y + Y0 - 0.5;
		tmp = tmp / py;
		return tmp;
	}
protected:
	double L()							// Абсцисса левой границы рабочей области окна (в мировых координатах)
	{
		return -X0 / px;
	}
	double R()							// Абсцисса правой границы рабочей области окна (в мировых координатах)
	{
		return (W - X0) / px;
	}
private:
	double posX, posY;					// Позиция графического курсора в мировых координатах (для функций MoveTo и LineTo)
	double posX1, posY1;

public:
	Camera2D(double X0, double Y0, double px, double py, int W, int H) : X0(X0), Y0(Y0), px(px), py(py), W(W), H(H)
	{
		posX = 0;
		posY = 0;
	}
	void Clear(HDC dc)
	{
		RECT r;
		GetClientRect(WindowFromDC(dc), &r);
		Rectangle(dc, 0, 0, r.right, r.bottom); // Очистка рабочей области окна
	}
	bool IsDraging()
	{
		return drag;
	}
	void StartDraging(double X, double Y)
	{
		drag = true;
		posX1 = X;
		posY1 = Y;
	}
	void Draging(double X, double Y)
	{
		int deltaX = X - posX1;
		int deltaY = Y - posY1;

		X0 += deltaX;
		Y0 += deltaY;

		posX1 = X;
		posY1 = Y;
	}
	void StopDraging()
	{
		drag = false;
	}

	void Mashtab(int delta, int X, int Y)
	{
		double k;
		if (delta > 0) k = 0.5;
		else k = 2;
		X0 = X + 0.5 - k * (X + 0.5 - X0);
		Y0 = Y + 0.5 - k * (Y + 0.5 - Y0);
		px = k * px;
		py = k * py;
	}
	void SetResolution(HDC dc)
	{
		RECT r;
		GetClientRect(WindowFromDC(dc), &r);
		int W_new = r.right;
		int H_new = r.bottom;

		double tmp1 = double(W_new) / double(W);
		py = px;
		double tmp2 = px / py;

		double px_new = tmp1 * px;

		double X0_new = tmp1 * X0;
		double tmp3 = tmp1 * tmp2;
		double tmp4 = double(H_new) / double(H);
		double Y0_new = tmp3 * Y0 + 0.5 * H * (tmp4 - tmp3);

		W = W_new;
		H = H_new;
		px = px_new;
		py = px_new;
		X0 = X0_new;
		Y0 = Y0_new;
	}
	void MoveTo(HDC dc, double X, double Y)
	{
		posX = X;
		posY = Y;
		MoveToEx(dc, WorldToScreenX(posX), WorldToScreenY(posY), 0);
	}
	void Line(HDC dc, double X, double Y)
	{
		LineTo(dc, WorldToScreenX(X), WorldToScreenY(Y));
		posX = X;
		posY = Y;
	}

	void Axes(HDC dc)
	{
		COLORREF PenColor = RGB(255, 255, 0);
		HPEN pen = (HPEN)SelectObject(dc, CreatePen(PS_SOLID, 1, PenColor));
		double l = L();
		double r = R();
		double ed = (R() - L()) / W;
		double j1 = 0, j2 = Y0, k1 = X0, k2 = 0;
        for (int i = 0; i < W*0.5; i++)
		{
			MoveToEx(dc, j1, j2, nullptr);
			LineTo(dc, W, j2);
			MoveToEx(dc, k1, k2, nullptr);
			LineTo(dc, k1, H);
			j2 += px;
			k1 += px;
		}

		j1 = 0;
		j2 = Y0;
		k1 = X0;
		k2 = 0;
		for (int i = 0; i < W * 0.5; i++)
		{	
			MoveToEx(dc, j1, j2, nullptr);
			LineTo(dc, W, j2);
			MoveToEx(dc, k1, k2, nullptr);
			LineTo(dc, k1, H);
			j2 -= px;
			k1 -= px;
		}
		DeleteObject(SelectObject(dc, pen));

		COLORREF PenColor1 = RGB(255, 0, 0);
		HPEN pen1 = (HPEN)SelectObject(dc, CreatePen(PS_SOLID, 1, PenColor1));
		
		MoveToEx(dc, 0, Y0, nullptr);
		LineTo(dc, W, Y0);
		MoveToEx(dc, X0, 0, nullptr);
		LineTo(dc, X0, H);

		DeleteObject(SelectObject(dc, pen1));  
		/*double ed = (R() - L()) / W;
		double s = 0.5 * (R() - L());

		for (int r = 1; r <= s;)
		{
			MoveTo(dc, r, 0);
			double x = r;
			double y;

			while (x >= -r)
		{
			y = double(sqrt(r * r - x * x));
			Line(dc, x, y);
			x = x -ed;
		}

		while (x <= r)
		{
			y = -double(sqrt(r * r - x * x));
			Line(dc, x, y);
			x = x + ed;
		}

			r = r + 1;
		}*/


		// Отрисовка координатных осей
	}

	void Figure(HDC dc, Model2D model)
	{
		Matrix<> vertex_tmp = model.GetVertexNow();

		int n_edges = model.GetN_Edges();
		pair<double, double>* edges_tmp = model.GetEdges();
		int j1 = 0, j2 = 0;
		for (int i = 0; i < n_edges; i++)
		{
			j1 = edges_tmp[i].first;
			j2 = edges_tmp[i].second;
			double tmp = vertex_tmp(0, j1);
			double t = vertex_tmp(1, j1);
			MoveTo(dc, vertex_tmp(0, j1), vertex_tmp(1, j1));
			Line(dc, vertex_tmp(0, j2), vertex_tmp(1, j2));
		}
	}


};

#endif CAMERA_2D_H
