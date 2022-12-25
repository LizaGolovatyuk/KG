#ifndef SCENE_2D_H
#define SCENE_2D_H
#include <cmath>
#include "Model2D.h"
#include "Matrix_.h"
#include "Camera2D.h"

class Scene2D : public Camera2D
{
private:
	vector<Model2D> models;

	//typedef double (*Func)(double);
public:
	Scene2D(double X0, double Y0, double px, double py, int W, int H) : Camera2D(X0, Y0, px, py, W, H)
	{	
	}
	void Put(Model2D model)
	{
		models.push_back(model);
	}

	void CreateVectorModels(vector<Model2D> models_)
	{
		for (int i = 0; i < models_.size(); i++)
		{
			models.push_back(models_[i]);
		}
	}
	
	void CreateModel(pair<double, double>* vertex,int n_vertex, pair<double, double>* edges, int n_edges_)
	{
		Model2D model(vertex, n_vertex, edges, n_edges_);
		models.push_back(model);
	}


	void Render(HDC dc)
	{
		//Axes(dc);

		for (int i = 0; i < models.size(); i++)
		{
			if (i == 0)
			{
				COLORREF PenColor1 = RGB(255, 0, 0);
				HPEN pen1 = (HPEN)SelectObject(dc, CreatePen(PS_SOLID, 1, PenColor1));
				Figure(dc, models[i]);
				DeleteObject(SelectObject(dc, pen1));
			}
			else 
			{
				if (i == 1)
				{
					COLORREF PenColor1 = RGB(139, 0, 255);
					HPEN pen1 = (HPEN)SelectObject(dc, CreatePen(PS_SOLID, 1, PenColor1));
					Figure(dc, models[i]);
					DeleteObject(SelectObject(dc, pen1));
				}
				else
				{
					if (i == 2)
					{
						COLORREF PenColor1 = RGB(0, 255, 0);
						HPEN pen1 = (HPEN)SelectObject(dc, CreatePen(PS_SOLID, 1, PenColor1));
						Figure(dc, models[i]);
						DeleteObject(SelectObject(dc, pen1));
					}
					else Figure(dc, models[i]);
				}
			}
		}
	}

	int Inside(int X, int Y)
	{
		int tmp = -1;
		for (int i = 0; i < models.size(); i++) 
		{
			pair<double, double> max = models[i].Max();
			pair<double, double> min = models[i].Min();
			double x1, x2, y1, y2;
			
				x1 = min.first;
				x2 = max.first;
			
				y1 = min.second;
				y2 = max.second;
	
			double x = ScreenToWorldX(X);
			double y = ScreenToWorldY(Y);
			y = -y;
			if (x >= x1 && x <= x2 && y >= y1 && y <= y2) tmp=i;
		}
		return tmp;
	}

	/*void Plot(HDC dc, Func f, bool axes = true)
	{
		if (axes)
			Axes(dc);
		double d_px = (R() - L()) / W;
		double i = phi.first;
		double r = f(i);
		double x = r * cos(i);
		double y = r * sin(i);
		MoveTo(dc, x, y);
		for (i = phi.first; i <= phi.second;)
		{
			r = f(i);
			x = r * cos(i);
			y = r * sin(i);
			Line(dc, x, y);
			i += d_px;
		}
	}*/

	int GetSize()
	{
		return models.size();
	}

	void Change(int i, Model2D m)
	{
		models[i] = m;
	}

	Model2D GetModel(int i)
	{
		return models[i];
	}
};

#endif SCENE_2D_H
