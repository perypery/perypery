#ifndef VECTOR3_H_
#define VECTOR3_H_

#include<math.h>

class Vector3
{ 
public:
	union {
		struct {
			double x;
			double y;
			double z;
		};
		double points[3];
	};
	Vector3() : x(0), y(0), z(0) {}
	Vector3(const Vector3 &v) : x(v.x), y(v.y), z(v.z) {}
	Vector3(double a, double b, double c) : x(a), y(b), z(c) {}
	Vector3(double *ptr) : x(ptr[0]), y(ptr[1]), z(ptr[2]) {}
	Vector3& operator=(const Vector3 &v) {
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
	bool operator==(const Vector3 &p) const		
	{
		return x == p.x && y == p.y && z == p.z;
	}
	Vector3 operator+(const Vector3 &v) const 
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}
	Vector3 operator-(const Vector3 &v) const 
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}
	Vector3 operator*(double l) const 
	{
		return Vector3(x * l, y * l, z * l);
	}
	Vector3 operator/(double l) const 
	{
		return Vector3(x / l, y / l, z / l);
	}
	double operator*(const Vector3 &v) const {
		return x * v.x + y * v.y + z * v.z;
	}
	Vector3 operator^(const Vector3 &v) const {
		return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
	double Length() const {
		double temp = sqrt(x*x + y*y + z*z);
		return (temp != 0) ? temp : 1.0;
	}
	Vector3 Normalize() {
		*this = *this * (1.0 / this->Length());
		return *this;
	}
	double & operator[](int p) {
		return points[p];
	}
	Vector3 operator-() const {
		return Vector3(-x, -y, -z);
	}
};

#endif