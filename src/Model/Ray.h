#ifndef RAY_H
#define RAY_H

#include "../Maths/Vector3.h"

namespace Model
{
	using namespace Maths;

	class Ray
	{
		private:
			Vector3 origin;
			Vector3 direction;

		public:
			Ray();
			Ray(Vector3 _origin, Vector3 _direction);

			Vector3 getNewPosition(double t);
			Vector3 getOrigin();
			Vector3 getDirection();
			void setDirection(Vector3 _direction);
			void setOrigin(Vector3 _origin);
	};
}

#endif