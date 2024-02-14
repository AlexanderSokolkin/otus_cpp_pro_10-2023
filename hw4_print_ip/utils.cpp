#include "utils.h"
#include "version.h"
#include <stdexcept>


int version_patch() noexcept
{
	return PROJECT_VERSION_PATCH;
}
