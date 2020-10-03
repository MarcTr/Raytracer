#include "Settings.h"
#include "ArgsParser.h"

using namespace Utility;

Settings::Settings() 
{
}

void Settings::init(int argc, char** argv) {
	Utility::ArgsParser argsParser;
	argsParser.Parse(argc, argv);


	std::string argsNumOfAASamples = argsParser.GetNumOfAaSamples();
	supersampling_aa = argsNumOfAASamples.empty() ? supersampling_aa : stoi(argsNumOfAASamples);

	std::string argsNumOfShadowSamples = argsParser.GetNumOfShadowSamples();
	supersampling_shadows = argsNumOfShadowSamples.empty() ? supersampling_shadows : stoi(argsNumOfShadowSamples);

	std::string argsWidth = argsParser.GetWidth();
	width = argsWidth.empty() ? width : stoi(argsWidth);

	std::string argsHeight = argsParser.GetHeight();
	height = argsHeight.empty() ? height : stoi(argsHeight);

	std::string argsRecDepth = argsParser.GetRecursionDepth();
	recursionDepth = argsRecDepth.empty() ? recursionDepth : stoi(argsRecDepth);
}

std::string Settings::toString() {
    return "Resolution: " + std::to_string(width) + "x" + std::to_string(height) + "\n"
        + "Recursion-depth: " + std::to_string(recursionDepth) + " steps\n"
        + "Supersampling (SoftShadows): " + std::to_string(supersampling_shadows) + " samples\n"
        + "Supersampling (AntiAliasing): " + std::to_string(supersampling_aa) + " samples\n";
}