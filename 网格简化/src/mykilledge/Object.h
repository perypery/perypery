#ifndef OBJECT_H_
#define OBJECT_H_

#include "Vector3.h"
#include "Matrix4.h"
#include <list>
#include <map>
#include "Priority_Queue.h"

using namespace std;

struct triangles 
{
	int pt1, pt2, pt3;
	Vector3 normal;
	triangles() 
	{
		pt1 = pt2 = pt3 = 0;
	} 
	triangles(int p1, int p2, int p3,Vector3 m) 
	{
		pt1 = p1;
		pt2 = p2;
		pt3 = p3;
		normal = m;
	}
};
struct Point
{
	Vector3 point;
	set<int> linkpoints;   //相邻的点
	set<int> linkfaces;    //相邻的边
};
class Object 
{	
public:
	vector<Point> points;						// 存储所有的点
	vector<bool> validpoints;					// 判断一个点是否保留
	vector<triangles> faces;					// 存储所有的三角形面的三个顶点序号
	vector<bool> validfaces;					// 判断一个三角形面是否保留

	vector<Matrix4> Q;							// 存储所有点的Q值
	Priority_Queue<double,pair<int,int>,9991> costheap;    //优先队列
	map<pair<int,int>,pair<Vector3,double>> edge;
	vector<int>  linkvalidpoints;				// 在输出时记录对应的点
	int sizeofvalidpoints;						// 有效顶点数
	int sizeofvalidfaces;						// 有效面数
public:
	Object();									// 构造函数，将所有数据清除0
	Object(char *filename)	;					// 使用文件名为filename的obj模型文件初始化
	void Clear();								// 清除所有数据
	Vector3 Normailize(int p);					// 返回第p个三角形的法向量
	void Load(char *filename);					// 加载文件名为filename的obj模型文件
	Matrix4 ComputeQ(int p);					// 计算第p个点的矩阵Q值
	void ComputeQ();							// 计算所有点的矩阵Q值
	double Det3x3(double *matrix);				// 计算一个3x3的矩阵的行列式值
	Vector3 GetCost(int pti, int ptj,double & cos);		// 计算第pti和ptj点组成的pair的cost值
	void InitializeLinks();						// 初始化link相关的数组

	void MakeHeap();							// 初始化优先队列
	void DeleteVertex();						// 删除一个pair
	void InitializeAll(char *filename);			// 初始化全部数据
	void Write(char *filename);				// 写入obj文件
	void Check();
	bool Check(int);
//	bool sameedge(int,int);
//	bool sameface(int,int);
};
#endif;