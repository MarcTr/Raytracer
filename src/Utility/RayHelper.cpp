#include "RayHelper.h"
#include "RGBType.h"
#include "Colors.h"
#include "../Model/HitInfo.h"
#include "../Model/Light.h"
#include "../Model/Geometry.h"
#include "../Maths/Vector3.h"

#include <cmath>


#ifndef M_PI 
#define M_PI 3.1415926535
#endif


using namespace Utility;

RGBType RayHelper::calculateRefractionColor(
		Model::HitInfo hitInfo, 
		Model::Light light, 
		std::vector<Model::Geometry*> sceneObjects, 
		Maths::Vector3 origin, 
		int recursion
	)
{
	Colors colors;
	Maths::Vector3 pointOfIntersection = hitInfo.getPointOfIntersection();
	Maths::Vector3 normal = hitInfo.getHitObject()->getNormal(pointOfIntersection).normalize();
	Maths::Vector3 directionToRayOrigin = origin.subtract(pointOfIntersection).normalize();

	// calculate angle of refraction
	double n_1 = 1.0003;
	double n_2 = 1.33;
	
	double alpha = acos(directionToRayOrigin.scalarProduct(normal) / (directionToRayOrigin.magnitude() * normal.magnitude()));
	double cosBeta = sqrt(1 - pow(n_1 / n_2, 2) * (1 - pow(normal.scalarProduct(directionToRayOrigin), 2)));
	double refraction_1 = n_2 / n_1;
	double cosAlpha = cos(alpha * M_PI / 180);

	Maths::Vector3 refraction_2 = normal.multiply(cosAlpha);
	Maths::Vector3 refraction_2a = refraction_2.subtract(directionToRayOrigin);
	Maths::Vector3 refraction_3 = normal.multiply(cosBeta);
	Maths::Vector3 refraction_4 = refraction_2a.multiply(refraction_1);

	Maths::Vector3 refraction = refraction_4.subtract(refraction_3);
	refraction = refraction.normalize();

	// create new ray in direction of the calculated angle
	Model::Ray refractionRay(hitInfo.getPointOfIntersection(), refraction);

	// modify origin for refraction ray, so that it does not intersect with its own object
	Maths::Vector3 modifiedOrigin = refractionRay.getNewPosition(0.001);
	refractionRay.setOrigin(modifiedOrigin);

	// shoot new ray in direction of refraction
	Model::HitInfo refractionHitInfo = RayHelper::shootRay(
			refractionRay, 
			sceneObjects, 
			false
		);

	RGBType refractionColor;

	// if an object was hit, calculate color of material at new intersection
	if (refractionHitInfo.getDistanceToIntersection() != -1)
	{
		Model::Geometry* hitObject = refractionHitInfo.getHitObject();
 		refractionColor = hitObject->calculateMaterial(
				refractionHitInfo, 
				light, 
				refractionRay.getOrigin()
			 ); 

		if (recursion > 0 && hitObject->getIsRefractive())
		{
			recursion--;
			RGBType recursionColor = RayHelper::calculateRefractionColor(
					refractionHitInfo, 
					light, 
					sceneObjects, 
					refractionRay.getOrigin(), 
					recursion
				);
			refractionColor.mixColors(recursionColor, 0, 100);
		}

		if (recursion > 0 && hitObject->getIsReflective())
		{
			recursion--;
			RGBType recursionColor = RayHelper::calculateReflectionColor(
					refractionHitInfo, 
					light, 
					sceneObjects, 
					refractionRay.getOrigin(), 
					recursion
				);
			refractionColor.mixColors(recursionColor, 50, 50);
		}

		return refractionColor;
	}
	else
	{
		// if no object was hit, return background-color
		return colors.background;
	}

}

RGBType RayHelper::calculateReflectionColor(
		Model::HitInfo hitInfo, 
		Model::Light light, 
		std::vector<Model::Geometry*> sceneObjects, 
		Maths::Vector3 origin, 
		int recursion
	)
{
	Colors colors;
	Maths::Vector3 normal = hitInfo.getHitObject()->getNormal(hitInfo.getPointOfIntersection()).normalize();
	Maths::Vector3 directionToLight = origin.subtract(hitInfo.getPointOfIntersection()).normalize();	

	// calculate angle of reflection
	double reflection_1 = (normal.scalarProduct(directionToLight)) * 2;
	Maths::Vector3 reflection_2 = normal.multiply(reflection_1);
	Maths::Vector3 reflection = reflection_2.subtract(directionToLight).normalize();

	// create new ray in direction of the calculated angle
	Model::Ray reflectionRay(hitInfo.getPointOfIntersection(), reflection);

	// modify origin for reflection ray, so that it does not intersect with its own object
	Maths::Vector3 modifiedOrigin = reflectionRay.getNewPosition(0.01);
	reflectionRay.setOrigin(modifiedOrigin);

	// shoot new ray in direction of reflection
	Model::HitInfo reflectionHitInfo = RayHelper::shootRay(
			reflectionRay, 
			sceneObjects, 
			false
		);


	RGBType reflectionColor;

	// if an object was hit, determine color of material at that point
	if (reflectionHitInfo.getDistanceToIntersection() != -1)
	{
		Model::Geometry* hitObject = reflectionHitInfo.getHitObject();
		reflectionColor = hitObject->calculateMaterial(
				reflectionHitInfo, 
				light, 
				reflectionRay.getOrigin()
			);

		if (recursion > 0 && hitObject->getIsRefractive())
		{
			recursion--;
			RGBType recursionColor = calculateRefractionColor(
					reflectionHitInfo, 
					light, 
					sceneObjects, 
					reflectionRay.getOrigin(), 
					recursion
				); // TODO: implement reflection strength?
			reflectionColor.mixColors(recursionColor, 50, 50);
		}

		if (recursion > 0 && hitObject->getIsReflective())
		{
			recursion--;
			RGBType recursionColor = calculateReflectionColor(
					reflectionHitInfo, 
					light, 
					sceneObjects, 
					reflectionRay.getOrigin(), 
					recursion
				); // TODO: implement reflection strength?
			reflectionColor.mixColors(recursionColor, 50, 50);
		}		
		return reflectionColor;

	}
	else
	{
		// if no object was hit, return color of background
		return colors.background;
	}
}

double RayHelper::shootLightRays(
		Model::HitInfo hitInfo, 
		Model::Light light, 
		std::vector<Model::Geometry*> sceneObjects, 
		Utility::Settings settings
	)
{
	int lightHitCounter = 0;

	// shoot multiple light rays per point of intersection for soft-shadows
	for (int sample = 1; sample <= settings.supersampling_shadows; sample++)
	{
		// generate random vector ( length = radius of lightsphere )
		Maths::Vector3 randomVector(rand(), rand(), rand());
		randomVector = randomVector.normalize();
		
		// TODO: hardcoded only for this specific sphere (lightsource) (radius = 0.5)
		randomVector.setX(randomVector.getX() / 2);
		randomVector.setY(randomVector.getY() / 2);
		randomVector.setZ(randomVector.getZ() / 2);
		
		// add generated vector to center of sphere (lightsource)
		Maths::Vector3 lightRayDirectionEnd = light.getPosition();
		lightRayDirectionEnd = lightRayDirectionEnd.add(randomVector);

		// generate light-ray (from point of intersection to lightsource)
		Model::Ray lightRay = RayHelper::getLightRay(
				hitInfo.getUntransformedIntersection(), 
				lightRayDirectionEnd
			);
		lightRay.setDirection(lightRay.getDirection().normalize());
		
		// shoot ray
		Model::HitInfo shadowInfo = RayHelper::shootRay(lightRay, sceneObjects, false);

		Model::Geometry* hitObject = shadowInfo.getHitObject();
		if (hitObject != 0) 
		{
			if (hitObject->getIsLight()) 
			{
				// if a light source was hit, add to sum
				lightHitCounter++;
			}
		}


	}
	return lightHitCounter;
}

Model::HitInfo RayHelper::shootRay(
		Model::Ray cameraRay, 
		std::vector<Model::Geometry*> sceneObjects, 
		bool isPrimaryRay
	)
{
	double distance = -1;
	Model::Geometry* currentObject = 0;
	Model::Geometry* hitObject = 0;


	// traverse all objects in the scene and find out which object 
	// the current cameraRay hits first
	for (int i = 0; i < sceneObjects.size(); i++)
	{
		currentObject = sceneObjects.at(i);
		double currentDistance = currentObject->getIntersectionDistance(cameraRay);

		if (currentDistance != -1)
		{
			if (distance == -1)
			{
				distance = currentDistance;
				hitObject = currentObject;
			}
			else
			{
				if (currentDistance < distance)
				{
					distance = currentDistance;
					hitObject = currentObject;
				}
			}
		}
	}



	Maths::Vector3 untransformedIntersection = cameraRay.getNewPosition(distance);
	Model::HitInfo hitInfo(distance, untransformedIntersection, hitObject);
	hitInfo.setUntransformedIntersection(untransformedIntersection);

	// if the current ray is a primary ray (i.e. not a shadow/refraction/reflection-ray),
	// apply the transformation (so that shadows for example are not transformed)
	if (isPrimaryRay && hitObject != 0)
	{
		if (hitObject->getIsTransformed())
		{
			cameraRay.setOrigin(hitObject->getInvertedTransformationMatrix().multiply(cameraRay.getOrigin(), 1));
			cameraRay.setDirection(hitObject->getInvertedTransformationMatrix().multiply(cameraRay.getDirection(), 0));
	
			Maths::Vector3 pointOfIntersection = cameraRay.getNewPosition(distance);
			hitInfo.setPointOfIntersection(pointOfIntersection);
		}
	}

	return hitInfo;
}


Model::Ray RayHelper::getLightRay(
		Maths::Vector3 origin, 
		Maths::Vector3 lightPosition
	)
{
	// build lightray from origin to position of lightsource
	Maths::Vector3 lightDirection = lightPosition.subtract(origin).normalize();
	Model::Ray lightRay(origin, lightDirection);

	// modify lightRayOrigin so it doesn't intersect with its own object
	Maths::Vector3 modifiedOrigin = lightRay.getNewPosition(0.01);
	lightRay.setOrigin(modifiedOrigin);

	return lightRay;
}

Model::Ray RayHelper::getCameraRay(
		Model::Camera camera, 
		int x, 
		int y, 
		int sample, 
		Utility::Settings settings
	)
{
	// generate ray from camera origin through pixel 
	double viewVectorDistance = camera.GetViewVector().magnitude();
	Maths::Vector3 camPos = camera.GetPosition();
	Maths::Vector3 camDir = camera.GetViewVector();
	Maths::Vector3 M_centerOfCameraPlane = camPos.add(camDir.normalize());

	// set offset from actual pixel to account for anti-aliasing
	// standard-offset without anti-aliasing: 0.5
	double offset = settings.supersampling_aa > 1 ? (1 / (double)settings.supersampling_aa) * sample : 0.5;

	// normalize
	double currentX = 2 * (x + offset) / settings.width - 1;
	double currentY = 2 * (y + offset) / settings.height - 1;


	// account for aspect ratio
	if (settings.width >= settings.height)
		currentX = currentX * ((double)settings.width / (double)settings.height);
	
	if (settings.height >= settings.width)
		currentY = currentY * ((double)settings.height/(double)settings.width);
		
	// get 3d coordinates of position of the pixel on the plane 
	Maths::Vector3 positionOnPlane = M_centerOfCameraPlane.add(camera.GetSideVector().multiply(currentX));
	positionOnPlane = positionOnPlane.add(camera.GetUpVector().multiply(currentY));

	// get direction from camera origin through the pixel
	Maths::Vector3 directionToPlaneIntersection = positionOnPlane.subtract(camPos);
	directionToPlaneIntersection = directionToPlaneIntersection.normalize();

	// return this ray
	return Model::Ray(camPos, directionToPlaneIntersection);
}