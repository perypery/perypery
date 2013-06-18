#include "StdAfx.h"
#include "point.h"
#include<math.h>

point::point(void)
{
}
void point::operator=(point p1)
{
	this->x=p1.x;
	this->y=p1.y;
	this->z=p1.z;
}
double point::distance(point p1)
{
	return sqrt((p1.x-x)*(p1.x-x)+(p1.y-y)*(p1.y-y)+(p1.z-z)*(p1.z-z));
}
point::point(double a,double b,double c)
{
	x=a;
	y=b;
	z=c;
}
point::~point(void)
{
}
