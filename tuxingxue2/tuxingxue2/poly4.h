#pragma once
#ifndef _POLY4_H
#define _POLY4_H
#include"_object.h"
#include"color.h"
#include"point.h"
#include"Triangle.h"
#include<vector>
class poly4:public _object
{
public:
	vector<Triangle> tri;
	poly4(point p0,point p1,point p2,point p3,color c);//需要按顺序输入
	double rayintersect(point&p,ray r,vector3& N,color& c);
	poly4(void);
	~poly4(void);
};

#endif