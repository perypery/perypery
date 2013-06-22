#ifndef VECTOR4_H_
#define VECTOR4_H_

#include<math.h>
#include"Matrix4.h"
 
class Matrix4;

class Vector4
{
public:
	union {
		struct {
			double x;
			double y;
			double z;
			double p;
		};
		double points[4];
	};
	Vector4() : x(0), y(0), z(0), p(0) {}
	Vector4(const Vector4 &v) : x(v.x), y(v.y), z(v.z), p(v.p) {}
	Vector4(double a, double b, double c, double d) : x(a), y(b), z(c), p(d) {}
	Vector4(double *ptr) : x(ptr[0]), y(ptr[1]), z(ptr[2]), p(ptr[3]) {}
	Vector4& operator=(const Vector4 &v) {
		x = v.x;
		y = v.y;
		z = v.z;
		p = v.p;
		return *this;
	}
	Vector4 operator+(const Vector4 &v) const 
	{
		return Vector4(x + v.x, y + v.y, z + v.z, p + v.p);
	}
	Vector4 operator-(const Vector4 &v) const 
	{
		return Vector4(x - v.x, y - v.y, z - v.z, p - v.p);
	}
	Vector4 operator*(double l) const 
	{
		return Vector4(x * l, y * l, z * l, p * l);
	}
	Vector4 operator*(Matrix4 &m) const;
	
	Vector4 operator/(double l) const 
	{
		return Vector4(x / l, y / l, z / l, p / l);
	}
	double operator*(const Vector4 &v) const {
		return x * v.x + y * v.y + z * v.z + p * v.p;
	}
	Matrix4 operator^(const Vector4 &v) const ;
	Vector4 Normalize() {
		*this = *this / p;
		return *this;
	}
	double & operator[](int p) {
		return points[p];
	}
	Vector4 operator-() const {
		return Vector4(-x, -y, -z, -p);
	}
};

#endif