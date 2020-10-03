#include "../Utility/stdafx.h"
#include "Plane.h"

using namespace Model;

Plane::Plane()
{
	this->distanceToOrigin = 0;

	Vector3 planeNormal(0, 0, -1);
	this->normal = planeNormal;
}

	
double Plane::getIntersectionDistance(Ray ray)
{
	
	if (this->getIsTransformed())
	{
		ray.setOrigin(this->getInvertedTransformationMatrix().multiply(ray.getOrigin(), 1));
		ray.setDirection(this->getInvertedTransformationMatrix().multiply(ray.getDirection(), 0));
	}

	double normalXdirection = normal.scalarProduct(ray.getDirection());

	if (normalXdirection == 0)
		return -1;

	double t = - (normal.scalarProduct(ray.getOrigin()) + distanceToOrigin) / normalXdirection;

	if (t < 0)
		return -1;

	// check if intersection point is within the limited plane (default: 2 units/axis)
	{
		Vector3 pointOfIntersection = ray.getNewPosition(t);
		if ((pointOfIntersection.getY() <= height / 2 && pointOfIntersection.getY() >= -(height/2)) && 
			(pointOfIntersection.getX() <= width / 2 && pointOfIntersection.getX () >= -(width/2)))
			return t;
	}

	return -1;
}

Vector3 Plane::getNormal(Vector3 hitPoint)
{
	return normal;
}