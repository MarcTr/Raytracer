#ifndef PHONG_H
#define PHONG_H

#include "Material.h"

namespace Materials
{
	using namespace Maths;

	class Phong : public Material
	{
		public:
			Phong();

			virtual RGBType calculateMaterial(
				Model::HitInfo hitinfo, 
				Model::Light light, 
				Maths::Vector3 rayOrigin
			);
	};
}

#endif