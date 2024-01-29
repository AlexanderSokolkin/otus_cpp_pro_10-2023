#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <sstream>
#include "utils.h"

namespace fs = std::filesystem;


TEST(ParseArgs, IsHelp)
{
	const int argc = 2;
	char* argv[argc] = {
		"C:/some/path/to/file.exe",
		"--help"
	};

	ASSERT_EQ(parseArgs(argc, argv), Arguments::Help);
};

TEST(ParseArgs, IsStdIn)
{
	const int argc = 1;
	char* argv[argc] = {
		"C:/some/path/to/file.exe",
	};

	ASSERT_EQ(parseArgs(argc, argv), Arguments::StdIn);
};

TEST(ParseArgs, IsFile)
{
	const int argc = 2;
	char* argv[argc] = {
		"C:/some/path/to/file.exe",
		"/some/file.txt"
	};

	ASSERT_EQ(parseArgs(argc, argv), Arguments::File);
};

TEST(ParseArgs, IsUnknown)
{
	const int argc = 3;
	char* argv[argc] = {
		"C:/some/path/to/file.exe",
		"--help",
		"path/to/txt"
	};

	ASSERT_EQ(parseArgs(argc, argv), Arguments::Unknown);
};


TEST(FileExists, FileIsExists)
{
	std::string fileName = "file.txt";
	fs::path tmpFilePath = fs::temp_directory_path() / fileName;
	std::ofstream f(tmpFilePath);
	f.close();

	ASSERT_TRUE(fileExists(tmpFilePath.string().c_str()));
	fs::remove(tmpFilePath);
};
