#pragma once
#include <vector>
#include "Scene2D.h"
#include "Camera3D.h"
#include "Model3D.h"
class Scene3D:public Scene2D
{
	Camera3D camera;
	vector <Model3D> models3D;
	vector <Model2D> models2D;


public:
	Scene3D(double X0, double Y0, double px, double py, int W, int H) : Scene2D(X0, Y0, px, py, W, H)
	{
		Triad Ov(5, 7, -5);
		Triad N(5, 10, -6);
		Triad T(0, -4, -2);
		double F = 16;
		camera.setOv(Ov);
		camera.setN(N);
		camera.setT(T);
		camera.setF(F);

		camera.UpdateCamera();
	}


	void CreateModel3D(int point, Triad* list1, pair<double, double>* Edges_, int n_edges, int count_facet, Triad* list3)
	{
		Model3D model(point,list1, Edges_,n_edges,count_facet,list3);
		models3D.push_back(model);
		Put(CreateModel2D(model));
		models2D.push_back(CreateModel2D(model));
	}
	void Change3D(int i, Model3D m)
	{
		models3D[i] = m;
		models2D[i] = CreateModel2D(models3D[i]);
		Change(i, models2D[i]);
	}
	Model2D CreateModel2D(Model3D model3D)
	{
		Matrix<> vertex_now = camera.getSwp() * model3D.getVertexNow();
		Model2D model(vertex_now, model3D.getEdges(), model3D.n_edg);
		return model;
	}
	void Render3D(HDC dc)
	{
		Render(dc);
	}
	Model3D getModel3D(int i) {
		return models3D[i];
	}
	void Clear3D(HDC dc)
	{
		Clear(dc);
	}
};

