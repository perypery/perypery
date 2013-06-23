#pragma once
#ifndef __OBJECT_H
#define __OBJECT_H
#include"point.h"
#include"ray.h"
#include"color.h"
class _object
{
public:
	double Kself;//自己颜色比例
	double Kd;//漫反射比例
	int Kn;//镜面反射的n
	double Ks;//镜面反射比例
	double Kr;//递归反射系数
	double Kre;//递归折射系数
	double eta;//折射方向
	bool is_light;//在算阴影线、不继续查找、高光有用
	//virtual vector3 getN(point pointtemp)=0;
	void set(double a,double b,int c,double d,double e,double f,double g,bool is_light);
	virtual double rayintersect(point& p,ray r,vector3& N,color& c) =0;//光线求交
};

#endif