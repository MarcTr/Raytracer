#ifndef LIGHT_H
#define LIGHT_H

#include "../Maths/Vector3.h"
#include "Geometry.h"

namespace Model
{
	using namespace Maths;

	class Geometry;

	class Light
	{
		private:
			Vector3 position;
			double intensity;

			bool hasGeometry = false;
			Geometry* geometry = NULL;

		public:
			Light();
			Light(Vector3 _position, double _intensity);

			void setGeometry(Geometry* _geometry);
			bool getHasGeometry();

			Vector3 getPosition();
			double getIntensity();
	};
}
#endif