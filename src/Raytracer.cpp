#include "Utility/stdafx.h"
#include "Utility/Settings.h"
#include "Raytracer.h"
#include "Model/Ray.h"
#include "Model/HitInfo.h"
#include "Model/Light.h"
#include "Model/Scene.h"
#include "Utility/ArgsParser.h"
#include "Utility/Colors.h"
#include "Utility/FileHandler.h"
#include "Utility/RayHelper.h"

#include <vector>
#include <time.h>
#include <cmath>

#ifndef M_PI 
#define M_PI 3.1415926535
#endif

using namespace Model;

int main(int argc, char** argv)
{
	// init settings and print
	Utility::Settings settings;
	settings.init(argc, argv);
	std::cout << settings.toString() << std::endl;

	// init scene
	Scene scene;
	scene.init();

	// init array to hold rendered image
	int pixels = settings.width * settings.height;
	RGBType *scenePixels = new RGBType[pixels];

	// render
	scenePixels = render(scene, scenePixels, settings);

	// save image
	Utility::FileHandler::saveBmp(
		"scene.bmp", 
		settings.width, 
		settings.height, 
		settings.dpi, 
		scenePixels
	);

	return 0;
}


RGBType* render(Scene scene, RGBType* scenePixels, Utility::Settings settings) {

	// setup progress display
	char progressCharacters[] = {'/', '-', '\\', '|'};

	// init random number generator for softshadows
	srand(time(0));

	// init components for render
	Utility::Colors colors;
	Camera camera = scene.getCamera();
	Light light1 = scene.getLight();
	std::vector<Geometry*> sceneObjects = scene.GetSceneObjects();
	RGBType currentPixelColor;

	// render scene, iterate through every pixel
	for (int x = 0; x < settings.width; x++)
	{

		// display progress change every 10 iterations
		if(x % 10 == 0) {
			char progressChar = progressCharacters[(x/2) % 4]; 
			std::cout << "Now Rendering  [ " << progressChar << " ]\r" << std::flush;
		}

		for (int y = 0; y < settings.height; y++)
		{
			// default color
			currentPixelColor = colors.black;

			// shoot multiple rays per pixel for anti-aliasing
			for (int sample = 1; sample <= settings.supersampling_aa; sample++)
			{
				// default color of current sample
				RGBType currentSampleColor = colors.background;
				
				// shoot sampled ray from camera through pixel
				Ray cameraRay = Utility::RayHelper::getCameraRay(
						camera, 
						x, y, 
						sample, 
						settings
					);
				Model::HitInfo hitInfo = Utility::RayHelper::shootRay(
						cameraRay, 
						sceneObjects, 
						true
					);

				// if any object was hit, determine material
				if (hitInfo.getDistanceToIntersection() != -1)
				{
					Geometry* hitObject = hitInfo.getHitObject();
					currentSampleColor = hitObject->calculateMaterial(
							hitInfo, 
							light1, 
							cameraRay.getOrigin()
						);

					if (hitObject->getIsReflective())
					{
						RGBType reflectionColor = Utility::RayHelper::calculateReflectionColor(
								hitInfo, 
								light1, 
								sceneObjects, 
								cameraRay.getOrigin(), 
								settings.recursionDepth
							);
						currentSampleColor.mixColors(reflectionColor, 50, 50);
					}

					if (hitObject->getIsRefractive())
					{
						RGBType refractionColor = Utility::RayHelper::calculateRefractionColor(
								hitInfo, 
								light1, 
								sceneObjects, 
								cameraRay.getOrigin(), 
								settings.recursionDepth
							);
						currentSampleColor.mixColors(refractionColor, 50, 50);
					}

					// shoot rays from point of intersection to lightsource
					double timesLightWasHit = Utility::RayHelper::shootLightRays(
							hitInfo, 
							light1, 
							sceneObjects, 
							settings
						);

					// determine strength of shadow on point of intersection
					double maxShadowValue = 0.3;
					double lightPercentage = (double)timesLightWasHit / ((double)settings.supersampling_shadows / (double)100);
					double lightPercentageInv = 100 - lightPercentage;
					double lightPercentageInv2 = lightPercentageInv / 100;
					double shadow = maxShadowValue * lightPercentageInv2;

					// darken pixel color using shadow strength
					currentSampleColor.r -= shadow;
					currentSampleColor.g -= shadow;
					currentSampleColor.b -= shadow;
				}
				
				// add colors of samples to prepare anti-aliasing
				currentPixelColor.addColor(currentSampleColor);
			}

			// divide summed up colors of samples by number of samples to apply anti-aliasing
			currentPixelColor.divideBy(settings.supersampling_aa);

			// clip in case RGB values fall below 0
			currentPixelColor.clip();

			// set color for current pixel
			int currentPixel = y * settings.width + x;
			scenePixels[currentPixel] = currentPixelColor;
		}
	}

	std::cout << "\rFinished, wrote file scene.bmp" << std::endl;
	return scenePixels;
}