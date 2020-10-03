#include "../Utility/stdafx.h"
#include "TranslationMatrix.h"

using namespace Maths;

TranslationMatrix::TranslationMatrix()
{
	this->isTranslationMatrix = true;
}

void TranslationMatrix::setTranslationX(double _x)
{
	this->matrix[3][0] = _x; 
}

void TranslationMatrix::setTranslationY(double _y)
{
	this->matrix[3][1] = _y;
}

void TranslationMatrix::setTranslationZ(double _z)
{
	this->matrix[3][2] = _z;
}


Matrix TranslationMatrix::invert()
{
	TranslationMatrix invertedMatrix;

	invertedMatrix.setTranslationX(-this->matrix[3][0]);
	invertedMatrix.setTranslationY(-this->matrix[3][1]);
	invertedMatrix.setTranslationZ(-this->matrix[3][2]);

	return invertedMatrix;
}