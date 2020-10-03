#include "Scene.h"
#include "Geometry.h"
#include "Plane.h"
#include "Sphere.h"
#include "Camera.h"
#include "../Materials/Lambert.h"
#include "../Materials/Phong.h"
#include "../Maths/ScaleMatrix.h"
#include "../Maths/RotationMatrix.h"
#include "../Maths/TranslationMatrix.h"
#include "../Maths/Vector3.h"
#include "../Utility/Colors.h"

#include <vector>

using namespace Model;

Scene::Scene() 
{
}

void Scene::init() 
{
	this->buildScene();
	this->createCamera();
	this->makeLight();
}

void Scene::createCamera()
{
	Vector3 position(0, 1.5, -3.5);
	Vector3 centerOfInterest(0, 1.5, 0);
	Vector3 userUpVector(0, 2, 0);

	camera = Model::Camera(position, centerOfInterest, userUpVector);
	camera.initialize();
}

void Scene::makeLight() {
	Vector3 geometryLightCenter(-1, 3, -3);
    light = Light(geometryLightCenter, 1);
}

void Scene::buildScene() {

	// setup colors
	Utility::Colors colors;
	
	// setup materials
	Lambert *lambert1 = new Lambert();
	Material* lambert1Mat = lambert1;

	Phong *phong1 = new Phong();
	Material* phong1Mat = phong1;

	// generate and transform all objects in the scene

	// matrix to set scale of planes
	ScaleMatrix planeScaleMatrix;
	planeScaleMatrix.setScaleX(3);
	planeScaleMatrix.setScaleY(3);
	ScaleMatrix* planeScaleMatrixP = &planeScaleMatrix;

	// create floor
	RotationMatrix bottomPlaneRotationMatrix;
	bottomPlaneRotationMatrix.setRotationX(90);
	RotationMatrix* bottomPlaneRotationMatrixP = &bottomPlaneRotationMatrix;

	TranslationMatrix bottomPlaneTranslationMatrix;
	bottomPlaneTranslationMatrix.setTranslationY(-1);
	TranslationMatrix* bottomPlaneTranslationMatrixP = &bottomPlaneTranslationMatrix;

	Plane *bottom = new Plane();
	bottom->setColor(colors.lightgrey);
	bottom->addMaterial(lambert1Mat);
	bottom->transform(planeScaleMatrixP);
	bottom->transform(bottomPlaneRotationMatrixP);
	bottom->transform(bottomPlaneTranslationMatrixP);
	sceneObjects.push_back(dynamic_cast<Geometry*>(bottom));

	// create left wall
	RotationMatrix leftPlaneRotationMatrix;
	leftPlaneRotationMatrix.setRotationY(90);
	RotationMatrix* leftPlaneRotationMatrixP = &leftPlaneRotationMatrix;

	TranslationMatrix leftPlaneTranslationMatrix;
	leftPlaneTranslationMatrix.setTranslationX(3);
	TranslationMatrix* leftPlaneTranslationMatrixP = &leftPlaneTranslationMatrix;

	TranslationMatrix leftPlaneTranslationMatrix2;
	leftPlaneTranslationMatrix2.setTranslationY(1.5);
	TranslationMatrix* leftPlaneTranslationMatrix2P = &leftPlaneTranslationMatrix2;

	Plane *left = new Plane();
	left->setColor(colors.blue);
	left->addMaterial(lambert1Mat);
	left->transform(planeScaleMatrixP);
	left->transform(leftPlaneRotationMatrixP);
	left->transform(leftPlaneTranslationMatrixP);
	left->transform(leftPlaneTranslationMatrix2P);
	sceneObjects.push_back(dynamic_cast<Geometry*>(left));
	
	// create right wall
	TranslationMatrix rightPlaneTranslationMatrix;
	rightPlaneTranslationMatrix.setTranslationX(-3);
	TranslationMatrix* rightPlaneTranslationMatrixP = &rightPlaneTranslationMatrix;

	Plane *right = new Plane();
	right->setColor(colors.green);
	right->addMaterial(lambert1Mat);
	right->transform(planeScaleMatrixP);
	right->transform(leftPlaneRotationMatrixP);
	right->transform(rightPlaneTranslationMatrixP);
	right->transform(leftPlaneTranslationMatrix2P);
	sceneObjects.push_back(dynamic_cast<Geometry*>(right));

	// create back wall
	TranslationMatrix backPlaneTranslationMatrix;
	backPlaneTranslationMatrix.setTranslationZ(1.5);
	TranslationMatrix* backPlaneTranslationMatrixP = &backPlaneTranslationMatrix;

	Plane *back = new Plane();
	back->setColor(colors.lightgrey);
	back->transform(planeScaleMatrixP);
	back->transform(backPlaneTranslationMatrixP);
	back->transform(leftPlaneTranslationMatrix2P);
	sceneObjects.push_back(dynamic_cast<Geometry*>(back));

	// create ceiling
	TranslationMatrix topPlaneTranslationMatrix;
	topPlaneTranslationMatrix.setTranslationY(4);
	TranslationMatrix* topPlaneTranslationMatrixP = &topPlaneTranslationMatrix;

	Plane *top = new Plane();
	top->setColor(colors.lightgrey);
	top->addMaterial(lambert1Mat);
	top->setIsLight(true);
	top->transform(planeScaleMatrixP);
	top->transform(bottomPlaneRotationMatrixP);
	top->transform(topPlaneTranslationMatrixP);
	sceneObjects.push_back(dynamic_cast<Geometry*>(top));

	// create main sphere
	TranslationMatrix sphereTranslationMatrix;
	sphereTranslationMatrix.setTranslationY(-0.3);
	sphereTranslationMatrix.setTranslationZ(1);
	TranslationMatrix* sphereTranslationMatrixP = &sphereTranslationMatrix;

	Sphere *sphere1 = new Sphere(1);
	sphere1->setColor(colors.red);
	sphere1->addMaterial(lambert1Mat);
	sphere1->addMaterial(phong1Mat);
	sphere1->transform(sphereTranslationMatrixP);
	// sphere1->setIsRefractive(true);
	// sphere1->setIsReflective(true);	
	sceneObjects.push_back(dynamic_cast<Geometry*>(sphere1));


	// create light geometry
	Sphere *light = new Sphere(0.5);
	light->setColor(colors.white);
	light->setIsLight(true);
	light->addMaterial(lambert1Mat);
	TranslationMatrix lightTransform;
	lightTransform.setTranslationX(-1);
	lightTransform.setTranslationY(3);
	lightTransform.setTranslationZ(-3);
	TranslationMatrix* lightTransformationP = &lightTransform;
	light->transform(lightTransformationP);
	sceneObjects.push_back(dynamic_cast<Geometry*>(light));
}

std::vector<Geometry*> Scene::GetSceneObjects() {
    return sceneObjects;
}

Camera Scene::getCamera() {
    return camera;
}

Light Scene::getLight() {
    return light;
}
