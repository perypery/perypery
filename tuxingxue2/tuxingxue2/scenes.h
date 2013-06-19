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
	point* _rayintersect(ray r,int& objectnum);
	scenes(void);
	color trace(ray r,int depth);
};
#endif
