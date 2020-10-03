#ifndef SETTINGS_H
#define SETTINGS_H

#include "ArgsParser.h"

namespace Utility
{
    class Settings
    {
        public:
            Settings();

            void init(int argc, char** argv);
            std::string toString();
            int width = 800;
            int height = 600;
            int dpi = 72;
            int recursionDepth = 3;
            int supersampling_aa = 1;
            int supersampling_shadows = 20;
    };
}
#endif