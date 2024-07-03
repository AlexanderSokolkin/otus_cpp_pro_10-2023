#pragma once
#include "command.h"
#include <string>


struct InputData
{
    enum class Type {
        StartDynamicSection,
        EndDynamicSection,
        Command,
        EndOfFile,
    };

    Type dataType;
    Command command;
};
