#pragma once
#include "constants.h"
#include <iostream>


Arguments parseArgs(int argc, char** argv);
void printHelp(std::ostream& out);
bool fileExists(const char* fileName);

int32_t versionPatch();
