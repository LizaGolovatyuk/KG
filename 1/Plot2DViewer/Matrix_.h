#pragma once
#ifndef MATRIX_H
#define MATRIX_H
#include "Triad.h"
#include <iostream>

using namespace std;


template <typename Cell = double>
class Matrix
{
private:
	int n, m;
	Cell** cells;
	void AllocateCells(int N, int M);
	void FreeCells();
public:
	Matrix() : n(0), m(0), cells(nullptr) {}	// Конструктор по умолчанию
	Matrix(const Matrix&);					// Конструктор копирования
	Matrix(int N, int M);							// Конструктор нулевой матрицы
	Matrix(int N, int M, Cell*);			// Конструктор матрицы из списка
	Matrix(int M, pair<Cell,Cell>*);
	Matrix(int, Triad*);
	Matrix(int N, int M, pair<Cell, Cell>* list);
	Matrix(int, int, Triad*);
	~Matrix();								// Деструктор

	Cell& operator()(int i, int j) { return cells[i][j]; }

	Matrix& operator = (const Matrix&);		// Перегрузка оператора присваивания
	Matrix  operator + (const Matrix&);		// Сложение матриц
	Matrix  operator - (const Matrix&);		// Вычитание матриц
	Matrix  operator * (const Matrix&);		// Умножение матриц

	int GetN() { return n; }
	int GetM() { return m; }

	friend istream& operator >> <> (istream&, Matrix&);			// Перегрузка оператора >> для ввода матрицы
	friend ostream& operator << <> (ostream&, const Matrix&);	// Перегрузка оператора << для вывода матрицы
};


template <typename Cell>
Matrix<Cell>::Matrix(const Matrix<Cell>& M)
{
	AllocateCells(M.n, M.m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cells[i][j] = M.cells[i][j];
}

template <typename Cell>
Matrix<Cell>::Matrix(int N, int M)
{
	AllocateCells(N, M);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cells[i][j] = 0;
}

template <typename Cell>
Matrix<Cell>::Matrix(int N, int M, Cell * list)
{
	AllocateCells(N, M);
	int k = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
		{
			cells[i][j] = list[k];
			k++;
		}
	}
}

template <typename Cell>
Matrix<Cell>::Matrix(int N, int M, pair<Cell, Cell>* list)
{
	AllocateCells(N, M);
	for (int j = 0; j < m; j++) {
		cells[0][j] = list[j].first;
		cells[1][j] = list[j].second;
	}
}

template <typename Cell>
Matrix<Cell>::Matrix(int M, pair<Cell, Cell>* list)
{
	AllocateCells(3, M);
	for (int j = 0; j < m; j++) {	
		    cells[0][j] = list[j].first;
			cells[1][j] = list[j].second;
			cells[2][j] = 1;	
	}
}

template <typename Cell>
Matrix<Cell>::Matrix(int n, Triad* v)//матрица однородный координат
{
	AllocateCells(4, n);
	for (int j = 0; j < n; j++)
	{
		int i = 0;
		Cell x = v[j].getX();
		Cell y = v[j].getY();
		Cell z = v[j].getZ();
		cells[i][j] = x;
		i++;
		cells[i][j] = y;
		i++;
		cells[i][j] = z;
		i++;
		cells[i][j] = 1;
	}

}

template <typename Cell>
Matrix<Cell>::Matrix(int n, int m, Triad* v) //матрица граней
{
	AllocateCells(m, n);
	for (int i = 0; i< m; i++)
	{
		int j = 0;
		Cell point1 = v[i].getX();
		Cell point2 = v[i].getY();
		Cell point3 = v[i].getZ();
		cells[i][j] = point1;
		j++;
		cells[i][j] = point2;
		j++;
		cells[i][j] = point3;
	}

}

template <typename Cell>
Matrix<Cell>::~Matrix()
{
	FreeCells();
}

template <typename Cell>
Matrix<Cell>& Matrix<Cell>::operator=(const Matrix & M)
{
	if (n != M.n && m != M.m)
	{
		FreeCells();
		AllocateCells(M.n, M.m);
	}
	for (int i = 0; i < M.n; i++)
		for (int j = 0; j < M.m; j++)
			cells[i][j] = M.cells[i][j];
	return *this;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator+(const Matrix & M)
{
	if (n == M.n && m == M.m)
	{
		Matrix<Cell> res(*this);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				res.cells[i][j] += M.cells[i][j];
		return res;
	}
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator-(const Matrix & M)
{
	if (n == M.n && m == M.m)
	{
		Matrix<Cell> res(*this);

		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				res.cells[i][j] -= M.cells[i][j];
		return res;
	}
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator*(const Matrix & M)
{
	if (m == M.n)
	{
		double sum = 0;
		Matrix<Cell> res(n, M.m);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < M.m; j++)
			{
				for (int k = 0; k < m; k++)
					sum += cells[i][k] * M.cells[k][j];
				res.cells[i][j] = sum;
				sum = 0;
			}
		}
		return res;
	}
}

template <typename Cell>
void Matrix<Cell>::AllocateCells(int N, int M)
{
	cells = new Cell * [N];
	for (int i = 0; i < N; i++)
		cells[i] = new Cell[M];
	n = N;
	m = M;
}

template <typename Cell>
void Matrix<Cell>::FreeCells()
{
	if (n > 0) {
		for (int i = 0; i < n; i++)
			delete cells[i];
		delete cells;
	}
	n = 0;
	m = 0;
}

template <typename Cell>
istream& operator >> (istream & fi, Matrix<Cell> & M)
{
	for (int i = 0; i < M.n; i++)
		for (int j = 0; j < M.m; j++)
			fi >> M.cells[i][j];
	return fi;
}

template <typename Cell>
ostream & operator << (ostream & fo, const Matrix<Cell> & M)
{
	for (int i = 0; i < M.n; i++)
	{
		fo << "  ";
		for (int j = 0; j < M.m; j++)
			fo << M.cells[i][j] << " \t";
		fo << endl;
	}
	return fo;
}

#endif MATRIX_H