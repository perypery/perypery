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
	set<int> linkpoints;   //���ڵĵ�
	set<int> linkfaces;    //���ڵı�
};
class Object 
{	
public:
	vector<Point> points;						// �洢���еĵ�
	vector<bool> validpoints;					// �ж�һ�����Ƿ���
	vector<triangles> faces;					// �洢���е���������������������
	vector<bool> validfaces;					// �ж�һ�����������Ƿ���

	vector<Matrix4> Q;							// �洢���е��Qֵ
	Priority_Queue<double,pair<int,int>,9991> costheap;    //���ȶ���
	map<pair<int,int>,pair<Vector3,double>> edge;
	vector<int>  linkvalidpoints;				// �����ʱ��¼��Ӧ�ĵ�
	int sizeofvalidpoints;						// ��Ч������
	int sizeofvalidfaces;						// ��Ч����
public:
	Object();									// ���캯�����������������0
	Object(char *filename)	;					// ʹ���ļ���Ϊfilename��objģ���ļ���ʼ��
	void Clear();								// �����������
	Vector3 Normailize(int p);					// ���ص�p�������εķ�����
	void Load(char *filename);					// �����ļ���Ϊfilename��objģ���ļ�
	Matrix4 ComputeQ(int p);					// �����p����ľ���Qֵ
	void ComputeQ();							// �������е�ľ���Qֵ
	double Det3x3(double *matrix);				// ����һ��3x3�ľ��������ʽֵ
	Vector3 GetCost(int pti, int ptj,double & cos);		// �����pti��ptj����ɵ�pair��costֵ
	void InitializeLinks();						// ��ʼ��link��ص�����

	void MakeHeap();							// ��ʼ�����ȶ���
	void DeleteVertex();						// ɾ��һ��pair
	void InitializeAll(char *filename);			// ��ʼ��ȫ������
	void Write(char *filename);				// д��obj�ļ�
	void Check();
	bool Check(int);
//	bool sameedge(int,int);
//	bool sameface(int,int);
};
#endif;