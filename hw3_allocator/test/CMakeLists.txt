set(TEST_SOURCES
		pool_allocator_test.cpp
		../src/utils.cpp
)

add_executable(allocator_test ${TEST_SOURCES})


target_include_directories(allocator_test
	PRIVATE ../src
	PRIVATE ${CMAKE_BINARY_DIR}/src
)

find_package(Catch2 REQUIRED)

target_link_libraries(allocator_test
	PRIVATE
		Catch2::Catch2WithMain
)

set_target_properties(allocator_test
	PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
)

enable_testing()
add_test(allocator_test allocator_test)
		