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
ofstream fout2("test");
scenes::scenes(void)//环境设定
{
	fout=new ofstream("2.txt");
}
double scenes::_rayintersect(ray r,point& p,int& objectnum)//返回光线和东西们最近的一点//这几个有bug
{
	double distancemin=1e5;
	//int objectnum=-1;
	point pointtemp=point();
	for(int i=0;i<objects.size();i++)
	{
		double distancetemp=objects[i]->rayintersect(pointtemp,r);
		if(distancetemp<distancemin)
		{
			p=pointtemp;
			objectnum=i;
			distancemin=distancetemp;
		}
	}
	return distancemin;
}
	/*
	point* pointtemp=NULL;
	double distancemin=100000;
	for(int i=0;i<objects.size();i++)
	{
		point* pointtemptemp=NULL;
		objects[i]->rayintersect(pointtemptemp,r,distancemin);//pointtemp可能是null，尽管有交点//有bug
		if(pointtemptemp!=NULL)
			fout2<<" point: x="<<pointtemptemp->x<<" y="<<pointtemptemp->y<<" z="<<pointtemptemp->z<<endl;
		if(pointtemptemp!=NULL)
		{
			
			//*pointtemp=*pointtemptemp;
			
			//std::cout<<"1";
			objectnum=i;
		}
		//else 
			//std::cout<<"2";
	}
	
	return pointtemp;
}*/

color scenes::trace(ray r,int depth)
{

	*fout<<" trace start ";
	if(depth==0)
		return color(0,0,0);
	int objectnum=-1;
	point pointtemp=point();
	if(_rayintersect(r,pointtemp,objectnum)>1e4)
	{
		*fout<<"background"<<endl;
		return BACKGROUND_COLOR;
	}
	*fout<<"objectnum="<<objectnum;
	if(objectnum<0)
	{
		std::cout<<objectnum<<"wrongg"<<endl;
	}
	if(objects[objectnum]->is_light)
	{
		*fout<<" light "<<endl;
		return ((ball*)objects[objectnum])->ball_color;
	}
	color pointcolor=color(0,0,0);
		

//	if(pointtemp==NULL)
//	{
//		std::cout<<"wrong";
//		exit(0);
//	}
	*fout<<" point: x="<<pointtemp.x<<" y="<<pointtemp.y<<" z="<<pointtemp.z;
	vector3 N=vector3(pointtemp.x-((ball*)objects[objectnum])->center.x,pointtemp.y-((ball*)objects[objectnum])->center.y,pointtemp.z-((ball*)objects[objectnum])->center.z);
	*fout<<" N= "<<N<<" ";
	vector3 V=r.ray_vector*-1;//
	*fout<<"V= "<<V<<endl;
//	vector<ray>rays;
	vector<vector3>L;
	//这是不考虑比例的
	color Ia=BACKGROUND_COLOR;
	color selfcolor=((ball*)objects[objectnum])->ball_color;
	pointcolor=Ia*Ka+selfcolor*Kself;
	for(int i=0;i<lights.size();i++)//有光线的时候，考虑漫反射和折射 
	{
		ray raytemp=ray(pointtemp,lights[i]->center);
		//rays.push_back(ray(*pointtemp,lights[i]->center));
		L.push_back(raytemp.ray_vector);
		int objectnumtemp=-1;
		point pointtemptemp=point();
		_rayintersect(raytemp,pointtemptemp,objectnumtemp);
		//_rayintersect(raytemp,objectnumtemp);
		if(objects[objectnumtemp]->is_light)//没有被挡住
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