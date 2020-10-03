#ifndef SCENE_H
#define SCENE_H

#include "Geometry.h"
#include "Camera.h"
#include "Light.h"
#include "../Utility/RGBType.h"

#include <vector>
#include <map>

namespace Model 
{
    class Scene 
    {
        private:
            std::vector<Geometry*> sceneObjects;
            Camera camera;
            Light light;

            void createCamera();
            void makeLight();
            void buildScene();

        public:
            Scene();

            void init();
            std::vector<Geometry*> GetSceneObjects();
            Camera getCamera();
            Light getLight();
    };
}
#endif