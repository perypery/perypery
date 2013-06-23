#pragma once
#ifndef _CUBOID_H
#define _CUBOID_H
#include"Triangle.h"
#include"_object.h"
#include"color.h"
#include<vector>
#include"point.h"
class cuboid:public _object // 六面体   //空架子，核心还是三角面片
{
public:
	//point p000,p001,p010,p011,p100,p101,p110,p111;
	vector<Triangle> tri;
	cuboid(point p0,point p1,point p2,point p3,point p4,point p5,point p6,point p7,color c);//需要按顺序输入
	double rayintersect(point&p,ray r,vector3& N,color& c);
	cuboid(void);
	~cuboid(void);
};

#endif