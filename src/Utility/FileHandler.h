#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "RGBType.h"

namespace Utility 
{
    class FileHandler 
    {
        public:
            static void saveBmp(
                const char *filename, 
                int width, 
                int height, 
                int dpi, 
                RGBType *data
            );

        private:
            FileHandler();
    };
}

#endif