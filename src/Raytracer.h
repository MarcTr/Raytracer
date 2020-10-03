#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Model/Camera.h"
#include "Model/Ray.h"
#include "Model/Geometry.h"
#include "Utility/RGBType.h"
#include "Utility/Settings.h"
#include "Model/HitInfo.h"
#include "Model/Scene.h"

#include <map>
#include <vector>

RGBType* render(
    Model::Scene scene, 
    RGBType *scenePixels, 
    Utility::Settings settings
);

#endif