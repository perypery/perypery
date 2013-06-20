#pragma once
#ifndef _SCENES_H
#define _SCENES_H
#include<vector>
#include"ball.h"
#include<fstream>
using namespace std;
class scenes
{
public:
	ofstream* fout;
	vector<ball*> lights;
	vector<_object*> objects;
	double _rayintersect(ray r,point& p,int& objectnum,vector3& N,color& c);
	scenes(void);
	color trace(ray r,int depth);
};
#endif
