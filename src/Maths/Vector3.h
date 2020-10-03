#ifndef VECTOR_H
#define VECTOR_H

#include <string>
#include <iostream>

namespace Maths
{
	class Vector3
	{
		private:
			double x;
			double y;
			double z;

		public:
			Vector3();
			Vector3(double _x, double _y, double _z);

			Vector3 subtract(Vector3 v);
			Vector3 add(Vector3 v);
			Vector3 multiply(double scalar);
			double scalarProduct(Vector3 v);
			Vector3 crossProduct(Vector3 v);
			double magnitude();
			Vector3 normalize();
			std::string toString();
			double getX();
			double getY();
			double getZ();
			void setX(double _x);
			void setY(double _y);
			void setZ(double _z);
	};
}
#endif