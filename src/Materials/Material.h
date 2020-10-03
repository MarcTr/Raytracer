#ifndef MATERIAL_H
#define MATERIAL_H

#include "../Utility/RGBType.h"
#include "../Maths/Vector3.h"

class HitInfo; 

namespace Model
{
	class Light;
	class HitInfo;
}

namespace Materials
{
	class Material
	{
	public:
		Material();

		virtual RGBType calculateMaterial(
			Model::HitInfo hitinfo, 
			Model::Light light, 
			Maths::Vector3 rayOrigin
		);
	};
}
#endif