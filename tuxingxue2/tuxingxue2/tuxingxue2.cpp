#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include"camera.h"
#include"ray.h"
#include"scenes.h"
#include<iostream>
#include"ball.h"
#include<fstream>
#include<omp.h>

using namespace std;
cv::Mat img; 
//double mx = 0, my = 0;
//int dx = 0, dy = 0, horizBar_x = 0, vertiBar_y = 0;
//bool clickVertiBar = false, clickHorizBar = false, needScroll = false;
//CvRect rect_bar_horiz, rect_bar_verti;
#define eye_x 240
#define eye_y 240
#define eye_z -2000
//img.ptr≈≈–Ú «bgr
/*
void paint(int i,int j,int a,int b,int c)
{
	img.ptr<uchar>(i)[j*3]=c;
	img.ptr<uchar>(i)[j*3+1]=b;
	img.ptr<uchar>(i)[j*3+2]=a;
}*/
void paint(int i,int j,color c)
{
	img.ptr<uchar>(i)[j*3]=c.number3;
	img.ptr<uchar>(i)[j*3+1]=c.number2;
	img.ptr<uchar>(i)[j*3+2]=c.number1;
}
int _tmain(int argc, _TCHAR* argv[])
{
	int display_x,display_y;
	display_x=480;
	display_y=480;
	img.create(display_x, display_y, CV_8UC3); 
	img.setTo(cv::Scalar(255,255,255));
	point eye(eye_x,eye_y,eye_z);
	camera cam(eye,display_x,display_y);//display_x,display_y);
	scenes scene;
	ball light1(point(200,20,3),5,color(255,255,255),true);
	scene.lights.push_back(&light1);
	ball ball1(point(130,130,200),50,color(255,0,0),false);
	ball ball2(point(300,300,200),50,color(0,255,255),false);
	scene.objects.push_back(&ball2);
	scene.objects.push_back(&ball1);
	scene.objects.push_back(&light1);
	color** antialiase;
	antialiase=new color*[display_x];
	for(int i=0;i<display_x;i++)
		antialiase[i]=new color[display_y];
#pragma omp parallel for
	for(int i=0;i<display_x;i++)
		for(int j=0;j<display_y;j++)
		{
			paint(i,j,(scene.trace(ray(eye,vector3(i-0.5-eye_x,j-0.5-eye_y,-eye_z)),2)
				+scene.trace(ray(eye,vector3(i-0.5-eye_x,j+0.5-eye_y,-eye_z)),2)
				+scene.trace(ray(eye,vector3(i-0.5-eye_x,j-eye_y,-eye_z)),2)
				+scene.trace(ray(eye,vector3(i-eye_x,j+0.5-eye_y,-eye_z)),2)
				+scene.trace(ray(eye,vector3(i+0.5-eye_x,j-eye_y,-eye_z)),2)
				+scene.trace(ray(eye,vector3(i-eye_x,j-0.5-eye_y,-eye_z)),2)
				+scene.trace(ray(eye,vector3(i-eye_x,j-eye_y,-eye_z)),2)
				+scene.trace(ray(eye,vector3(i+0.5-eye_x,j-0.5-eye_y,-eye_z)),2)
				+scene.trace(ray(eye,vector3(i+0.5-eye_x,j+0.5-eye_y,-eye_z)),2))*(1.0/9));
		}
	//int a=0;
	//cvCreateTrackbar("test","hah",&a,100);

	//int barWidth=25;
	//winWidth=barWidth+
	//rect_bar_horiz=cvRect(5,5,100,30);
	
	//IplImage image = img;
//	IplImage* out=cvCreateImage(cvGetSize(&image),IPL_DEPTH_8U,3);
	//cvSmooth(&image,out,CV_GAUSSIAN,3,3);
	cv::imshow("show", img);
	//cvRectangleR(&image,rect_bar_horiz,cvScalarAll(255),-1);
	//cvShowImage("show",&image);
	cv::waitKey(0);
	return 0;

}

/*void mouse_callback(int event,int x,int y,int flags,void* param)
{
	switch(event)
	{
	case CV_EVENT_LBUTTONDOWN:
		mx=x,my=y;
		dx=0;dy=0;
		if(x>=rect_bar_horiz.x&&x<=rect_bar_horiz.x+rect_bar_horiz.width&&y>=rect_bar_horiz.y&&y<=rect_bar_horiz.y+rect_bar_horiz.height)
		{
			clickHorizBar = true;
		}
		if(x>=rect_bar_verti.x&&x<=rect_bar_verti.x+rect_bar_verti.width&&y>=rect_bar_verti.y&&y<=rect_bar_verti.y+rect_bar_verti.height)
		{
			clickVertiBar = true;
		}
		break;
	case CV_EVENT_MOUSEMOVE: 
		if (clickHorizBar)
		{
			dx = fabs(x-mx) > 1 ? (int)(x-mx) : 0;
			dy = 0;
		}
		if (clickVertiBar)
		{
			dx = 0;
			dy = fabs(y-my) > 1 ? (int)(y-my) : 0;
		}
		mx = x, my = y;
		break; 
	case CV_EVENT_LBUTTONUP: 
		mx = x, my = y;
		dx = 0, dy = 0;
		clickHorizBar = false;
		clickVertiBar = false;
		break;  
	default:
		dx = 0, dy = 0;
		break;
	}
}*/