#pragma once
#ifndef _VECTOR3_H
#define _VECTOR3_H
class vector3//��ά��λ����
{
public:
	double x;
	double y;
	double z;
	vector3(double a,double b,double c);//������ѷǵ�λ�ĸ�Ϊ��λ��
	double operator*(vector3 t);
	vector3 operator*(double t);
	~vector3(void);
	vector3();
};
#endif
