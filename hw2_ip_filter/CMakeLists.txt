cmake_minimum_required(VERSION 3.14)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(ip_filter LANGUAGES CXX VERSION ${PROJECT_VESRION})


add_subdirectory(src)
add_subdirectory(unit_tests)
