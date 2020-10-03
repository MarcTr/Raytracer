#include "../Utility/stdafx.h"
#include "RotationMatrix.h"
#include <cmath>

using namespace Maths;

#ifndef M_PI 
#define M_PI 3.1415926535
#endif

RotationMatrix::RotationMatrix()
{
}


void RotationMatrix::setRotationX(double _rotationX)
{
	double convertedRotation = _rotationX * M_PI / 180; 

	matrix[1][1] = std::cos(convertedRotation);
	matrix[2][1] = -std::sin(convertedRotation);
	matrix[1][2] = std::sin(convertedRotation);
	matrix[2][2] = std::cos(convertedRotation);
}

void RotationMatrix::setRotationY(double _rotationY)
{
	double convertedRotation = _rotationY * M_PI / 180; 

	matrix[0][0] = std::cos(convertedRotation);
	matrix[2][0] = std::sin(convertedRotation);
	matrix[0][2] = -std::sin(convertedRotation);
	matrix[2][2] = std::cos(convertedRotation);
}

void RotationMatrix::setRotationZ(double _rotationZ)
{
	// TODO: Implement
}


Matrix RotationMatrix::invert()
{
	RotationMatrix invertedMatrix;
	invertedMatrix.setMatrix(this->matrix);
	return invertedMatrix;
}