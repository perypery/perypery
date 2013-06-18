#pragma once
#ifndef _RAY_H
#define _RAY_H
#include"point.h"
#include"vector3.h"
class ray
{
public:
	point vertex;
	vector3 ray_vector;
	ray(point p,vector3 v);
	ray(point p1,point p2);
	~ray(void);
};
#endif
