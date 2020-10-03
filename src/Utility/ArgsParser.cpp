#include "ArgsParser.h"


#include <string>
#include <iostream>

using namespace Utility;

ArgsParser::ArgsParser()
{
}

void ArgsParser::Parse(int argc, char** argv)
{
    for(int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if(arg == "-aaSamples") {
            if(i + 1 < argc) {
                numOfAaSamples = argv[++i];
            }
            else {
                std::cerr << "No argument provided for parameter -aaSamples" << std::endl;
            }
        }
        else if(arg == "-shadowSamples") {
            if(i + 1 < argc) {
                numOfShadowSamples = argv[++i];
            }
            else {
                std::cerr << "No argument provided for parameter -shadowsSamples" << std::endl;
            }
        }
        else if(arg == "-recDepth") {
            if(i + 1 < argc) {
                recursionDepth = argv[++i];
            }
            else {
                std::cerr << "No argument provided for parameter -recDepth" << std::endl;
            }
        }
        else if(arg == "-w") {
            if(i + 1 < argc) {
                width = argv[++i];
            }
            else {
                std::cerr << "No argument provided for parameter -w" << std::endl;
            }
        }
        else if(arg == "-h") {
            if(i + 1 < argc) {
                height = argv[++i];
            }
            else {
                std::cerr << "No argument provided for parameter -h" << std::endl;
            }
        }
        else {
            std::cerr << "Unknown argument " << argv[i] << std::endl;
        }
    }
}

std::string ArgsParser::GetNumOfAaSamples() 
{ 
    return numOfAaSamples; 
}

std::string ArgsParser::GetNumOfShadowSamples() 
{ 
    return numOfShadowSamples; 
}

std::string ArgsParser::GetHeight() 
{ 
    return height; 
}

std::string ArgsParser::GetWidth() 
{ 
    return width; 
}

std::string ArgsParser::GetRecursionDepth() 
{
    return recursionDepth;
}