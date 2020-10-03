#ifndef SCALEMATRIX_H
#define SCALEMATRIX_H

#include "Matrix.h"

namespace Maths
{
	class ScaleMatrix : public Matrix
	{
		public:
			ScaleMatrix();

			void setScaleX(double _x);
			void setScaleY(double _y);
			void setScaleZ(double _z);

			virtual Matrix invert();
	};
}
#endif