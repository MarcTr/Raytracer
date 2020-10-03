#ifndef RAYHELPER_H
#define RAYHELPER_H

#include "RGBType.h"
#include "Settings.h"
#include "../Model/HitInfo.h"
#include "../Model/Light.h"
#include "../Model/Camera.h"
#include "../Maths/Vector3.h"


namespace Utility
{
    class RayHelper 
    {
        public: 
            static RGBType calculateRefractionColor(
                Model::HitInfo hitInfo, 
                Model::Light light, 
                std::vector<Model::Geometry*> sceneObjects, 
                Maths::Vector3 origin, 
                int recursion
            );
            static RGBType calculateReflectionColor(
                Model::HitInfo hitInfo, 
                Model::Light light, 
                std::vector<Model::Geometry*> sceneObjects, 
                Maths::Vector3 origin, 
                int recursion
            );
            static double shootLightRays(
                Model::HitInfo hitInfo, 
                Model::Light light, 
                std::vector<Model::Geometry*> sceneObjects, 
                Settings settings
            );
            static Model::HitInfo shootRay(
                Model::Ray cameraRay, 
                std::vector<Model::Geometry*> sceneObjects, 
                bool isPrimaryRay
            );
            static Model::Ray getLightRay(
                Maths::Vector3 origin, 
                Maths::Vector3 lightPosition
            );
            static Model::Ray getCameraRay(
                Model::Camera camera, 
                int x, 
                int y, 
                int sample, 
                Settings settings
            );

        private:
            RayHelper();
    };
}

#endif