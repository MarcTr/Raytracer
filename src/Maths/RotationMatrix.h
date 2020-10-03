#ifndef ROTATIONMATRIX_H
#define ROTATIONMATRIX_H

#include "Matrix.h"

namespace Maths
{
	class RotationMatrix : public Matrix
	{
		public:
			RotationMatrix();

			void setRotationX(double _rotationX);
			void setRotationY(double _rotationY);
			void setRotationZ(double _rotationZ);
		
			virtual Matrix invert();
	};
}
#endif