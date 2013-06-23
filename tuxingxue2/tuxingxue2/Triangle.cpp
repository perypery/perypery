#include "StdAfx.h"
#include "Triangle.h"

//ofstream fout2("test2");
 ofstream* Triangle::fout2=new ofstream("test2.txt");
Triangle::Triangle()
{
	
}

Triangle::Triangle(point a,point b,point c,color tc)
{
	//fout2=new ofstream("test2.txt");
	v0=a;
	v1=b;
	v2=c;
	triangle_color=tc;
}
double Triangle::rayintersect(point& pp,ray r,vector3& N,color& cc)    //ÐèÒªÐÞ¸Ä
{
	
	cc=triangle_color;
	double a=v0.x-v1.x,b=v0.x-v2.x,c=r.ray_vector.x,d=v0.x-r.vertex.x;
	double e=v0.y-v1.y,f=v0.y-v2.y,g=r.ray_vector.y,h=v0.y-r.vertex.y;
	double i=v0.z-v1.z,j=v0.z-v2.z,k=r.ray_vector.z,l=v0.z-r.vertex.z;
	double m=f*k-g*j,n=h*k-g*l,p=f*l-h*j;
	double q=g*i-e*k,s=e*j-f*i;
	double inv_denom=1.0/(a*m+b*q+c*s);
	double e1=d*m-b*n-c*p;
	double beta=e1*inv_denom;
	if(beta<1e-6)
	{
		*fout2<<" first";
		return 1e10;
	}
	double rr=e*l-h*i;
	double e2=a*n+d*q+c*rr;
	double gamma=e2*inv_denom;
	if(gamma<1e-6)
	{
		*fout2<<" second";
		return 1e10;
	}
	if(beta+gamma>1)
	{
		*fout2<<" third";
		return 1e10;
	}
	double e3=a*p-b*rr+d*s;
	double t=e3*inv_denom;
	if(t<1e-6)
	{
		*fout2<<" fourth";
		return 1e10;
	}
	pp=point(r.vertex.x+t*r.ray_vector.x,r.vertex.y+t*r.ray_vector.y,r.vertex.z+t*r.ray_vector.z);
	vector3 edge1,edge2;
	edge1=vector3(v0.x-v1.x,v0.y-v1.y,v0.z-v1.z);
	edge2=vector3(v0.x-v2.x,v0.y-v2.y,v0.z-v2.z);
	N=edge1.cross(edge2)*-1;
	return t;
	//vector3 edge1,edge2,dd;
	//double det;
	//double u,v,t;
	//edge1=vector3(v0.x-v1.x,v0.y-v1.y,v0.z-v1.z);
	//edge2=vector3(v0.x-v2.x,v0.y-v2.y,v0.z-v2.z);
	//dd=vector3(v0.x-r.vertex.x,v0.y-r.vertex.y,v0.z-r.vertex.z);
	//double m=

	//p=point(r.vertex.x+t*r.ray_vector.x,r.vertex.y+t*r.ray_vector.y,r.vertex.z+t*r.ray_vector.z);
	//*fout2<<" p="<<p;
	//*fout2<<" N="<<N;
	//return t;
}

Triangle::~Triangle(void)
{
}
