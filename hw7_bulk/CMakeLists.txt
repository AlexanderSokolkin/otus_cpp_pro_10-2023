cmake_minimum_required(VERSION 3.14)


set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(bulk LANGUAGES CXX VERSION ${PROJECT_VESRION})

configure_file(version.h.in version.h)

set(SOURCES
		bulk.cpp
		command.cpp
		main.cpp
		utils.cpp
)

set(HEADERS
		arguments.h
		bulk.h
		command.h
		utils.h
)

add_executable(bulk ${SOURCES} ${HEADERS})

add_subdirectory(handler)
add_subdirectory(input)
add_subdirectory(output)


set_target_properties(bulk
	PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
)

target_include_directories(bulk
	PRIVATE ${CMAKE_BINARY_DIR}
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
	CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	target_compile_options(bulk PRIVATE
		-g
		-Wall
		-Wextra
		-pedantic
	)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	target_compile_options(bulk PRIVATE
		/EHsc
		/W4
	)
endif()



install(TARGETS bulk RUNTIME DESTINATION bin)

if(WIN32)
	set(CPACK_GENERATOR ZIP)
elseif(UNIX)
	set(CPACK_GENERATOR DEB)
	set(CPACK_PACKAGE_CONTACT example@example.com)
endif()

set(CPACK_PACKAGE_NAME "bulk")
set(CPACK_PACKAGE_VENDOR "CMake.org")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
include(CPack)
