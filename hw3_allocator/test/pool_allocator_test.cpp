#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include <bitset>
#include "utils.h"
#include "pool_allocator.h"


TEST_CASE("Factorials are computed", "[factorial]")
{
    REQUIRE(factorial(1) == 1);
    REQUIRE(factorial(2) == 2);
    REQUIRE(factorial(3) == 6);
    REQUIRE(factorial(10) == 3'628'800);
}

TEST_CASE("Check valid pool_allocator work", "[pool_allocator]")
{
	constexpr size_t ALLOCATOR_SIZE = 10;
	pool_allocator<int, ALLOCATOR_SIZE> alloc;

	SECTION("Same pool in copied allocator") {
		constexpr size_t ALLOCATOR_COPY_SIZE = 20;
		pool_allocator<char, ALLOCATOR_COPY_SIZE> alloc_copy(alloc);
		REQUIRE(alloc.getPool() == alloc_copy.getPool());
	}

	SECTION("Return nullptr if try to allocate 0 elements") {
		REQUIRE(alloc.allocate(0) == nullptr);
	}

	SECTION("Correct data struct") {
		constexpr size_t DATA_SIZE = 5;
		constexpr uint8_t EXPECTED_FIRST_BYTE = 0b11111000;
		constexpr uint8_t EXPECTED_SECOND_BYTE = 0b00000000;

		int* data = alloc.allocate(DATA_SIZE);
		uint8_t* ctrl = reinterpret_cast<uint8_t*>(data) - static_cast<size_t>(std::ceil(ALLOCATOR_SIZE / 8.));

		REQUIRE(*ctrl == EXPECTED_FIRST_BYTE);
		REQUIRE(*(ctrl + 1) == EXPECTED_SECOND_BYTE);

		alloc.deallocate(data, DATA_SIZE);
	}
}

