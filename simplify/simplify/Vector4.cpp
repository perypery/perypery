#include "Vector4.h"

Matrix4 Vector4::operator ^(const Vector4 &v) const{
	Matrix4 temp;
	memset(temp.matrix, 0, sizeof(temp.matrix));
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			temp.matrix[i][j] = points[i] * v.points[j];
		}
	return temp;
} 
Vector4 Vector4::operator*(Matrix4 &m) const {
		Vector4 temp;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) 
				temp.points[i] += points[j] * m.matrix[j][i];
		}
		return temp;
	}