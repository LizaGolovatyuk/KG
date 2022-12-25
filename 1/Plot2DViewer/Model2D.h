#pragma once
#include "Matrix_.h"
#include "AfineTransform_.h"
#include <vector>

class Model2D
{
private:

	Matrix<> AT;
	Matrix<> Vertex;
	Matrix<> VertexNow;
	pair<double, double>* Edges;
	int n_edges;

public:
	Model2D(Matrix<> Vertex_, Matrix<> Edges_, int n_edges_)
	{
		n_edges = n_edges_;
		Edges = new pair<double, double>[n_edges_];
		for (int i = 0; i < n_edges_; i++) 
		{
			Edges[i].first = Edges_(0,i);
			Edges[i].second = Edges_(1,i);
		}
		Vertex = Vertex_;
		VertexNow = Vertex_;
	}
	Model2D(pair<double, double>* v, int n_vertex, pair<double, double>* Edges_, int n_edges_)
	{
		AT = Identity2();

		Matrix<> Vertex_1(n_vertex, v);
		Vertex = Vertex_1;
		VertexNow = Vertex;

		Edges = new pair<double, double>[n_edges_];
		for (int i = 0; i < n_edges_; i++)
		{
			Edges[i].first = Edges_[i].first;
			Edges[i].second = Edges_[i].second;
		}
		n_edges = n_edges_;
	}
	pair<double, double> Min() {
		double minx = VertexNow(0, 0);
		double miny = VertexNow(1, 0);
		for (int i = 0; i < VertexNow.GetM(); i++)
		{
			if (VertexNow(0, i) < minx) minx = VertexNow(0, i);
			if (VertexNow(1, i) < miny) miny = VertexNow(1, i);
		}
		pair<double, double> min;
		min.first = minx;
		min.second = miny;
		return min;
	}

	pair<double, double> Max() {
		double maxx = VertexNow(0, 0);
		double maxy = VertexNow(1, 0);
		for (int i = 0; i < VertexNow.GetM(); i++)
		{
			if (VertexNow(0, i) > maxx) maxx = VertexNow(0, i);
			if (VertexNow(1, i) > maxy) maxy = VertexNow(1, i);
		}
		pair<double, double> max;
		max.first = maxx;
		max.second = maxy;
		return max;
	}

	pair<double, double> Size()
	{
		pair<double, double> max = Max();
		pair<double, double> min = Min();
		double a = max.first - min.first;
		double b = max.second - min.second;
		pair<double, double> size;
		size.first = a;
		size.second = b;
		return size;
	}

	pair<double, double> OXY()
	{
		pair<double, double> min = Min();
		pair<double, double> size = Size();
		pair<double, double> oxy;
		oxy.first = size.first * 0.5 + min.first;
		oxy.second = size.second * 0.5 + min.second;
		return oxy;
	}

	pair<double, double> GetFirst()
	{
		pair<double, double> P;
		P.first = VertexNow(0, 0);
		P.second = VertexNow(1, 0);
		return P;
	}
	void Apply(Matrix<> AT_new, bool tmp)
	{
		AT = AT_new * AT;
		if(tmp==true) VertexNow = AT * Vertex;
	}
	Matrix<> GetVertexNow() { return VertexNow; }
	Matrix<> GetVertex() { return Vertex; }
	pair<double, double>* GetEdges() { return Edges; }
	int GetN_Edges() { return n_edges; }

};