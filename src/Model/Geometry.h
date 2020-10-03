#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "Ray.h"
#include "../Utility/RGBType.h"
#include "../Materials/Material.h"
#include "Light.h"
#include "../Maths/Matrix.h"

#include <vector>



namespace Model
{
	using namespace Materials;

	class HitInfo;

	class Geometry
	{
		private:
			RGBType color;
			std::vector<Material*> materials;
			bool isReflective = false;
			bool isRefractive = false;
			bool isTransformed = false;
			bool isLight = false;
			Matrix transformationMatrix = Matrix();
			Matrix invertedMatrix = Matrix();
			
		
		public:
			Geometry();

			virtual double getIntersectionDistance(Ray ray);
			RGBType calculateMaterial(HitInfo hitInfo, Light light1, Vector3 rayOrigin);
			
			bool getIsReflective();
			void setIsReflective(bool _isReflective);
			bool getIsRefractive();
			void setIsRefractive(bool _isRefractive);
			bool getIsTransformed();
			void addMaterial(Material* _material);
			virtual Vector3 getNormal(Vector3 hitPoint);
			RGBType getColor();
			std::vector<Material*> getMaterials();
			Matrix getTransformationMatrix();
			Matrix getInvertedTransformationMatrix();
			void setColor(RGBType _color);
			void setIsLight(bool _isLight);
			bool getIsLight();
			void transform(Matrix*	 _transformationMatrix);
	};
}
#endif