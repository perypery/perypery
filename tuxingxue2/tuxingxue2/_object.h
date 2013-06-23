#pragma once
#ifndef __OBJECT_H
#define __OBJECT_H
#include"point.h"
#include"ray.h"
#include"color.h"
class _object
{
public:
	double Kself;//�Լ���ɫ����
	double Kd;//���������
	int Kn;//���淴���n
	double Ks;//���淴�����
	double Kr;//�ݹ鷴��ϵ��
	double Kre;//�ݹ�����ϵ��
	double eta;//���䷽��
	bool is_light;//������Ӱ�ߡ����������ҡ��߹�����
	//virtual vector3 getN(point pointtemp)=0;
	void set(double a,double b,int c,double d,double e,double f,double g,bool is_light);
	virtual double rayintersect(point& p,ray r,vector3& N,color& c) =0;//������
};

#endif