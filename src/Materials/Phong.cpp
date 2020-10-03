#include "Phong.h"
#include "Lambert.h"
#include "src/Model/HitInfo.h"
#include "../Model/Light.h"
#include "../Utility/stdafx.h"
#include <cmath>

using namespace Materials;

Phong::Phong()
{
}

RGBType Phong::calculateMaterial(
		Model::HitInfo hitinfo, 
		Model::Light light, 
		Maths::Vector3 rayOrigin
	)
{
	RGBType hitObjectColor = hitinfo.getHitObject()->getColor();
	Vector3 pointOfIntersection = hitinfo.getPointOfIntersection();

	Vector3 normal = hitinfo.getHitObject()->getNormal(pointOfIntersection).normalize();
	Vector3 directionToLight = light.getPosition().subtract(pointOfIntersection).normalize();
	Vector3 directionToOrigin = rayOrigin.subtract(pointOfIntersection).normalize();

	// get reflection vector
	double reflection_1 = (normal.scalarProduct(directionToLight)) * 2;
	Vector3 reflection_2 = normal.multiply(reflection_1);
	Vector3 reflection = reflection_2.subtract(directionToLight).normalize();


	double n = 50;
	RGBType materialColor;

	if (directionToOrigin.scalarProduct(reflection) > 0)
	{
		materialColor.r = light.getIntensity() * hitObjectColor.r * std::pow((directionToOrigin.scalarProduct(reflection)), n);
		materialColor.g = light.getIntensity() * hitObjectColor.g * std::pow((directionToOrigin.scalarProduct(reflection)), n);
		materialColor.b = light.getIntensity() * hitObjectColor.b * std::pow((directionToOrigin.scalarProduct(reflection)), n);
	}
	return materialColor;
}