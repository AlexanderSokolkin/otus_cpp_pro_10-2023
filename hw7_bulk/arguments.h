#pragma once
#include <filesystem>


struct Arguments
{
    enum class State {
        ManyArguments,
        NoArguments,
        InvalidSize,
        NotANumber,
        Correct
    };

    State state;
    int size;
    std::filesystem::path path;
};