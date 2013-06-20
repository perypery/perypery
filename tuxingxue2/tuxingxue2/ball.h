#pragma once
#ifndef _BALL_H
#define _BALL_H
#include"_object.h"
#include"point.h"
#include"color.h"
class ball:public _object
{
public:
	point center;
	double radius;
	color ball_color;
	double rayintersect(point&p,ray r,vector3& N,color& c);
	ball(point p,double r,color c,bool is_light);
	~ball(void);
};
#endif
