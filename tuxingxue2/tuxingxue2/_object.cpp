#include "StdAfx.h"
#include"_object.h"
void _object::set(double a,double b,int c,double d,double e,double f,double g,bool is_light)
{
	Kself=a;
	Kd=b;
	Kn=c;
	Ks=d;
	Kr=e;
	Kre=f;
	eta=g;
	this->is_light=is_light;
}