#include "utils.h"
#include "version.h"
#include <stdexcept>


unsigned int factorial(int num)
{
	if (num < 0 || num > 12) {
		throw std::out_of_range("");
	}

	if (num == 0) {
		return 1;
	}

	unsigned int result = 1;
	while (num) {
		result *= num;
		--num;
	}
	return result;
}

int version_patch() noexcept
{
	return PROJECT_VERSION_PATCH;
}
