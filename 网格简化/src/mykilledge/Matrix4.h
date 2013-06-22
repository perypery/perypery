#ifndef MATRIX4_H_
#define MATRIX4_H_

#include <iostream>
#include "Vector4.h"
class Vector4;
class Matrix4 
{
public:
		double matrix[4][4];
		Matrix4(){memset(matrix, 0, sizeof(matrix));};
		Matrix4(const Matrix4 &m){memcpy(matrix, m.matrix, sizeof(matrix));};
		Matrix4(double *p)
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					matrix[i][j] = *(p + i * 4 + j);
		}
		Matrix4 &operator=(const Matrix4 &m)
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
				matrix[i][j] = m.matrix[i][j];
			return *this;
		}
		Matrix4 operator+(const Matrix4 &m) const
		{
			Matrix4 temp;
			memset(temp.matrix, 0, sizeof(temp.matrix));
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					temp.matrix[i][j] = matrix[i][j] + m.matrix[i][j];
			return temp;
		}
		Matrix4 operator-(const Matrix4 &m) const
		{
			Matrix4 temp;
			memset(temp.matrix, 0, sizeof(temp.matrix));
			for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				temp.matrix[i][j] = matrix[i][j] - m.matrix[i][j];
			return temp;
		}
		Vector4 operator*(const Vector4 &v) const;
		Matrix4 operator-() const
		{
			Matrix4 temp;
			memset(temp.matrix, 0, sizeof(temp.matrix));
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					temp.matrix[i][j] = -matrix[i][j];
			return temp;
		}
	};
 
#endif