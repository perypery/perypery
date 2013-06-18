#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include"camera.h"
#include"ray.h"
#include"scenes.h"
#include<iostream>
#include"ball.h"
using namespace std;
//double mx = 0, my = 0;
//int dx = 0, dy = 0, horizBar_x = 0, vertiBar_y = 0;
//bool clickVertiBar = false, clickHorizBar = false, needScroll = false;
//CvRect rect_bar_horiz, rect_bar_verti;
#define eye_x 240
#define eye_y 240
#define eye_z -200
//img.ptr排序是bgr
int _tmain(int argc, _TCHAR* argv[])
{
	double display_x,display_y;
	//double eye_x,eye_y,eye_z,
	//display_x和display_y都是480
	//eye_x,eye_y,eye_z计划设定为240,240，-200
	cv::Mat img; 
	display_x=480;
	display_y=480;
	img.create(480, 480, CV_8UC3); 
	img.setTo(cv::Scalar(255,255,255));
	point eye(eye_x,eye_y,eye_z);
	camera cam(eye,display_x,display_y);//display_x,display_y);
	scenes scene;
	ball light1(point(10,200,10),50,color(255,255,0),true);
	scene.lights.push_back(&light1);
	ball ball1(point(240,240,200),100,color(0,0,0),false);
	
	ball ball2(point(400,400,200),100,color(0,0,0),false);
	scene.objects.push_back(&ball2);
	scene.objects.push_back(&ball1);
	scene.objects.push_back(&light1);
	for(int i=0;i<480;i++)
	{
		for(int j=0;j<480;j++)
		{
			//ray ra(point(i,j,0),vector3(0,0,1));
			ray ra(eye,vector3(i-eye_x,j-eye_y,-eye_z));
			color c=scene.trace(ra,1);
			img.ptr<uchar>(i)[j*3]=c.number3;
			img.ptr<uchar>(i)[j*3+1]=c.number2;
			img.ptr<uchar>(i)[j*3+2]=c.number1;
			//point* pointfirst=scene._rayintersect(ra,num);
		}
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