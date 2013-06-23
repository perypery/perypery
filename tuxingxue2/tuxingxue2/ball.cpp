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

double ball::rayintersect(point& p,ray r,vector3& N,color& c)//�����صĵ�ȷ�Ǹ����ʱ��distance�������ľ���//distance�Ǵ����������룬�����ǰ������������ҪԶ���н����û������
{
	c=ball_color;
	double Loc=r.vertex.distance(center);//������㵽����
	double tca=(center.x-r.vertex.x)*r.ray_vector.x+(center.y-r.vertex.y)*r.ray_vector.y+(center.z-r.vertex.z)*r.ray_vector.z;//������㵽���������������A�ľ���
	double thc2=radius*radius-Loc*Loc+tca*tca;//���ҳ���ƽ��
	if(thc2<1e-2)//���ߺ���û�н���
		return 1e10;// NULL;
	double thc=sqrt(thc2);
	double t1=tca-thc; 
	if(t1>1e-2)//���ߺ�������������
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
		if(t2>1e-2)//����Դ�����ڣ�ֻ��һ������
		{
			p=point(r.vertex.x+t2*r.ray_vector.x,r.vertex.y+t2*r.ray_vector.y,r.vertex.z+t2*r.ray_vector.z);
			N=vector3(p.x-center.x,p.y-center.y,p.z-center.z);//Ӧ���ò���
			return t2;
		}
		else//����Դ�����棬û�н���
		{
			return 1e10;//NULL;
		}
	}
}

ball::~ball(void)
{
}
	