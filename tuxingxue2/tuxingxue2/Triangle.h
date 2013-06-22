#pragma once
#include"point.h"
#include"ray.h"
#include"color.h"
#include"_object.h"
#include<fstream>
using namespace std;
class Triangle:public _object
{
public:
	static ofstream* fout2;
	point v0,v1,v2;
	color triangle_color;
	Triangle();
	Triangle(point a,point b,point c,color tc,bool is_light);
	double rayintersect(point& p,ray r,vector3& N,color& c);
	//Triangle(void);
	~Triangle(void);
};

