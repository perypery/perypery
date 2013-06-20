#pragma once
#ifndef _POINT_H
#define _POINT_H
#include<iostream>
using namespace std;
class point
{
public:
	double x;
	double y;
	double z;
	point(void);
	void operator=(point p1);
	double distance(point p1);
	point(double a,double b,double c);
	~point(void);
	friend ostream& operator<<(ostream& output,point& p);
};
#endif
