#include "StdAfx.h"
#include "scenes.h"
#include<iostream>

#define BACKGROUND_COLOR color(255,255,255)
scenes::scenes(void)//�����趨
{
}

scenes::~scenes(void)
{
}
point* scenes::_rayintersect(ray r,int& objectnum)//���ع��ߺͶ����������һ��
{
	point* pointtemp;
	double distancemin=100000;
	for(int i=0;i<objects.size();i++)
	{
		pointtemp=objects[i]->rayintersect(r,distancemin);//pointtemp������null�������н���//��bug
		if(pointtemp!=NULL)
			objectnum=i;		
	}
	return pointtemp;
}

color scenes::trace(ray r,int depth)
{
	if(depth==0)
		return color(0,0,0);
	int objectnum=-1;
	point* pointtemp;
	pointtemp=_rayintersect(r,objectnum);//pointtempΪ��һ�����㣬objectnumΪobject��
	//��û�У�pointtempΪ�գ�objectnumΪ-1
	if(objectnum==-1)		
		return BACKGROUND_COLOR;
	if(objects[objectnum]->is_light)
		return ((ball*)objects[objectnum])->ball_color;
	color pointcolor;

	vector3 N=vector3(pointtemp->x-((ball*)objects[objectnum])->center.x,pointtemp->y-((ball*)objects[objectnum])->center.y,pointtemp->z-((ball*)objects[objectnum])->center.z);
	vector3 V=r.ray_vector*-1;//
	vector<ray>rays;
	vector<vector3>L;
	for(int i=0;i<lights.size();i++)
	{
		rays.push_back(ray(*pointtemp,lights[i]->center));
		L.push_back(rays[i].ray_vector)
		//color Ip,Id,Is;

	}
		
//	return color(255,255,255);
}