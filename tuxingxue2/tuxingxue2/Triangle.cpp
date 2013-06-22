#include "StdAfx.h"
#include "Triangle.h"

//ofstream fout2("test2");
 ofstream* Triangle::fout2=new ofstream("test2.txt");
Triangle::Triangle()
{
	
}

Triangle::Triangle(point a,point b,point c,color tc,bool is_light)
{
	//fout2=new ofstream("test2.txt");
	v0=a;
	v1=b;
	v2=c;
	triangle_color=tc;
	this->is_light=is_light;
}
double Triangle::rayintersect(point& p,ray r,vector3& N,color& c)
{
	
	c=triangle_color;
	vector3 edge1,edge2,tvec,pvec,qvec;
	double det;
	double u,v,t;
	edge1=vector3(v1.x-v0.x,v1.y-v0.y,v1.z-v0.z);
	edge2=vector3(v2.x-v0.x,v2.y-v0.y,v2.z-v0.z);
	pvec=r.ray_vector.cross(edge2);
	det=edge1*pvec;
	if(det<1e-2)
		return 1e10;
	tvec=vector3(r.vertex.x-v0.x,r.vertex.y-v0.y,r.vertex.z-v0.z);
	u=tvec*pvec;
	if(u<1e-2||u>det)
		return 1e10;
	qvec=tvec.cross(edge1);
	v=r.ray_vector*qvec;
	if(v<1e-2||u+v>det)
		return 1e10;
	t=edge2*qvec;
	t/=det;
	u/=det;
	v/=det;
	N=edge1.cross(edge2);
	p=point(r.vertex.x+t*r.ray_vector.x,r.vertex.y+t*r.ray_vector.y,r.vertex.z+t*r.ray_vector.z);
	*fout2<<" p="<<p;
	*fout2<<" N="<<N;
	return t;
}

Triangle::~Triangle(void)
{
}
