#ifndef PLANE_H
#define PLANE_H

#include "../Maths/Vector3.h"
#include "Geometry.h"
#include "Ray.h"

namespace Model
{
	class Plane : public Geometry
	{
		private:
			Vector3 normal;
			int width = 2;
			int height = 2;
			double distanceToOrigin;

		public:
			Plane();
			
			virtual double getIntersectionDistance(Ray ray);
			virtual Vector3 getNormal(Vector3 hitPoint);
	};
}

#endif