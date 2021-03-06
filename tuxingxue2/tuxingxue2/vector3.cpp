#include "StdAfx.h"
#include "vector3.h"
#include<math.h>
vector3::vector3(double a,double b,double c)
{
	x=a;
	y=b;
	z=c;
	double temp;
	temp=a*a+b*b+c*c;
	if(temp>1+1e-2||temp<1-1e-2)
	{
		temp=sqrt(temp);
		x=x/temp;
		y=y/temp;
		z=z/temp;
	}
}
vector3 vector3::sym(vector3 v1)//V关于N的对称就是2（N*V）*N-V
{
	double k=2*(this->x*v1.x+this->y*v1.y+this->z*v1.z)/(v1.x*v1.x+v1.y*v1.y+v1.z*v1.z);
	return vector3(v1.x*k-this->x,v1.y*k-this->y,v1.z*k-this->z);
}
double vector3::operator*(vector3 t)
{
	return x*t.x+y*t.y+z*t.z;
}
ostream& operator<<(ostream& output,vector3& v)
{
	output<<v.x<<" "<<v.y<<" "<<v.z<<" ";
	return output;
}
vector3 vector3::operator*(double t)
{
	return vector3(x*t,y*t,z*t);
}
vector3 vector3::operator-(vector3 t)
{
	return vector3(x-t.x,y-t.y,z-t.z);
}
vector3 vector3::operator+(vector3 t)
{
	return vector3(x+t.x,y+t.y,z+t.z);
}
vector3::vector3()
{
}
vector3 vector3::cross(vector3 t)//可能有叉乘出的方向问题
{
	return vector3(y*t.z-z*t.y,z*t.x-x*t.z,x*t.y-y*t.x);
}