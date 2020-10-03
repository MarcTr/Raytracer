#include "Material.h"
#include "../Utility/stdafx.h"
#include "src/Model/HitInfo.h"
#include "src/Model/Light.h"

using namespace Materials;

Material::Material()
{
}


RGBType Material::calculateMaterial(
		Model::HitInfo hitinfo, 
		Model::Light light, 
		Maths::Vector3 rayOrigin
	)
{
	RGBType materialColor;
	materialColor.r = 0;
	materialColor.g = 0;
	materialColor.b = 1;
	return materialColor;
}

