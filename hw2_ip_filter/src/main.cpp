#include "constants.h"
#include "utils.h"
#include "io_ip.h"
#include "ipv4_address.h"
#include <string>
#include <algorithm>




int main(int argc, char** argv)
{
	Addresses addresses;
	switch (parseArgs(argc, argv)) {
		case Arguments::Help: {
			printHelp(std::cout);
			break;
		}
		case Arguments::StdIn: {
			readIpAdresses(std::cin, addresses);
			break;
		}
		case Arguments::File: {
			if (!fileExists(argv[1])) {
				std::cerr << "File " << argv[1] << " not found!";
				return 0;
			}
			std::ifstream fs(argv[1], std::ios::in);
			if (!fs.is_open()) {
				std::cerr << "File " << argv[1] << " could not be opened";
				return 0;
			}
			readIpAdresses(fs, addresses);
			break;
		}
		default: {
			std::cerr << "Arguments are invalid!";
			printHelp(std::cout);
			break;
		}
	}

	std::sort(addresses.begin(), addresses.end(), std::greater<>{});
	
	printIpAddresses(std::cout, addresses);
	
	auto firstIs1 = [octVal = 1](const ipv4_address& ip) {
		return 	ip.octetValue(ipv4_address::Octet_1) == octVal;
	};
	printIpAddresses_if(std::cout, addresses, firstIs1);

	auto firstIs46SecondIs70 = [oct1Val = 46, oct2Val = 70](const ipv4_address& ip) {
		return 	ip.octetValue(ipv4_address::Octet_1) == oct1Val &&
				ip.octetValue(ipv4_address::Octet_2) == oct2Val;
	};
	printIpAddresses_if(std::cout, addresses, firstIs46SecondIs70);

	auto anyIs46 = [octVal = 46](const ipv4_address& ip) {
		return 	ip.octetValue(ipv4_address::Octet_1) == octVal ||
				ip.octetValue(ipv4_address::Octet_2) == octVal ||
				ip.octetValue(ipv4_address::Octet_3) == octVal ||
				ip.octetValue(ipv4_address::Octet_4) == octVal;
	};
	printIpAddresses_if(std::cout, addresses, anyIs46);
	
	return 0;
}