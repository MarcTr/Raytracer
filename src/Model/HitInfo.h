#ifndef HITINFO_H
#define HITINFO_H

#include "src/Maths/Vector3.h"
#include "src/Model/Geometry.h"

namespace Model
{
	using namespace Maths;

	class HitInfo
	{
		private:
			double distanceToIntersection;
			Vector3 pointOfIntersection;
			Vector3 untransformedIntersection;
			Geometry* hitObject;

		public:
			HitInfo();
			HitInfo(
				double _distanceToIntersection, 
				Vector3 _pointOfIntersection, 
				Geometry* _hitObject
			);

			double getDistanceToIntersection();
			void setPointOfIntersection(Vector3 intersection);
			Vector3 getPointOfIntersection();
			void setUntransformedIntersection(Vector3 intersection);
			Vector3 getUntransformedIntersection();

			Geometry* getHitObject();
	};
}
#endif