#pragma once
#ifndef _SCENES_H
#define _SCENES_H
#include<vector>
#include"ball.h"
using namespace std;
class scenes
{
public:
	vector<ball*> lights;
	vector<_object*> objects;
	point* _rayintersect(ray r,int& objectnum);
	scenes(void);
	color trace(ray r,int depth);
};
#endif
