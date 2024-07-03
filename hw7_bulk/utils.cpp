#include "utils.h"
#include "version.h"



int version_patch() noexcept
{
	return PROJECT_VERSION_PATCH;
}

Arguments parseArguments(int argc, char** argv)
{
	switch (argc) {
		case 1:
			return Arguments{Arguments::State::NoArguments};
		case 2:
			break;
		default:
			return Arguments{Arguments::State::ManyArguments};
	}

	int i = 0;
	if (argv[1][0] == '-') {
		++i;
	}

	for (; i < std::strlen(argv[1]); ++i) {
		if (!std::isdigit(argv[1][i])) {
			return Arguments{Arguments::State::NotANumber};
		}
	}

	int size = std::atoi(argv[1]);
	if (size < 1 || size > 100) {
		return Arguments{Arguments::State::InvalidSize};
	}

	return Arguments{Arguments::State::Correct, size, std::filesystem::path(argv[0])};
}

void printHelp(std::ostream& in)
{
	const char* help = 	"Batch processing of commands.\n"
						"The program accepts one parameter - "
						"an integer, which is the size of a static block (from 1 to 100).\n"
						"\tFor example: bulk 3\n";

	in << help;
}

