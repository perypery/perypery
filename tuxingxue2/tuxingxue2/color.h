#pragma once
#ifndef _COLOR_H
#define _COLOR_H
#include<iostream>
using namespace std;
class color
{
public:
	double number1;
	double number2;
	double number3;
	void operator=(color c1);
	color operator+(color c1);
	color operator*(double a);
	color();
	color(double a,double b,double c);
	~color(void);
	friend ostream& operator<<(ostream& output,color& c);
};
#endif
