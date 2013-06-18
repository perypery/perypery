#include "StdAfx.h"
#include "ray.h"


ray::ray(point p,vector3 v)
{
	vertex=p;
	ray_vector=v;
}
ray::ray(point p1,point p2)
{
	vertex=p1;
	ray_vector=vector3(p2.x-p1.x,p2.y-p1.y,p2.z-p1.z);
}

ray::~ray(void)
{
}
