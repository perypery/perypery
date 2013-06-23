#pragma once
#ifndef _FLOOR_H
#define _FLOOR_H
#include"_object.h"
#include"color.h"
class Floor:public _object
{
public:
	double height;
	Floor(double x);
	double rayintersect(point&p,ray r,vector3& N,color& c);
};
#endif
