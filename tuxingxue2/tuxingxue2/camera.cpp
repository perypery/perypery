#include "StdAfx.h"
#include "camera.h"


camera::camera(point p,double display_x,double display_y)
{
	eye=p;
	this->display_x=display_x;
	this->display_y=display_y;
}


camera::~camera(void)
{
}
