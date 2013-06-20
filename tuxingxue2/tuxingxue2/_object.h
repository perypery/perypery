#pragma once
#ifndef __OBJECT_H
#define __OBJECT_H
#include"point.h"
#include"ray.h"
#include"color.h"
class _object
{
public:
	bool is_light;//在算阴影线、不继续查找、高光有用
	//virtual vector3 getN(point pointtemp)=0;
	virtual double rayintersect(point& p,ray r,vector3& N,color& c) =0;//光线求交
};

#endif