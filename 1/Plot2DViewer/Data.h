#define _USE_MATH_DEFINES
#include <cmath>
#include <windows.h>
#include <map>
using namespace std;

double					// Исходные значения параметров X0, Y0, px, py
X0 = 200,
Y0 = 200,
px = 30,
py = 30;
int
W = 400,
H = 400;

double PolarRoz(double x)
{
	return sin(6 * x);
}

double Kardioida(double x)
{
	return 1 - sin(x);
}

pair <double, double> Star(double t)
{
	pair <double, double> tmp;
	tmp.first = 4 * cos(t) * cos(t) * cos(t);
	tmp.second = 2 * sin(t) * sin(t) * sin(t);
	return tmp;
}
