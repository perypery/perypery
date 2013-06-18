#include "StdAfx.h"
#include "color.h"


color::color(double a,double b,double c)
{
	this->number1=a;
	this->number2=b;
	this->number3=c;
}
void color::operator=(color c1)
{
	this->number1=c1.number1;
	this->number2=c1.number2;
	this->number3=c1.number3;
}
color color::operator*(double a)
{
	return color(number1*a,number2*a,number3*a);
}
color color::operator+(color c1)
{
	return color(this->number1+c1.number1,this->number2+c1.number2,this->number3+c1.number3);
}
color::color()
{
}
color::~color(void)
{
}
