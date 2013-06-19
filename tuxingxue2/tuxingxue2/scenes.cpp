#include "StdAfx.h"
#include "scenes.h"
#include<iostream>
#include<fstream>

#define BACKGROUND_COLOR color(255,255,255)
#define Ka 0.2     //背景
#define Kself 0.2   //自己颜色
//#define Kd 0.2   //漫反射
#define Kn 3    //镜面反射的n
#define Ks 0.2  //镜面反射
#define Kr 0.5  //反射的系数
#define Kre 0.2  //折射的系数

scenes::scenes(void)//环境设定
{
	fout=new ofstream("2.txt");
}
point* scenes::_rayintersect(ray r,int& objectnum)//返回光线和东西们最近的一点//这几个有bug
{
	point* pointtemp=NULL;
	double distancemin=100000;
	for(int i=0;i<objects.size();i++)
	{
		objects[i]->rayintersect(pointtemp,r,distancemin);//pointtemp可能是null，尽管有交点//有bug
		if(pointtemp!=NULL)
		{
			//std::cout<<"1";
			objectnum=i;
		}
		//else 
			//std::cout<<"2";
	}
	return pointtemp;
}

color scenes::trace(ray r,int depth)
{
	
	*fout<<" trace start ";
	if(depth==0)
		return color(0,0,0);
	int objectnum=-1;
	point* pointtemp;
	pointtemp=_rayintersect(r,objectnum);//pointtemp为第一个交点，objectnum为object数
	//若没有，pointtemp为空，objectnum为-1
	if(objectnum==-1)	
	{

		return BACKGROUND_COLOR;
	}
	if(objects[objectnum]->is_light)
		return ((ball*)objects[objectnum])->ball_color;
	color pointcolor=color(0,0,0);
	if(pointtemp==NULL)
	{
		std::cout<<"wrong";
		exit(0);
	}
	vector3 N=vector3(pointtemp->x-((ball*)objects[objectnum])->center.x,pointtemp->y-((ball*)objects[objectnum])->center.y,pointtemp->z-((ball*)objects[objectnum])->center.z);
	vector3 V=r.ray_vector*-1;//
//	vector<ray>rays;
	vector<vector3>L;
	//这是不考虑比例的
	color Ia=BACKGROUND_COLOR;
	color selfcolor=((ball*)objects[objectnum])->ball_color;
	pointcolor=Ia*Ka+selfcolor*Kself;
	for(int i=0;i<lights.size();i++)//有光线的时候，考虑漫反射和折射 
	{
		ray raytemp=ray(*pointtemp,lights[i]->center);
		//rays.push_back(ray(*pointtemp,lights[i]->center));
		L.push_back(raytemp.ray_vector);
		int objectnumtemp=-1;
		_rayintersect(raytemp,objectnumtemp);
		if(objects[objectnum]->is_light)//没有被挡住
		{
			pointcolor=pointcolor+((ball*)objects[objectnum])->ball_color*(N*raytemp.ray_vector)*(0.9,0.1,0.1);
			pointcolor=pointcolor+((ball*)objects[objectnum])->ball_color*(pow(raytemp.ray_vector.sym(N)*V,Kn))*Ks;
		}
		else
		{

		}
	}
//	pointcolor=pointcolor+trace(ray(*pointtemp,V.sym(N)),depth-1)*Kr;
	return pointcolor;
}