#pragma once
#ifndef _CAMERA_H
#define _CAMERA_H
#include"point.h"
//照相机类的作用是提供视角位置（因为显示屏位置是固定的，改变的是大小）
class camera
{
public:
	point eye;
	double display_x,display_y;
	camera(point p,double display_x,double display_y);
	~camera(void);
};
#endif
