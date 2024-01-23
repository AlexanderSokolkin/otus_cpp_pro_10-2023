cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(helloworld VERSION ${PROJECT_VESRION})

find_package(GTest REQUIRED)

configure_file(version.h.in version.h)

add_executable(helloworld main.cpp)
add_library(helloworldLib lib.cpp)
add_executable(helloworld_test helloworld_test.cpp)

set_target_properties(helloworld helloworldLib helloworld_test PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# include для файла version.h
target_include_directories(helloworldLib
    PRIVATE ${CMAKE_BINARY_DIR}
)

target_include_directories(helloworld_test
	PRIVATE ${GTEST_INCLUDE_DIRS}
	PRIVATE ${gtest_SOURCE_DIR}
)

target_link_libraries(helloworld
	PRIVATE
		helloworldLib
)
target_link_libraries(helloworld_test
	PRIVATE
		helloworldLib
		GTest::gtest
		GTest::gtest_main
)

if (MSVC)
    target_compile_options(helloworld PRIVATE
        /W4
    )
    target_compile_options(helloworldLib PRIVATE
        /W4
    )
    target_compile_options(helloworld_test PRIVATE
        /W4
    )
else ()
    target_compile_options(helloworld PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(helloworldLib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(helloworld_test PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS helloworld RUNTIME DESTINATION bin)


if(WIN32)
	set(CPACK_GENERATOR ZIP)
elseif(UNIX)
	set(CPACK_GENERATOR DEB)
	set(CPACK_PACKAGE_CONTACT example@example.com)
endif()

set(CPACK_PACKAGE_NAME "helloworld")
set(CPACK_PACKAGE_VENDOR "CMake.org")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Installation example for GitHub Actions")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
include(CPack)


enable_testing()
add_test(test1 helloworld_test)
