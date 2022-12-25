#pragma once
class Triad
{
	double x;
	double y;
	double z;
public:
	Triad()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	};
	Triad(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Triad(Triad& point)
	{
		this->x = point.x;
		this->y = point.y;
		this->z = point.z;
	}
	Triad operator =(Triad& point)
	{
		x = point.x;
		y = point.y;
		z = point.z;
		return *this;
	}
	double weight()
	{
		return sqrt(x * x + y * y + z * z);
	}
	Triad operator /(double w)
	{
		return Triad(x / w, y / w, z / w);
	}
	Triad vect(Triad v)
	{
		return Triad(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);

	}

	double getX()
	{
		return x;
	}
	double getY()
	{
		return y;
	}
	double getZ()
	{
		return z;
	}
};
