#pragma once
#include"_object.h"
class polyhedron:public _object
{
public:
	polyhedron(void);
	double rayintersect(point&p,ray r,vector3& N,color& c);
	~polyhedron(void);
};

