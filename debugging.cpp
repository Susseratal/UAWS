#include "debugging.h"

//// Standard Library Headers ////
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <string>
#include <filesystem>

//// Unreal Headers ////
#include "Engine/Engine.h"
#include "Containers/UnrealString.h"
#include "Modules/ModuleManager.h"

using namespace std;
namespace fs = std::filesystem;

std::ofstream Udebugging::outputHandle;
bool Udebugging::debuggingEnabled = false;

std::ostream& operator<<(std::ostream& o, const FString& f) {
	o << TCHAR_TO_ANSI(*f);
	return o;
}

string getTime() {
	std::stringstream builder;
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	builder << std::put_time(&tm, "%H:%M:%S: ");
	return builder.str();
}

void Udebugging::initDebugFile(FString path) {
	if (path.IsEmpty() == true) {
		outputHandle = std::ofstream("output.log");
	}
	else {
		char* pathChar = TCHAR_TO_ANSI(*path);
		outputHandle = std::ofstream(pathChar);
	}

	outputHandle.rdbuf()->pubsetbuf(0, 0);
	outputHandle << getTime() << "Created output log\n";
	debuggingEnabled = true;
}

void Udebugging::logDebugMessage(FString message) {
	if (debuggingEnabled) {
		outputHandle << getTime() << message << "\n";
	}
}

void Udebugging::debugTime(FString& time) {
	time = getTime().c_str();
}

