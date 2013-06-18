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

double vector3::operator*(vector3 t)
{
	return x*t.x+y*t.y+z*t.z;
}

vector3::~vector3(void)
{
}
vector3 vector3::operator*(double t)
{
	return vector3(x*t,y*t,z*t);
}
vector3::vector3()
{
}
