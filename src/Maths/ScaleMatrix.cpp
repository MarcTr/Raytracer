#include "../Utility/stdafx.h"
#include "ScaleMatrix.h"

using namespace Maths;

ScaleMatrix::ScaleMatrix()
{
}

void ScaleMatrix::setScaleX(double _x)
{
	matrix[0][0] = _x;	
}

void ScaleMatrix::setScaleY(double _y)
{
	matrix[1][1] = _y;
}

void ScaleMatrix::setScaleZ(double _z)
{
	matrix[2][2] = _z;
}


Matrix ScaleMatrix::invert()
{
	ScaleMatrix invertedMatrix;

	invertedMatrix.setScaleX(1 / this->matrix[0][0]);
	invertedMatrix.setScaleY(1 / this->matrix[1][1]);
	invertedMatrix.setScaleZ(1 / this->matrix[2][2]);

	return invertedMatrix;
}