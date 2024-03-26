cmake_minimum_required(VERSION 3.14)


set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(matrix LANGUAGES CXX VERSION ${PROJECT_VESRION})

configure_file(version.h.in version.h)

set(SOURCES
	main.cpp
	utils.cpp
)

set(HEADERS
	matrix.h
	utils.h
)

add_executable(matrix ${SOURCES} ${HEADERS})

set_target_properties(matrix
	PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
)

target_include_directories(matrix
	PRIVATE ${CMAKE_BINARY_DIR}
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
	CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	target_compile_options(matrix PRIVATE
		-g
		-Wall
		-Wextra
		-pedantic
	)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	target_compile_options(matrix PRIVATE
		/EHsc
		/W4
	)
endif()



install(TARGETS matrix RUNTIME DESTINATION bin)

if(WIN32)
	set(CPACK_GENERATOR ZIP)
elseif(UNIX)
	set(CPACK_GENERATOR DEB)
	set(CPACK_PACKAGE_CONTACT example@example.com)
endif()

set(CPACK_PACKAGE_NAME "matrix")
set(CPACK_PACKAGE_VENDOR "CMake.org")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
include(CPack)