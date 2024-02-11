#include <iostream>
#include <map>
#include <array>
#include "pool_allocator.h"
#include "utils.h"
#include "sequence_container.h"


void test_std_map()
{
	std::cout << "**** test_std_map\n";
	using Map10 = std::map<int, int, std::less<int>, pool_allocator<std::pair<const int, int>, 10>>;
	try {
		Map10 m;
		for (int i = 0; i < 10; ++i) {
			m.insert(std::make_pair(i, factorial(i)));
		}
		for (int i = 0; i < 10; ++i) {
			std::cout << i << " " << m[i] << std::endl;
		}
	} catch (std::exception e) {
		std::cout << e.what();
	}
}

void test_custom_vector()
{
	std::cout << "**** test_custom_vector\n";
	using Vector15 = SequenceContainer<int, pool_allocator<int, 15>>;
	try {
		Vector15 vec;
		vec.reserve(12);
		for (int i = 0; i < 10; ++i) {
			vec.push_back(factorial(i));
		}
		for (int i = 0; i < 10; ++i) {
			std::cout << i << " " << vec[i] << std::endl;
		}
	} catch (std::exception e) {
		std::cout << e.what();
	}
}


int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	test_std_map();
	test_custom_vector();

	return 0;
}
