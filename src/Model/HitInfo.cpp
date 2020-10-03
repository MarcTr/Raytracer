#include "../Utility/stdafx.h"
#include "HitInfo.h"

using namespace Model;

Model::HitInfo::HitInfo()
{
}

Model::HitInfo::HitInfo(
		double _distanceToIntersection, 
		Maths::Vector3 _pointOfIntersection, 
		Geometry* _hitObject
	)
	: 	distanceToIntersection(_distanceToIntersection), 
		pointOfIntersection(_pointOfIntersection), 
		hitObject(_hitObject)
{
}

double Model::HitInfo::getDistanceToIntersection()
{
	return distanceToIntersection;
}

Maths::Vector3 Model::HitInfo::getPointOfIntersection()
{
	return pointOfIntersection;
}

Model::Geometry* Model::HitInfo::getHitObject()
{
	return this->hitObject;
}

void Model::HitInfo::setUntransformedIntersection(Maths::Vector3 intersection)
{
	this->untransformedIntersection = intersection;
}

Maths::Vector3 Model::HitInfo::getUntransformedIntersection()
{
	return this->untransformedIntersection;
}

void Model::HitInfo::setPointOfIntersection(Maths::Vector3 intersection)
{
	this->pointOfIntersection = intersection;
}