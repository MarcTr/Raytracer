#include "../Utility/stdafx.h"
#include "Geometry.h"
#include "HitInfo.h"

using namespace Model;

Geometry::Geometry()
{
}

RGBType Geometry::calculateMaterial(
		Model::HitInfo hitInfo, 
		Model::Light light1, 
		Maths::Vector3 rayOrigin
	)
{

	if (materials.size() == 0)
		return color;
	
	RGBType currentPixelInfo;
	for (Material* material : materials)
	{
		RGBType currentMaterial = material->calculateMaterial(hitInfo, light1, rayOrigin);
		currentPixelInfo.r += currentMaterial.r;
		currentPixelInfo.g += currentMaterial.g;
		currentPixelInfo.b += currentMaterial.b;
	}

	return currentPixelInfo;
}


void Geometry::setColor(RGBType _color)
{
	this->color = _color;
}

void Geometry::transform(Matrix* _transformationMatrix)
{
	this->transformationMatrix = _transformationMatrix->multiply(this->transformationMatrix);
	this->invertedMatrix = this->invertedMatrix.multiply(_transformationMatrix->invert());

	isTransformed = true;
}

double Geometry::getIntersectionDistance(Ray ray)
{
	return -1;
}

void Geometry::setIsReflective(bool _isReflective)
{
	this->isReflective = _isReflective;
}

void Geometry::setIsRefractive(bool _isRefractive)
{
	this->isRefractive = _isRefractive;
}

bool Geometry::getIsRefractive()
{
	return this->isRefractive;
}

bool Geometry::getIsReflective()
{
	return this->isReflective;
}

Vector3 Geometry::getNormal(Vector3 hitPoint)
{
	return Vector3(0, 1, 0);
}

RGBType Geometry::getColor()
{
	return this->color;
}

std::vector<Material*> Geometry::getMaterials()
{
	return this->materials;
}

void Geometry::addMaterial(Material* _material)
{
	this->materials.push_back(dynamic_cast<Material*>(_material));
}

Matrix Geometry::getTransformationMatrix()
{
	return this->transformationMatrix;
}

Matrix Geometry::getInvertedTransformationMatrix()
{
	return this->invertedMatrix;
}

bool Geometry::getIsTransformed()
{
	return this->isTransformed;
}

void Geometry::setIsLight(bool _isLight)
{
	this->isLight = _isLight;
}

bool Geometry::getIsLight()
{
	return isLight;
}