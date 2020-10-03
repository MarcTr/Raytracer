#include "../Utility/stdafx.h"
#include "Sphere.h"
#include <cmath>

using namespace Model;

Sphere::Sphere()
{
}

Sphere::Sphere(double _radius)
	: radius(_radius), center(Vector3(0,0,0))
{
}


double Sphere::getIntersectionDistance(Ray ray)
{
	if (this->getIsTransformed())
	{
		ray.setOrigin(this->getInvertedTransformationMatrix().multiply(ray.getOrigin(), 1));
		ray.setDirection(this->getInvertedTransformationMatrix().multiply(ray.getDirection(), 0)); 
	}

	double B = 2 *	(ray.getOrigin().getX() * ray.getDirection().getX()
					+ ray.getOrigin().getY() * ray.getDirection().getY()
					+ ray.getOrigin().getZ() * ray.getDirection().getZ());

	double C = std::pow(ray.getOrigin().getX(), 2)
		+ std::pow(ray.getOrigin().getY(), 2)
		+ std::pow(ray.getOrigin().getZ(), 2)
		- std::pow(radius, 2);

	double discriminant = std::pow(B, 2) - 4 * C;

	if (discriminant < 0)
		return -1;

	double t_0 = (-B - std::sqrt(discriminant)) / 2;

	if (discriminant == 0)
		return t_0;

	double t_1 = (-B + std::sqrt(discriminant)) / 2;


	double result = 0;

	if (t_0 <= t_1)
		result = t_0;
	else
		result = t_1;

	if (result < 0)
	{
		return -1;
	}
	return result;
}

Vector3 Sphere::getNormal(Vector3 hitPoint)
{
	Vector3 normal = hitPoint.subtract(center);
	return normal;
}
