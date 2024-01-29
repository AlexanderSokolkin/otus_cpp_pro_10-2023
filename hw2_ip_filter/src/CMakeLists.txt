configure_file(version.h.in version.h)

set(SOURCES
		ipv4_address.cpp
		main.cpp
		utils.cpp
)

set(HEADERS
		constants.h
		io_ip.h
		ipv4_address.h
		utils.h
)

add_executable(ip_filter ${SOURCES} ${HEADERS})

set_target_properties(ip_filter
	PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
)

target_include_directories(ip_filter
	PRIVATE ${CMAKE_BINARY_DIR}/src
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
	CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	target_compile_options(ip_filter PRIVATE
		-g
		-Wall
		-Wextra
		-pedantic
	)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	target_compile_options(ip_filter PRIVATE
		/EHsc
		/W4
	)
endif()



install(TARGETS ip_filter RUNTIME DESTINATION bin)

if(WIN32)
	set(CPACK_GENERATOR ZIP)
elseif(UNIX)
	set(CPACK_GENERATOR DEB)
	set(CPACK_PACKAGE_CONTACT example@example.com)
endif()

set(CPACK_PACKAGE_NAME "ip_filter")
set(CPACK_PACKAGE_VENDOR "CMake.org")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
include(CPack)
