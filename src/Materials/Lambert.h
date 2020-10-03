#ifndef LAMBERT_H
#define LAMBERT_H

#include "Material.h"
#include "../Maths/Vector3.h"

namespace Materials
{
	using namespace Maths;

	class Lambert : public Material
	{
		public:
			Lambert();

			virtual RGBType calculateMaterial(
				Model::HitInfo hitinfo, 
				Model::Light light, 
				Maths::Vector3 rayOrigin
			);
	};
}

#endif