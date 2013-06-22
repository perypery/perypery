#include "StdAfx.h"
#include "Floor.h"


Floor::Floor(double x,bool is_light)
{
	height=x;
	this->is_light=is_light;
}
double Floor::rayintersect(point&p,ray r,vector3& N,color& c)
{
	double distance=(height-r.vertex.x)/r.ray_vector.x;
	if (distance<1e-2)
		return 1e10;
	else
	{
		p=point(height,r.vertex.y+distance*r.ray_vector.y,r.vertex.z+distance*r.ray_vector.z);
		if(height>r.vertex.x)
			N=vector3(1,0,0);
		else
			N=vector3(-1,0,0);
		if((int(p.y)/40+int(p.z)/40)%2)
			c=color(0,0,0);
		else
			c=color(255,255,255);
		return distance;
	}
}