#ifndef SPHERE_H
#define SPHERE_H

#include "Geometry.h"

namespace Model
{
	class Sphere : public Geometry
	{
		private:
			double radius;
			Vector3 center;

		public:
			Sphere();
			Sphere(double _radius);

			virtual double getIntersectionDistance(Ray ray);
			virtual Vector3 getNormal(Vector3 hitPoint);
	};
}
#endif