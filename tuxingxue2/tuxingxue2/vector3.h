#pragma once
#ifndef _VECTOR3_H
#define _VECTOR3_H
#include<iostream>
using namespace std;
class vector3//三维单位向量
{
public:
	double x;
	double y;
	double z;
	vector3(double a,double b,double c);//在这里把非单位的改为单位的
	double operator*(vector3 t);
	vector3 operator*(double t);
	friend ostream& operator<<(ostream& output,vector3& v);
	vector3 sym(vector3 v1);
	~vector3(void);
	vector3();
};
#endif
