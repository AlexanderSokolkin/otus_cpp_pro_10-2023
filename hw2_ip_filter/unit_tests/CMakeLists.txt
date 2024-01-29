set(TEST_SOURCES
		test.cpp
		io_ip_tests.cpp
		ipv4_address_tests.cpp
		utils_tests.cpp
		../src/utils.cpp
		../src/ipv4_address.cpp
)

set(TEST_HEADERS
		../src/io_ip.h
		../src/ipv4_address.h
		../src/utils.h
)


add_executable(ip_filter_test ${TEST_SOURCES} ${TEST_HEADERS})
target_include_directories(ip_filter_test
	PRIVATE ../src
	PRIVATE ${CMAKE_BINARY_DIR}/src)


find_package(GTest REQUIRED)

target_include_directories(ip_filter_test
	PRIVATE ${GTEST_INCLUDE_DIRS}
	PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(ip_filter_test
	PRIVATE
		GTest::gtest
		GTest::gtest_main
)

set_target_properties(ip_filter_test
	PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
)

enable_testing()
add_test(ip_filter_test ip_filter_test)
		