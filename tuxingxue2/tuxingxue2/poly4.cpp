#include "StdAfx.h"
#include "poly4.h"


poly4::poly4(void)
{
}

poly4::poly4(point p0,point p1,point p2,point p3,color c)
{
	tri.push_back(Triangle(p0,p1,p2,c));
	tri.push_back(Triangle(p0,p1,p3,c));
	tri.push_back(Triangle(p0,p2,p3,c));
	tri.push_back(Triangle(p1,p2,p3,c));
}
poly4::~poly4(void)
{
}

double poly4::rayintersect(point&p,ray r,vector3& N,color& c)
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