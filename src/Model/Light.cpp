#include "../Utility/stdafx.h"
#include "Light.h"
#include "Geometry.h"

using namespace Model;

Light::Light()
{
}

Light::Light(Vector3 _position, double _intensity)
	: position(_position), intensity(_intensity)
{
}


void Light::setGeometry(Geometry* _geometry)
{
	this->geometry = _geometry;
}

bool Light::getHasGeometry()
{
	return this->hasGeometry;
}

Vector3 Light::getPosition()
{
	return this->position;
}

double Light::getIntensity()
{
	return this->intensity;
}
