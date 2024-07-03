#pragma once
#include "arguments.h"
#include <iostream>


int version_patch() noexcept;

Arguments parseArguments(int argc, char** argv);
void printHelp(std::ostream& in);

