#include "utils.h"
#include "arguments.h"
#include "bulk.h"
#include <iostream>



int main(int argc, char** argv)
{
	Arguments args = parseArguments(argc, argv);

	switch (args.state) {
		case Arguments::State::ManyArguments:
			std::cerr << "There are too many arguments." << std::endl;
			printHelp(std::cout);
			return 0;

		case Arguments::State::NotANumber:
			std::cerr << "The argument is not a number." << std::endl;
			return 0;

		case Arguments::State::InvalidSize:
			std::cerr << "The size is specified incorrectly." << std::endl;
			printHelp(std::cout);
			return 0;

		case Arguments::State::Correct:
			break;

		default:
			std::cerr << "Unknown error." << std::endl;
			printHelp(std::cout);
			return 0;
	}

	Bulk bulk(args);

	return bulk.exec();
}
