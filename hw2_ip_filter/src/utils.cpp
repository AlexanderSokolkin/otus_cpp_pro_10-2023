#include "utils.h"
#include <cstring>
#include <filesystem>
#include "version.h"


namespace fs = std::filesystem;


Arguments parseArgs(int argc, char** argv)
{
	switch (argc) {
		case 1:
			return Arguments::StdIn;
		case 2:
			if (strcmp(argv[1], "--help") == 0) {
				return Arguments::Help;
			}
			return Arguments::File;
		default:
			return Arguments::Unknown;
	}
}

void printHelp(std::ostream& out)
{
	out <<	"ip_filter reads input data either from a file or from a standard input stream.\n"
			"From file: ip_filter <filename>\n"
			"From standard input: echo text | ip_filter or just ip_filter and sequential text "
			"input with a signal to simulate the end of the file (depends on the OS).\n"
			"\tAvailable arguments:\n"
			"\t\t--help - print current help.\n";
}

bool fileExists(const char* fileName)
{
	fs::path f = fileName;
	if (fs::exists(f) && (fs::is_regular_file(f) || fs::is_symlink(f))) {
		return true;
	}
	return false;
}

int32_t versionPatch()
{
	return PROJECT_VERSION_PATCH;
}
