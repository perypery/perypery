#pragma once
#ifndef _CAMERA_H
#define _CAMERA_H
#include"point.h"
//���������������ṩ�ӽ�λ�ã���Ϊ��ʾ��λ���ǹ̶��ģ��ı���Ǵ�С��
class camera
{
public:
	point eye;
	double display_x,display_y;
	camera(point p,double display_x,double display_y);
	~camera(void);
};
#endif
