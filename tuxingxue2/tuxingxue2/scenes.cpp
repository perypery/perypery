#include "StdAfx.h"
#include "scenes.h"
#include<iostream>
#include<fstream>

#define BACKGROUND_COLOR color(255,255,255)
#define Ka 0.2     //����
#define Kself 0.2   //�Լ���ɫ
//#define Kd 0.2   //������
#define Kn 3    //���淴���n
#define Ks 0.2  //���淴��
#define Kr 0.5  //�����ϵ��
#define Kre 0.2  //�����ϵ��

scenes::scenes(void)//�����趨
{
	fout=new ofstream("2.txt");
}
point* scenes::_rayintersect(ray r,int& objectnum)//���ع��ߺͶ����������һ��//�⼸����bug
{
	point* pointtemp=NULL;
	double distancemin=100000;
	for(int i=0;i<objects.size();i++)
	{
		objects[i]->rayintersect(pointtemp,r,distancemin);//pointtemp������null�������н���//��bug
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
	pointtemp=_rayintersect(r,objectnum);//pointtempΪ��һ�����㣬objectnumΪobject��
	//��û�У�pointtempΪ�գ�objectnumΪ-1
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
	//���ǲ����Ǳ�����
	color Ia=BACKGROUND_COLOR;
	color selfcolor=((ball*)objects[objectnum])->ball_color;
	pointcolor=Ia*Ka+selfcolor*Kself;
	for(int i=0;i<lights.size();i++)//�й��ߵ�ʱ�򣬿�������������� 
	{
		ray raytemp=ray(*pointtemp,lights[i]->center);
		//rays.push_back(ray(*pointtemp,lights[i]->center));
		L.push_back(raytemp.ray_vector);
		int objectnumtemp=-1;
		_rayintersect(raytemp,objectnumtemp);
		if(objects[objectnum]->is_light)//û�б���ס
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