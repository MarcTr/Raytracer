#include "../Utility/stdafx.h"
#include "Matrix.h"
#include <sstream>

using namespace Maths;

#ifndef M_PI 
#define M_PI 3.1415926535
#endif

Matrix::Matrix()
{
	// first line
	matrix[0][0] = 1;
	matrix[1][0] = 0;
	matrix[2][0] = 0;
	matrix[3][0] = 0;

	// second line
	matrix[0][1] = 0;
	matrix[1][1] = 1;
	matrix[2][1] = 0;
	matrix[3][1] = 0;

	// third line
	matrix[0][2] = 0;
	matrix[1][2] = 0;
	matrix[2][2] = 1;
	matrix[3][2] = 0;

	// fourth line
	matrix[0][3] = 0;
	matrix[1][3] = 0;
	matrix[2][3] = 0;
	matrix[3][3] = 1;
}

Vector3 Matrix::multiply(Vector3 _vector, int homogenousCoordinate)
{
	double resultX = matrix[0][0] * _vector.getX() + matrix[1][0] * _vector.getY() + matrix[2][0] * _vector.getZ() + matrix[3][0] * homogenousCoordinate;
	double resultY = matrix[0][1] * _vector.getX() + matrix[1][1] * _vector.getY() + matrix[2][1] * _vector.getZ() + matrix[3][1] * homogenousCoordinate;
	double resultZ = matrix[0][2] * _vector.getX() + matrix[1][2] * _vector.getY() + matrix[2][2] * _vector.getZ() + matrix[3][2] * homogenousCoordinate;

	Vector3 result(resultX, resultY, resultZ);
	return result;
}

double Matrix::getField(int x, int y)
{
	return matrix[x][y];
}

Matrix Matrix::multiply(Matrix _matrix)
{
	double resultMatrix[4][4];

	// first line
	resultMatrix[0][0] = matrix[0][0] * _matrix.getField(0, 0) + matrix[1][0] * _matrix.getField(0, 1) + matrix[2][0] * _matrix.getField(0, 2) + matrix[3][0] * _matrix.getField(0, 3);
	resultMatrix[1][0] = matrix[0][0] * _matrix.getField(1, 0) + matrix[1][0] * _matrix.getField(1, 1) + matrix[2][0] * _matrix.getField(1, 2) + matrix[3][0] * _matrix.getField(1, 3);
	resultMatrix[2][0] = matrix[0][0] * _matrix.getField(2, 0) + matrix[1][0] * _matrix.getField(2, 1) + matrix[2][0] * _matrix.getField(2, 2) + matrix[3][0] * _matrix.getField(2, 3);
	resultMatrix[3][0] = matrix[0][0] * _matrix.getField(3, 0) + matrix[1][0] * _matrix.getField(3, 1) + matrix[2][0] * _matrix.getField(3, 2) + matrix[3][0] * _matrix.getField(3, 3);

	// second line
	resultMatrix[0][1] = matrix[0][1] * _matrix.getField(0, 0) + matrix[1][1] * _matrix.getField(0, 1) + matrix[2][1] * _matrix.getField(0, 2) + matrix[3][1] * _matrix.getField(0, 3);
	resultMatrix[1][1] = matrix[0][1] * _matrix.getField(1, 0) + matrix[1][1] * _matrix.getField(1, 1) + matrix[2][1] * _matrix.getField(1, 2) + matrix[3][1] * _matrix.getField(1, 3);
	resultMatrix[2][1] = matrix[0][1] * _matrix.getField(2, 0) + matrix[1][1] * _matrix.getField(2, 1) + matrix[2][1] * _matrix.getField(2, 2) + matrix[3][1] * _matrix.getField(2, 3);
	resultMatrix[3][1] = matrix[0][1] * _matrix.getField(3, 0) + matrix[1][1] * _matrix.getField(3, 1) + matrix[2][1] * _matrix.getField(3, 2) + matrix[3][1] * _matrix.getField(3, 3);

	// third line
	resultMatrix[0][2] = matrix[0][2] * _matrix.getField(0, 0) + matrix[1][2] * _matrix.getField(0, 1) + matrix[2][2] * _matrix.getField(0, 2) + matrix[3][2] * _matrix.getField(0, 3);
	resultMatrix[1][2] = matrix[0][2] * _matrix.getField(1, 0) + matrix[1][2] * _matrix.getField(1, 1) + matrix[2][2] * _matrix.getField(1, 2) + matrix[3][2] * _matrix.getField(1, 3);
	resultMatrix[2][2] = matrix[0][2] * _matrix.getField(2, 0) + matrix[1][2] * _matrix.getField(2, 1) + matrix[2][2] * _matrix.getField(2, 2) + matrix[3][2] * _matrix.getField(2, 3);
	resultMatrix[3][2] = matrix[0][2] * _matrix.getField(3, 0) + matrix[1][2] * _matrix.getField(3, 1) + matrix[2][2] * _matrix.getField(3, 2) + matrix[3][2] * _matrix.getField(3, 3);

	// fourth line
	resultMatrix[0][3] = matrix[0][3] * _matrix.getField(0, 0) + matrix[1][3] * _matrix.getField(0, 1) + matrix[2][3] * _matrix.getField(0, 2) + matrix[3][3] * _matrix.getField(0, 3);
	resultMatrix[1][3] = matrix[0][3] * _matrix.getField(1, 0) + matrix[1][3] * _matrix.getField(1, 1) + matrix[2][3] * _matrix.getField(1, 2) + matrix[3][3] * _matrix.getField(1, 3);
	resultMatrix[2][3] = matrix[0][3] * _matrix.getField(2, 0) + matrix[1][3] * _matrix.getField(2, 1) + matrix[2][3] * _matrix.getField(2, 2) + matrix[3][3] * _matrix.getField(2, 3);
	resultMatrix[3][3] = matrix[0][3] * _matrix.getField(3, 0) + matrix[1][3] * _matrix.getField(3, 1) + matrix[2][3] * _matrix.getField(3, 2) + matrix[3][3] * _matrix.getField(3, 3);

	Matrix result;
	result.setMatrix(resultMatrix);
	return result;
}

void Matrix::setMatrix(double _matrix[4][4])
{
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			matrix[x][y] = _matrix[x][y];
		}
	}
}

std::string Matrix::toString()
{
	std::stringstream sstm;
	sstm << matrix[0][0] << " " << matrix[1][0] << " " << matrix[2][0] << " " << matrix[3][0] << "\n";
	sstm << matrix[0][1] << " " << matrix[1][1] << " " << matrix[2][1] << " " << matrix[3][1] << "\n";
	sstm << matrix[0][2] << " " << matrix[1][2] << " " << matrix[2][2] << " " << matrix[3][2] << "\n";
	sstm << matrix[0][3] << " " << matrix[1][3] << " " << matrix[2][3] << " " << matrix[3][3] << "\n";

	return sstm.str();
}

Matrix Matrix::invert()
{
	// Needed for inheritance
	return Matrix();
}