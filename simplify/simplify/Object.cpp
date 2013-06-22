#include "Object.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <algorithm>
#include <GL/gl.h>
#include <GL/glu.h>

#pragma comment(lib, "glu32.lib")
//#pragma comment(lib, "glaux.lib")
#pragma comment(lib, "opengl32.lib")

using namespace std;

const Matrix4 Zero;

bool debug = false;

Object::Object()									// ���캯�����������������0
{
	this->Clear();	
}
Object::Object(char *filename)						// ʹ���ļ���Ϊfilename��objģ���ļ���ʼ��
{
	this->Load(filename);
}
void Object::Clear()								// �����������
{
	points.clear();
	validpoints.clear();

	faces.clear();
	validfaces.clear();

	Q.clear();

	linkvalidpoints.clear();
	sizeofvalidfaces = 0;
	sizeofvalidpoints = 0;
}
Vector3 Object::Normailize(int p)			// ���ص�p�������εķ�����
{
	Vector3 temp;
	Vector3 v1, v2;
	v1 = points[faces[p].pt1].point - points[faces[p].pt2].point;
	v2 = points[faces[p].pt1].point - points[faces[p].pt3].point;
	temp = v1 ^ v2;							// ʹ�������߶�Ӧ�����������Ϊ������
	temp.Normalize();
	return temp;		
}

// �����ļ���Ϊfilename��objģ���ļ�
void Object::Load(char *filename)
{
	char c;
	ifstream fin(filename);
	this->Clear();							// �����������
	char tempchars[100];
	fin >> c;
	while (c != 'v') 
	{
		fin.getline(tempchars, 100);
		fin >> c;
	}
	while(c == 'v') 
	{
		Point temp;
		fin >> temp.point.x >> temp.point.y >> temp.point.z;	// ���붥������
		points.push_back(temp);				// ����¶���
		validpoints.push_back(true);		// �����¼Ӷ������Ч
		sizeofvalidpoints++;
		fin >> c;
		if(c == 'f')break;
		while(c != 'v')
		{
			fin.getline(tempchars, 100);
			
			fin >> c;
			if(c == 'f')break;
		}
	}
	//cout << "points = " << sizeofvalidpoints << endl;
	while (c == 'f') 
	{
		triangles temp;
		fin >> temp.pt1 >> temp.pt2 >> temp.pt3;			// ���������ζ�����
		if (temp.pt1 == 0 || temp.pt2 == 0 || temp.pt3 == 0) break;
		temp.pt1--;
		temp.pt2--;
		temp.pt3--;
		faces.push_back(temp);								// �����������
		validfaces.push_back(true);							// ��������������Ч
		faces[sizeofvalidfaces].normal = Normailize(sizeofvalidfaces);
		sizeofvalidfaces++;
		fin >> c;
		while (c != 'f' && c != '#') 
		{						// ����������ĸ��ʾ�ĺ���
			fin.getline(tempchars, 100);
			fin >> c;
		}
		if (c == '#') 
			break;
	}
	fin.close();
	//cout << "faces = " << faces.size() << endl;
}

void Object::InitializeLinks()						// ��ʼ��link��ص�����
{
	
	for (int i = 0; i < (int)faces.size(); i++) //���õ�Ĺ�����
	{				// �������ӹ�ϵ
		points[faces[i].pt1].linkpoints.insert(faces[i].pt2);
		points[faces[i].pt1].linkpoints.insert(faces[i].pt3);

		points[faces[i].pt2].linkpoints.insert(faces[i].pt1);
		points[faces[i].pt2].linkpoints.insert(faces[i].pt3);

		points[faces[i].pt3].linkpoints.insert(faces[i].pt1);
		points[faces[i].pt3].linkpoints.insert(faces[i].pt2);
	}
	

	for (int i = 0; i < (int)faces.size(); i++) 
	{			// ���������������ε����ӹ�ϵ
		points[faces[i].pt1].linkfaces.insert(i);
		points[faces[i].pt2].linkfaces.insert(i);
		points[faces[i].pt3].linkfaces.insert(i);
	}
	
}

Matrix4 Object::ComputeQ(int p)				// �����p����ľ���Qֵ
{ 
	Q[p] = Zero;								// ��ʼ����Ϊ0����	
	Matrix4 temp;
	int t;
	set<int>::iterator set_it;
	for (set_it = points[p].linkfaces.begin(); set_it != points[p].linkfaces.end(); set_it++) 
	{
		Vector4 plane;
		t = *set_it;
		plane.x = faces[t].normal.x;				// ��������Ϊ����ƽ��
		plane.y = faces[t].normal.y;
		plane.z = faces[t].normal.z;
		plane.p = -points[p].point * faces[t].normal;
		temp = plane ^ plane;								// ����ƽ���Ӧ����
		Q[p] = Q[p] + temp;
	}
	return Q[p];
}
void Object::ComputeQ()								// �������е�ľ���Qֵ
{	
	for (int i = 0; i < (int)points.size(); i++) 
	{
		Q.push_back(Zero);
	}
	for (int i = 0; i < (int)points.size(); i++) 
	{
		ComputeQ(i);
	}
}
double Object::Det3x3(double *matrix)					// ����һ��3x3�ľ��������ʽֵ
{											// ֱ��������ʽչ������
	int plus[3][3] = {{0, 4, 8}, {1, 5, 6}, {3, 7, 2}};
	int minus[3][3] = {{2, 4, 6}, {1, 3, 8}, {5, 7, 0}};
	double ans = 0;
	for (int i = 0; i < 3; i++) 
	{
		double temp = 1;
		for (int j = 0; j < 3; j++)
			temp *= matrix[plus[i][j]];
		ans += temp;
	}
	for (int i = 0; i < 3; i++) 
	{
		double temp = 1;
		for (int j = 0; j < 3; j++)
			temp *= matrix[minus[i][j]];
		ans -= temp;
	}
	return ans;
}
Vector3 Object::GetCost(int pti, int ptj,double & cos)		// �����pti��ptj����ɵ�pair��costֵ
{
	Matrix4 m;
	m = Q[pti] + Q[ptj];

	double Qsolve[4][10];									// ���¼���Ϊ��Cramer�������
	memset(Qsolve, 0, sizeof(Qsolve));						// [ matrix00, matrix01, matrix02 ] [ optimalv4_x ] + [ matrix03 ] = [ 0 ]
	for (int k = 0; k < 4; k++) 							// | matrix10, matrix11, matrix12 | | optimalv4_y | + | matrix13 | = | 0 |
	{														// [ matrix20, matrix21, matrix22 ] [ optimalv4_z ] + [ matrix23 ] = [ 0 ]
		for (int i = 0; i< 3; i++)							
			for (int j = 0; j < 3; j++)
				Qsolve[k][i * 3 + j] = m.matrix[i][j];
	}
	for (int k = 1; k < 4; k++)
		for (int i = 0; i < 3; i++)
			Qsolve[k][i * 3 + k - 1] = m.matrix[i][3];

	Vector4 optimalv4;
	double temp3x3 = Det3x3(Qsolve[0]);
	if (temp3x3 != 0) 											// ��ֹ����Ϊ0
	{
		optimalv4.x = -Det3x3(Qsolve[1]) / Det3x3(Qsolve[0]);
		optimalv4.y = -Det3x3(Qsolve[2]) / Det3x3(Qsolve[0]);
		optimalv4.z = -Det3x3(Qsolve[3]) / Det3x3(Qsolve[0]);
	}
	else 
	{
		optimalv4.x = optimalv4.y = optimalv4.z = 0;
	}
	optimalv4.p = 1;

	double cost;
	cost = optimalv4 * m * optimalv4;					
	Vector3 best;
	cos = fabs(cost);
	best.x = optimalv4.x;
	best.y = optimalv4.y;
	best.z = optimalv4.z;
	return best;
}

void Object::MakeHeap()								// ��ʼ�����ȶ���
{
	double cost = 0.0;
	set<int>::iterator set_it;
	for (int i = 0; i < (int)points.size(); i++) 
	{
		for (set_it = points[i].linkpoints.begin(); set_it != points[i].linkpoints.end(); set_it ++) 
		{
			if(i<*set_it)								// ȷ��ÿһ��pairֻ����һ��
			{
			Vector3 temp = GetCost(i,*set_it,cost);	// ���һ��pair
			costheap.push(cost,pair<int,int>(i,*set_it));										// ��pair�������
			edge[pair<int,int>(i,*set_it)] = pair<Vector3,double>(temp,cost);
			}
		}
	}
}

// ��ʼ��ȫ������
void Object::InitializeAll(char *filename)
{
	//cout << filename << endl;
	Load(filename);
	InitializeLinks();
	ComputeQ();
	MakeHeap();
	Check();
}

//��鶥�����Ƭ�����Ϸ���
void Object::Check()
{
	for(int i =0;i<(int)points.size();i++)
	{

		if(!this->Check(i)){
		return;}
	}
}
bool Object::Check(int i)
{
		if((int)points[i].linkfaces.size()>(int)points[i].linkpoints.size())  //������ȹ�����࣬bug
		{
			cout<<(int)points[i].linkfaces.size()<<" "<<(int)points[i].linkpoints.size()<<endl;
			cout<<"point:";
			set<int>::iterator set_it;
			for (set_it = points[i].linkpoints.begin(); set_it != points[i].linkpoints.end(); set_it++) 
			{					
				cout<<*set_it<<" ";
			}
			cout<<endl;
		return false;
		}
		return true;
}

void Object::DeleteVertex()							// ɾ��һ��pair
{													//����һ�����ã���Ҫ��ĳ���Ѿ�ɾ���ĵ�ʱ���õ��µ㡣

	pair<int,int> vbest = costheap.pop().second;
	Point temppoint;
	temppoint.point = edge[vbest].first;//û�д����µ㣬ֱ�Ӱ�һ���ɵ�ȡ����������һ�����޸ĺܶණ��
	
	points.push_back(temppoint);
	validpoints.push_back(true);
	sizeofvalidpoints++;
	
	int todelete1 = vbest.first;
	int todelete2 = vbest.second;		
	validpoints[todelete1] = false;
	validpoints[todelete2] = false;	
	sizeofvalidpoints-=2;
	
	std::vector<int> sharefaces;
	set<int>::iterator set_i;
	set<int>::iterator set_j;
	set<int>::iterator set_k;
	//ɾ���˻�����Ƭ
	for (set_i = points[todelete1].linkfaces.begin(); set_i != points[todelete1].linkfaces.end(); set_i++)
		for (set_j = points[todelete2].linkfaces.begin(); set_j != points[todelete2].linkfaces.end(); set_j++)
			if (*set_i == *set_j) 
			{	
				validfaces[*set_i] = false;			
				int c =  faces[*set_i].pt1 + faces[*set_i].pt2 + faces[*set_i].pt3 - todelete1 - todelete2;

				for (set_k = points[c].linkfaces.begin(); set_k != points[c].linkfaces.end();)
				{
					if (*set_i == *set_k) 
					{
						points[c].linkfaces.erase(set_k++);
					}
					else set_k++;
				}
				sizeofvalidfaces--;
			}
	//��δ�˻�����Ƭ���ӵ��µĵ���
	for (set_i = points[todelete1].linkfaces.begin(); set_i != points[todelete1].linkfaces.end(); set_i++) 
	{					
		if (validfaces[*set_i]) 
		{							
			points.rbegin()->linkfaces.insert(*set_i);			
			if (faces[*set_i].pt1 == todelete1) 
			{			
				faces[*set_i].pt1 = points.size() - 1;
			}
			else if (faces[*set_i].pt2 == todelete1) 
			{
				faces[*set_i].pt2 = points.size() - 1;
			} 
			else if (faces[*set_i].pt3 == todelete1) 
			{
				faces[*set_i].pt3 = points.size() - 1;
			}
			else 
			{
				cout<<"error1"<<endl;
				system("pause");
			}
			faces[*set_i].normal = Normailize(*set_i);	
		}
	}
	for (set_i = points[todelete2].linkfaces.begin(); set_i != points[todelete2].linkfaces.end(); set_i++) 
	{					
		if (validfaces[*set_i]) 
		{							
			points.rbegin()->linkfaces.insert(*set_i);		
			if (faces[*set_i].pt1 == todelete2) 
			{			
				faces[*set_i].pt1 = points.size() - 1;
			} 
			else if (faces[*set_i].pt2 == todelete2) 
			{
				faces[*set_i].pt2 = points.size() - 1;
			} 
			else if (faces[*set_i].pt3 == todelete2) 
			{
				faces[*set_i].pt3 = points.size() - 1;
			}
			else 
			{
				cout<<"error2"<<endl;
				system("pause");
			}
			faces[*set_i].normal = Normailize(*set_i);	
		}
	}

	Q.push_back(Zero);
	ComputeQ(Q.size() - 1);

	//����Χ�������ӵ��µ���
	set<int> ano;
	int anopoint;
	set<int>::iterator set_it;
	for (set_it = points[todelete1].linkpoints.begin(); set_it != points[todelete1].linkpoints.end(); set_it++) 
	{					
		anopoint = *set_it;
		if (validpoints[anopoint]) 
		{
			ano.insert(anopoint);
			points.rbegin()->linkpoints.insert(anopoint);
			points[anopoint].linkpoints.insert(points.size()-1);
		}
	}
	for (set_it = points[todelete2].linkpoints.begin(); set_it != points[todelete2].linkpoints.end(); set_it++) 
	{			
		anopoint = *set_it;
		if (validpoints[anopoint]) 
		{
			ano.insert(anopoint);
			points.rbegin()->linkpoints.insert(anopoint);
			points[anopoint].linkpoints.insert(points.size()-1);
		}
	}


	for (set_it = points[todelete1].linkpoints.begin(); set_it != points[todelete1].linkpoints.end(); set_it++)
	{
		if(debug){cout<<"	de1	"<<min(todelete1,*set_it)<<" de2  "<<max(todelete1,*set_it)<<endl;}
		if(!(costheap.deleteItem(costheap.query(edge[pair<int,int>(min(todelete1,*set_it),max(todelete1,*set_it))].second,pair<int,int>(min(todelete1,*set_it),max(todelete1,*set_it))))))
		{
			if(debug){cout<<"	faile1 "<<points.size()<<endl;}
		}
		if(!edge.erase(pair<int,int>(min(todelete1,*set_it),max(todelete1,*set_it))))
		{
			if(debug){cout<<"	failed2 "<<points.size()<<endl;}
		}
	}
	for (set_it = points[todelete2].linkpoints.begin(); set_it != points[todelete2].linkpoints.end(); set_it++)
	{
		if(debug){cout<<"	de3	"<<min(todelete2,*set_it)<<" de4  "<<max(todelete2,*set_it)<<endl;}
		if(!(costheap.deleteItem(costheap.query(edge[pair<int,int>(min(todelete2,*set_it),max(todelete2,*set_it))].second,pair<int,int>(min(todelete2,*set_it),max(todelete2,*set_it))))))
		{
			if(debug){cout<<"	faile3 "<<points.size()<<endl;}
		}
		if(!edge.erase(pair<int,int>(min(todelete2,*set_it),max(todelete2,*set_it))))
		{
			if(debug){cout<<"	failed4 "<<points.size()<<endl;}
		}
	}
	//�����µ�cost
	double tempcost=0.0;
	for (set_it = ano.begin(); set_it != ano.end(); set_it++) 
	{			
		Vector3 tempvec = GetCost(points.size() - 1, *set_it,tempcost);
		costheap.push(tempcost,pair<int,int>(*set_it,points.size()-1));
		edge[pair<int,int>(*set_it,points.size()-1)]= pair<Vector3,double>(tempvec,tempcost);
	}
}
/*
bool Object::sameedge(int i,int j)
{
	if(faces[i].pt1 ==faces[j].pt1 && faces[i].pt2 == faces[j].pt2)return true;
	if(faces[i].pt1 ==faces[j].pt2 && faces[i].pt2 == faces[j].pt3)return true;
	if(faces[i].pt1 ==faces[j].pt3 && faces[i].pt2 == faces[j].pt1)return true;
	if(faces[i].pt2 ==faces[j].pt1 && faces[i].pt3 == faces[j].pt2)return true;
	if(faces[i].pt2 ==faces[j].pt2 && faces[i].pt3 == faces[j].pt3)return true;
	if(faces[i].pt2 ==faces[j].pt3 && faces[i].pt3 == faces[j].pt1)return true;
	return false;
}*/
/*
bool Object::sameface(int i,int j)
{
	int a1=faces[i].pt1;
	int a2=faces[i].pt2;
	int a3=faces[i].pt3;
	int b1=faces[j].pt1;
	int b2=faces[j].pt2;
	int b3=faces[j].pt3;
	if((a1+a2+a3)!=(b1+b2+b3))return false;
	if(min(a1,min(a2,a3)) != min(b1,min(b2,b3)))return false;
	if(max(a1,max(a2,a3)) != max(b1,max(b2,b3)))return false;
	return true;
}*/

// д��obj�ļ�
void Object::Write(char *filename)	
{
	//cout<<"start outputing"<<endl;
	char space = ' ';
	int current = 0;
	for (int i = 0; i < (int)points.size(); i++) 
	{
		linkvalidpoints.push_back(-1);
		if (validpoints[i]) 
		{
			*linkvalidpoints.rbegin() = ++current;
		}
	}
	std::ofstream fout(filename);
	fout << '#' << space << sizeofvalidpoints << space << sizeofvalidfaces << std::endl;
	for (int i = 0; i < (int)points.size(); i++)
		if (validpoints[i]) 
			fout << 'v' << space << points[i].point.x << space << points[i].point.y << space << points[i].point.z << std::endl;
	for (int i = 0; i < (int)faces.size(); i++)
		if (validfaces[i])
			fout << 'f' << space << linkvalidpoints[faces[i].pt1] << space << linkvalidpoints[faces[i].pt2] << space << linkvalidpoints[faces[i].pt3] << std::endl;
	fout.close();
	//cout<<"outputing finish!"<<endl;
}