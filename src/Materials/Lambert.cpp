#include "Lambert.h"
#include "../Utility/stdafx.h"
#include "../Model/HitInfo.h"
#include "../Model/Light.h"

using namespace Materials;

Lambert::Lambert()
{
}

RGBType Lambert::calculateMaterial(
		Model::HitInfo hitinfo, 
		Model::Light light, 
		Maths::Vector3 rayOrigin
	)
{
	RGBType materialColor;
	RGBType hitObjectColor = hitinfo.getHitObject()->getColor();
	Vector3 pointOfIntersection = hitinfo.getPointOfIntersection();

	Vector3 normal = hitinfo.getHitObject()->getNormal(pointOfIntersection).normalize();
	Vector3 directionToLight = light.getPosition().subtract(pointOfIntersection).normalize();
					
	materialColor.r = light.getIntensity() * hitObjectColor.r * (normal.scalarProduct(directionToLight));
	materialColor.g = light.getIntensity() * hitObjectColor.g * (normal.scalarProduct(directionToLight));
	materialColor.b = light.getIntensity() * hitObjectColor.b * (normal.scalarProduct(directionToLight));

	return materialColor;
}