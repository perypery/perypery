#pragma once
#ifndef __OBJECT_H
#define __OBJECT_H
#include"point.h"
#include"ray.h"
class _object
{
public:
	bool is_light;//������Ӱ�ߡ����������ҡ��߹�����
	virtual point* rayintersect(ray r,double& distance) =0;//������
};

#endif