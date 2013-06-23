#include "StdAfx.h"
#include "ball.h"
#include<math.h>
#include<iostream>
using namespace std;

ball::ball(point p,double r,color c)
{
	ball_color=c;
	center=p;
	radius=r;
}

double ball::rayintersect(point& p,ray r,vector3& N,color& c)//当返回的的确是个点的时候，distance是碰到的距离//distance是传入的最近距离，如果当前距离比这个距离要远，有交点就没有意义
{
	c=ball_color;
	double Loc=r.vertex.distance(center);//光线起点到距离
	double tca=(center.x-r.vertex.x)*r.ray_vector.x+(center.y-r.vertex.y)*r.ray_vector.y+(center.z-r.vertex.z)*r.ray_vector.z;//光线起点到光线离球心最近点A的距离
	double thc2=radius*radius-Loc*Loc+tca*tca;//半弦长的平方
	if(thc2<1e-2)//光线和球没有交点
		return 1e10;// NULL;
	double thc=sqrt(thc2);
	double t1=tca-thc; 
	if(t1>1e-2)//光线和球有两个交点
	{
		{
			 p=point(r.vertex.x+t1*r.ray_vector.x,r.vertex.y+t1*r.ray_vector.y,r.vertex.z+t1*r.ray_vector.z);
			 N=vector3(p.x-center.x,p.y-center.y,p.z-center.z);
			 return t1;			
		}
	}
	else 
	{
		double t2=tca+thc;
		if(t2>1e-2)//光线源在球内，只有一个交点
		{
			p=point(r.vertex.x+t2*r.ray_vector.x,r.vertex.y+t2*r.ray_vector.y,r.vertex.z+t2*r.ray_vector.z);
			N=vector3(p.x-center.x,p.y-center.y,p.z-center.z);//应该用不到
			return t2;
		}
		else//光线源在球背面，没有交点
		{
			return 1e10;//NULL;
		}
	}
}

ball::~ball(void)
{
}
	