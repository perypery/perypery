#pragma once
#ifndef __OBJECT_H
#define __OBJECT_H
#include"point.h"
#include"ray.h"
class _object
{
public:
	bool is_light;//在算阴影线、不继续查找、高光有用
	virtual void rayintersect(point*& p,ray r,double& distance) =0;//光线求交
};

#endif