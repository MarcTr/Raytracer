#include "../Utility/stdafx.h"
#include "Ray.h"

using namespace Model;

Ray::Ray()
{
}

Ray::Ray(Vector3 _origin, Vector3 _direction)
	: origin(_origin), direction(_direction)
{
}

Vector3 Ray::getNewPosition(double t)
{
	return origin.add(direction.multiply(t));
}

void Ray::setOrigin(Vector3 _origin){ origin = _origin; }
Vector3 Ray::getOrigin(){ return origin; }


void Ray::setDirection(Vector3 _direction){ direction = _direction; }
Vector3 Ray::getDirection() { return direction; }