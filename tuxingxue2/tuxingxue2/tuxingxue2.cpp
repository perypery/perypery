#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include"camera.h"
#include"ray.h"
#include"scenes.h"
#include<iostream>
#include"ball.h"
#include<fstream>
#include<omp.h>
#include"Floor.h"
#include"cuboid.h"
#include"Triangle.h"
#include"poly4.h"
using namespace std;
cv::Mat img; 
#define eye_x 240
#define eye_y 240
#define eye_z -2000
#define depth 3
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
	ball light1(point(20,240,26),5,color(255,255,255));
	light1.set(0.2,0.2,8,0.3,0.2,0.2,0.2,true);
	//ball light2(point(360,340,20),5,color(255,255,255));
	//light2.set(0.2,0.2,8,0.3,0.2,0.2,0.2,true);
	scene.lights.push_back(&light1);
//	scene.lights.push_back(&light2);
	ball ball1(point(360,370,100),30,color(0,0,0));//Í¸Ã÷
	ball1.set(0.05,0.05,8,0.05,1,1,0.1,false);
	poly4 po1(point(150,150,100),point(200,100,100),point(200,200,200),point(220,200,80),color(50,205,50));
	po1.set(0.2,0.2,8,0.3,0.4,0.5,0.2,false);
	ball ball2(point(360,290,100),30,color(255,0,0));
	ball2.set(0.2,0.2,8,0.3,0.2,0.1,0.2,false);
	cuboid cub1(point(400,100,30),point(420,140,50),point(400,160,30),point(380,120,10),point(340,100,90),point(360,140,110),point(340,160,90),point(320,120,70),color(0,155,255));
	cub1.set(0.2,0.2,8,0.3,0.4,0.5,0.2,false);
	scene.objects.push_back(&po1);
	Floor floor1(430);
	floor1.set(0.2,0.2,8,0.3,0.2,0.2,0.2,false);
	scene.objects.push_back(&ball2);
	scene.objects.push_back(&ball1);
//	scene.objects.push_back(&light2);
	scene.objects.push_back(&light1);
	scene.objects.push_back(&cub1);
	scene.objects.push_back(&floor1);
#pragma omp parallel for
	for(int i=0;i<display_x;i++)
		for(int j=0;j<display_y;j++)
		{
			*Triangle::fout2<<"i="<<i<<" j="<<j;
			//paint(i,j,scene.trace(ray(eye,vector3(i-eye_x,j-eye_y,-eye_z)),depth));
			//paint(i,j,scene.trace(ray(point(i,j,0),vector3(0,0,1)),3));
			paint(i,j,(scene.trace(ray(eye,vector3(i-0.5-eye_x,j-0.5-eye_y,-eye_z)),depth)
				+scene.trace(ray(eye,vector3(i-0.5-eye_x,j+0.5-eye_y,-eye_z)),depth)
				+scene.trace(ray(eye,vector3(i-0.5-eye_x,j-eye_y,-eye_z)),depth)
				+scene.trace(ray(eye,vector3(i-eye_x,j+0.5-eye_y,-eye_z)),depth)
				+scene.trace(ray(eye,vector3(i+0.5-eye_x,j-eye_y,-eye_z)),depth)
				+scene.trace(ray(eye,vector3(i-eye_x,j-0.5-eye_y,-eye_z)),depth)
				+scene.trace(ray(eye,vector3(i-eye_x,j-eye_y,-eye_z)),depth)
				+scene.trace(ray(eye,vector3(i+0.5-eye_x,j-0.5-eye_y,-eye_z)),depth)
				+scene.trace(ray(eye,vector3(i+0.5-eye_x,j+0.5-eye_y,-eye_z)),depth))*(1.0/9));
			*Triangle::fout2<<endl;
		}
	cv::imshow("show", img);
	cv::waitKey(0);
	return 0;

}