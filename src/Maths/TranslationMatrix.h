#ifndef TRANSLATIONMATRIX_H
#define TRANSLATIONMATRIX_H

#include "Matrix.h"

namespace Maths
{
	class TranslationMatrix : public Matrix
	{
		public:
			TranslationMatrix();

			void setTranslationX(double _x);
			void setTranslationY(double _y);
			void setTranslationZ(double _z);

			virtual Matrix invert();
	};
}
#endif