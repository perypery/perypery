#include "StdAfx.h"
#include "scenes.h"
#include<iostream>
#include<fstream>
#include"Triangle.h"
#define BACKGROUND_COLOR color(0,0,0)
#define Ka 0.2    //背景
//ofstream fout("test");
scenes::scenes(void)//环境设定
{
//	fout=new ofstream("2.txt");
}
double scenes::_rayintersect(ray r,point& p,int& objectnum,vector3& N,color& c)//返回光线和东西们最近的一点
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
			//Triangle t=Triangle();
			p=pointtemp;
			N=vectortemp;
			objectnum=i;
			c=colortemp;
			distancemin=distancetemp;
			*Triangle::fout2<<" gengxin objectnum="<<objectnum;
		}
	}
	return distancemin;
}
color scenes::trace(ray r,int depth)
{
	*Triangle::fout2<<"           depth="<<depth;
	if(depth==0)
		return color(0,0,0);
	int objectnum=-1;
	vector3 N;
	color selfcolor;
	point pointtemp=point();
	if(_rayintersect(r,pointtemp,objectnum,N,selfcolor)>1e4)
	{
		*Triangle::fout2<<" nopoint";
		return BACKGROUND_COLOR;
	}
	*Triangle::fout2<<" point:"<<pointtemp;
	if(objectnum<0)
	{
		std::cout<<objectnum<<"wrongg"<<endl;
	}
	if(objects[objectnum]->is_light)
	{
		*Triangle::fout2<<" light "<<endl;
		return ((ball*)objects[objectnum])->ball_color;
	}
	color pointcolor=color(0,0,0);
	//*fout<<" N= "<<N<<" ";
	vector3 V=r.ray_vector*-1;//
	//*fout<<"V= "<<V;
	//vector<vector3>L;
	//这是不考虑比例的
	color Ia=BACKGROUND_COLOR;//(255,255,0)
	pointcolor=Ia*Ka+selfcolor*objects[objectnum]->Kself;
//	*fout<<" 1.color="<<pointcolor;
	for(int i=0;i<lights.size();i++)//有光线的时候，考虑漫反射和折射 
	{
		*Triangle::fout2<<" kanguang";
		ray raytemp=ray(pointtemp,lights[i]->center);
	//	L.push_back(raytemp.ray_vector);
		int objectnumtemp=-1;
		point pointtemptemp=point();
		_rayintersect(raytemp,pointtemptemp,objectnumtemp,vector3(0,0,1),color(0,0,0));
	//	*fout<<" objectnumtemp="<<objectnumtemp;
		if(objects[objectnumtemp]->is_light)//没有被挡住
		{
	//		*fout<<" no dangzhu";
	//		*fout<<" N*raytemp.ray_vector="<<N*raytemp.ray_vector;
			pointcolor=pointcolor+((ball*)objects[objectnumtemp])->ball_color*fabs(N*raytemp.ray_vector)*objects[objectnum]->Kd;
	//		*fout<<" 2.color="<<pointcolor;
			pointcolor=pointcolor+((ball*)objects[objectnumtemp])->ball_color*(pow(raytemp.ray_vector.sym(N)*V,objects[objectnum]->Kn))*objects[objectnum]->Ks;
	//		*fout<<" 3.color="<<pointcolor;
		}
		else
		{

		}
	}
	*Triangle::fout2<<" fanqian:"<<pointcolor;
//	*Triangle::fout2<<" fanray:"<<V.sym(N);
	pointcolor=pointcolor+trace(ray(pointtemp,V.sym(N)),depth-1)*objects[objectnum]->Kr;
//	*Triangle::fout2<<" fanhouzheqian:"<<pointcolor;
	double cos1=N*V;
	if(cos1<0)
		N=N*-1;
	double sin2=sqrt(1-cos1*cos1)*objects[objectnum]->eta;
	double cos2=sqrt(1-sin2*sin2);
	double sin1=sqrt(1-cos1*cos1);
	double b=-sin2/sin1;
	double a=-b*cos1-cos2;
	*Triangle::fout2<<" N="<<N<<" V="<<V;
	*Triangle::fout2<<" zheray:"<<N*a+V*b;
	pointcolor=pointcolor+trace(ray(pointtemp,N*a+V*b),depth-1)*objects[objectnum]->Kre;
	*Triangle::fout2<<" zhehou:"<<pointcolor;
	return pointcolor;
}
/*
i=341 j=148           
depth=3 gengxin objectnum=2 point:(430,66.9307,1762.38) gengxin objectnum=1 fansheqian:(66.2091,66.2091,66.2091) fansheray:-0.0503826 -0.0458931 0.997675            
depth=2 nopoint fanshehouzhesheqian:(66.2091,66.2091,66.2091) zhesheray:-0.689064 -0.033301 0.723935            
depth=2 nopoint zheshehou:(66.2091,66.2091,66.2091)
/*
i=341 j=174           
depth=3 gengxin objectnum=0 point:(344.748,171.551,74.2131) gengxin objectnum=1 fansheqian:(32.4246,45.1746,45.1746) fansheray:-0.849813 0.0586015 -0.523816            
depth=2 nopoint fanshehouzhesheqian:(32.4246,45.1746,45.1746) zhesheray:0.28778 -0.0435875 0.956704            
depth=2 gengxin objectnum=0 point:(361.512,169.012,129.946) gengxin objectnum=0 fansheqian:(0,12.75,12.75) fansheray:0.189896 0.0203764 -0.981593            
depth=1 gengxin objectnum=0 point:(372.575,170.199,72.7632) gengxin objectnum=0 fansheqian:(0,12.75,12.75) fansheray:-0.624022 0.00750769 0.781371            
depth=0 fanshehouzhesheqian:(0,12.75,12.75) zhesheray:-0.950467 0.0570027 -0.305554            
depth=0 zheshehou:(0,12.75,12.75) fanshehouzhesheqian:(0,15.3,15.3) zhesheray:0.984112 -0.0441426 -0.171975            
depth=1 gengxin objectnum=0 point:(368.633,168.692,128.701) gengxin objectnum=0 fansheqian:(0,12.75,12.75) fansheray:0.914698 -0.0336291 -0.402736            
depth=0 fanshehouzhesheqian:(0,12.75,12.75) zhesheray:0.52506 -0.000418569 -0.851065            
depth=0 zheshehou:(0,12.75,12.75) zheshehou:(0,28.05,28.05) zheshehou:(32.4246,73.2246,73.2246)




参数为0.1
i=341 j=149           
depth=3 gengxin objectnum=0 point:(345.661,144.801,92.2942) gengxin objectnum=1 fansheqian:(3.17656,15.9266,15.9266) fansheray:-0.181166 -0.452316 0.873263            
depth=2 nopoint fanshehouzhesheqian:(3.17656,15.9266,15.9266) zhesheray:0.335206 0.50411 0.795933            
depth=2 gengxin objectnum=0 point:(361.512,168.638,129.931) gengxin objectnum=0 fansheqian:(0,12.75,12.75) fansheray:0.25579 0.575663 -0.776649            
depth=1 gengxin objectnum=0 point:(373.607,195.859,93.206) gengxin objectnum=0 fansheqian:(0,12.75,12.75) fansheray:-0.459121 -0.782985 -0.419692            
depth=0 fanshehouzhesheqian:(0,12.75,12.75) zhesheray:-0.303803 -0.439804 -0.845149            
depth=0 zheshehou:(0,12.75,12.75) fanshehouzhesheqian:(0,15.3,15.3) zhesheray:0.437521 0.844107 -0.309934            
depth=1 gengxin objectnum=0 point:(370.056,185.123,123.878) gengxin objectnum=0 fansheqian:(0,12.75,12.75) fansheray:0.219305 0.515936 -0.82808            
depth=0 fanshehouzhesheqian:(0,12.75,12.75) zhesheray:0.0880912 0.29273 -0.952129            
depth=0 zheshehou:(0,12.75,12.75) zheshehou:(0,28.05,28.05) zheshehou:(3.17656,43.9766,43.9766)
*/
/*
参数为1时：
i=372 j=150           
depth=3 gengxin objectnum=2 point:(430,110.455,878.788) gengxin objectnum=1 fansheqian:(45.5558,45.5558,45.5558)           
depth=2 nopoint fanshehouzhesheqian:(45.5558,45.5558,45.5558)           
depth=2 nopoint zheshehou:(45.5558,45.5558,45.5558)
i=372 j=151           
depth=3 gengxin objectnum=0 point:(378.251,146.785,94.7092) gengxin objectnum=0 fansheqian:(0,12.75,12.75)           
depth=2 gengxin objectnum=2 point:(430,91.7164,357.535) gengxin objectnum=1 fansheqian:(90.5897,90.5897,90.5897)           
depth=1 nopoint fanshehouzhesheqian:(90.5897,90.5897,90.5897)           
depth=1 nopoint zheshehou:(90.5897,90.5897,90.5897) fanshehouzhesheqian:(18.1179,30.8679,30.8679)           
depth=2 gengxin objectnum=0 point:(361.974,168.669,129.905) gengxin objectnum=0 fansheqian:(0,12.75,12.75)           
depth=1 gengxin objectnum=0 point:(341.349,193.485,99.2229) gengxin objectnum=1 fansheqian:(9.36789,22.1179,22.1179)           
depth=0 fanshehouzhesheqian:(9.36789,22.1179,22.1179)           
depth=0 zheshehou:(9.36789,22.1179,22.1179) fanshehouzhesheqian:(1.87358,17.1736,17.1736)           
depth=1 nopoint zheshehou:(1.87358,17.1736,17.1736) zheshehou:(19.9915,48.0415,48.0415)
*/