#include "StdAfx.h"
#include "scenes.h"
#include<iostream>
#include<fstream>

#define BACKGROUND_COLOR color(0,0,0)
#define Ka 0.2     //����
#define Kself 0.2   //�Լ���ɫ
#define Kd 0.2   //������
#define Kn 8    //���淴���n
#define Ks 0.4  //���淴��
#define Kr 0.2  //�����ϵ��
#define Kre 0.2  //�����ϵ��
ofstream fout2("test");
scenes::scenes(void)//�����趨
{
	fout=new ofstream("2.txt");
}
double scenes::_rayintersect(ray r,point& p,int& objectnum,vector3& N,color& c)//���ع��ߺͶ����������һ��
{
	double distancemin=1e5;
	point pointtemp=point();
	vector3 vectortemp;
	color colortemp;
	for(int i=0;i<objects.size();i++)
	{
		double distancetemp=objects[i]->rayintersect(pointtemp,r,vectortemp,colortemp);
		if(distancetemp<distancemin)
		{
			p=pointtemp;
			N=vectortemp;
			objectnum=i;
			c=colortemp;
			distancemin=distancetemp;
		}
	}
	return distancemin;
}
color scenes::trace(ray r,int depth)
{
	*fout<<" trace start ";
	if(depth==0)
		return color(0,0,0);
	int objectnum=-1;
	vector3 N;
	color selfcolor;
	point pointtemp=point();
	if(_rayintersect(r,pointtemp,objectnum,N,selfcolor)>1e4)
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
	//*fout<<" N= "<<N<<" ";
	vector3 V=r.ray_vector*-1;//
	//*fout<<"V= "<<V;
	//vector<vector3>L;
	//���ǲ����Ǳ�����
	color Ia=BACKGROUND_COLOR;//(255,255,0)
	pointcolor=Ia*Ka+selfcolor*Kself;
	*fout<<" 1.color="<<pointcolor;
	for(int i=0;i<lights.size();i++)//�й��ߵ�ʱ�򣬿�������������� 
	{
		ray raytemp=ray(pointtemp,lights[i]->center);
	//	L.push_back(raytemp.ray_vector);
		int objectnumtemp=-1;
		point pointtemptemp=point();
		_rayintersect(raytemp,pointtemptemp,objectnumtemp,vector3(0,0,1),color(0,0,0));
		*fout<<" objectnumtemp="<<objectnumtemp;
		if(objects[objectnumtemp]->is_light)//û�б���ס
		{
			*fout<<" no dangzhu";
			*fout<<" N*raytemp.ray_vector="<<N*raytemp.ray_vector;
			pointcolor=pointcolor+((ball*)objects[objectnumtemp])->ball_color*fabs(N*raytemp.ray_vector)*Kd;
			*fout<<" 2.color="<<pointcolor;
			pointcolor=pointcolor+((ball*)objects[objectnumtemp])->ball_color*(pow(raytemp.ray_vector.sym(N)*V,Kn))*Ks;
			*fout<<" 3.color="<<pointcolor;
		}
		else
		{

		}
	}
	pointcolor=pointcolor+trace(ray(pointtemp,V.sym(N)),depth-1)*Kr;
	*fout<<endl;
	return pointcolor;
}