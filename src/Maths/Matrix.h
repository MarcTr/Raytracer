#ifndef MATRIX_H
#define MATRIX_H

#include "Vector3.h"

namespace Maths
{
	class Matrix
	{
		protected:
			double matrix[4][4];
			bool isTranslationMatrix = false;
			bool isRotationMatrix = false;
			bool isScaleMatrix = false;


		public:
			Matrix();
			Vector3 multiply(Vector3 _vector, int homogenousCoordinate);
			Matrix multiply(Matrix _matrix);
			double getField(int x, int y);
			void setMatrix(double _matrix[4][4]);

			virtual Matrix invert();

			std::string toString();
	};
}

#endif