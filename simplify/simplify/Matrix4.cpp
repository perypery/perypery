#include"Matrix4.h"

Vector4 Matrix4::operator*(const Vector4 &v) const
{
	Vector4 temp;
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++) 
		temp.points[i] += matrix[i][j] * v.points[j];
	} 
	return temp;
}