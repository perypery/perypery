#include "StdAfx.h"
#include "cuboid.h"


cuboid::cuboid(point p0,point p1,point p2,point p3,point p4,point p5,point p6,point p7,color c)
{
	tri.push_back(Triangle(p0,p1,p4,c));//每相邻两个法向量就不同
	tri.push_back(Triangle(p5,p1,p4,c));
	tri.push_back(Triangle(p2,p1,p5,c));
	tri.push_back(Triangle(p2,p6,p5,c));
	tri.push_back(Triangle(p4,p5,p6,c));
	tri.push_back(Triangle(p4,p7,p6,c));
	tri.push_back(Triangle(p0,p3,p4,c));
	tri.push_back(Triangle(p7,p3,p4,c));
	tri.push_back(Triangle(p2,p3,p7,c));
	tri.push_back(Triangle(p2,p6,p7,c));
	tri.push_back(Triangle(p0,p1,p2,c));
	tri.push_back(Triangle(p0,p3,p2,c));
	for(int i=0;i<12;i++)
		tri[i].set(Kself,Kd,Kn,Ks,Kr,Kre,eta,is_light);
}

double cuboid::rayintersect(point&p,ray r,vector3& N,color& c)
{
	double distancemin=1e5;
	point pointtemp=point();
	vector3 vectortemp;
	color colortemp;
	int trinum=-1;
	for(int i=0;i<tri.size();i++)
	{
		double distancetemp=tri[i].rayintersect(pointtemp,r,vectortemp,colortemp);
		if(distancetemp<distancemin)
		{
			//Triangle t=Triangle();
			
			p=pointtemp;
			N=vectortemp;
			trinum=i;
			c=colortemp;
			distancemin=distancetemp;
			*Triangle::fout2<<" gengxin trinum="<<trinum;
		}
	}
	return distancemin;
}
cuboid::~cuboid(void)
{
}
