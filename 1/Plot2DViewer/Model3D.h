#pragma once
#include "AfineTransform3D.h"
#include "Triad.h"
#include "Matrix_.h"

class Model3D {
protected:
	Matrix<> vertex;
	Matrix<> edges;
	Matrix<> facet;

	Matrix<> AT;
	Matrix<> vertex_now;

public:
	int n_edg;

	Model3D() {};
	Model3D(int point, Triad* list1, pair<double,double>* Edges_, int n_edges, int count_facet, Triad* list3) {
		//n_edg = n_edges;
		Matrix<> tmp_vertex(point, list1);//вершины
		Matrix<> tmp_edges(2,n_edges, Edges_);//ребра

		Matrix<> tmp_facet(3, count_facet, list3);//грани
		createEdges(count_facet, list3);
		vertex = tmp_vertex;
		//edges = tmp_edges;
		facet = tmp_facet;

		AT = Identity();
		vertex_now = vertex;
	}

	void createEdges(int count_facet, Triad* list1)
	{
		int count_edges = count_facet * 3;
		pair<double, double>* list = new pair<double, double>[count_edges];
		int j = 0;
		for (int i = 0; i < count_facet; i++)
		{
			list[j].first = list1[i].getX();
			list[j].second = list1[i].getY();
			j++;
			list[j].first = list1[i].getX();
			list[j].second = list1[i].getZ();
			j++;
			list[j].first = list1[i].getZ();
			list[j].second = list1[i].getY();
			j++;

		}
		n_edg= count_edges;
		Matrix<> tmp_edges(2, count_edges, list);
		edges = tmp_edges;
	}
	Triad Min3D() {
		double minx = vertex_now(0, 0);
		double miny = vertex_now(1, 0);
		double minz = vertex_now(2, 0);
		for (int i = 0; i < vertex_now.GetM(); i++)
		{
			if (vertex_now(0, i) < minx) minx = vertex_now(0, i);
			if (vertex_now(1, i) < miny) miny = vertex_now(1, i);
			if (vertex_now(2, i) < minz) minz = vertex_now(2, i);
		}
		Triad min3D(minx, miny, minz);
		return min3D;
	}
	Triad Max3D() {
		double maxx = vertex_now(0, 0);
		double maxy = vertex_now(1, 0);
		double maxz = vertex_now(2, 0);
		for (int i = 0; i < vertex_now.GetM(); i++)
		{
			if (vertex_now(0, i) > maxx) maxx = vertex_now(0, i);
			if (vertex_now(1, i) > maxy) maxy = vertex_now(1, i);
			if (vertex_now(2, i) > maxz) maxz = vertex_now(2, i);
		}
		Triad max3D(maxx,maxy,maxz);
		return max3D;
	}

	Triad Size3D()
	{
		Triad max = Max3D();
		Triad min = Min3D();
		double a = max.getX()-min.getX();
		double c = max.getZ() - min.getZ();
		double b = max.getY() - min.getY();
		Triad size(a, b, c);
		return size;
	}

	Triad Middle()
	{
		Triad min = Min3D();
		Triad size3D = Size3D();
		Triad middle(size3D.getX() * 0.5 + min.getX(), size3D.getY() * 0.5 + min.getY(), size3D.getZ() * 0.5 + min.getZ());
		return middle;
	}

	Matrix<> getVertex()
	{
		return vertex;
	}
	Matrix<> getVertexNow()
	{
		return vertex_now;
	}
	Matrix<> getEdges()
	{
		return edges;
	}
	Matrix<> getFacet()
	{
		return facet;
	}

	Triad get0()
	{
		return Triad(vertex_now(0, 0), vertex_now(1,0),vertex_now(2,0));
	}
	Triad get3()
	{
		return Triad(vertex_now(0, 3), vertex_now(1,3), vertex_now(2,3));
	}
	void Apply(Matrix<> A, bool tmp = false)
	{
		AT = A * AT;
		if (tmp)vertex_now = AT * vertex;
	}
};
