#ifndef ARGSPARSER_H
#define ARGSPARSER_H

#include <string>

namespace Utility 
{

    class ArgsParser
    {
        private:
            std::string numOfAaSamples;
            std::string numOfShadowSamples;
            std::string width;
            std::string height;
            std::string recursionDepth;

        public:
            ArgsParser();

            void Parse(int argc, char** argv);
            std::string GetNumOfAaSamples();
            std::string GetNumOfShadowSamples();
            std::string GetWidth();
            std::string GetHeight();
            std::string GetRecursionDepth();
    };
}
#endif