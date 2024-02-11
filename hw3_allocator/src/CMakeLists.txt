configure_file(version.h.in version.h)

set(SOURCES
		main.cpp
		utils.cpp
)

add_executable(allocator ${SOURCES})

target_include_directories(allocator
	PRIVATE ${CMAKE_BINARY_DIR}/src
)

set_target_properties(allocator
	PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
)

target_include_directories(allocator
	PRIVATE ${CMAKE_BINARY_DIR}
	PRIVATE containers
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
	CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	target_compile_options(allocator PRIVATE
		-g
		-Wall
		-Wextra
		-pedantic
	)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	target_compile_options(allocator PRIVATE
		/EHsc
		/W4
	)
endif()



install(TARGETS allocator RUNTIME DESTINATION bin)

if(WIN32)
	set(CPACK_GENERATOR ZIP)
elseif(UNIX)
	set(CPACK_GENERATOR DEB)
	set(CPACK_PACKAGE_CONTACT example@example.com)
endif()

set(CPACK_PACKAGE_NAME "allocator")
set(CPACK_PACKAGE_VENDOR "CMake.org")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
include(CPack)