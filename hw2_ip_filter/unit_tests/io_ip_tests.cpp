#include <gtest/gtest.h>
#include <sstream>
#include "io_ip.h"


struct IO_ip : testing::Test
{
	IO_ip() = default;
	~IO_ip() = default;

	void SetUp() override {}

	void TearDown() override {}

	std::string unvalidIp1 = "123.456.789.5";
	std::string unvalidIp2 = "255.255.255.256";
	std::string validIp1 = "1.2.3.4";
	Addresses addresses;
};


TEST_F(IO_ip, CorrectRead)
{
	std::string list;
	std::istringstream in;
	int expectedSize = 1;
	std::string_view expectedIp(validIp1);


	list += unvalidIp1 + "\tsome txt1\n";
	list += validIp1 + "\tsome txt2\n";
	list += unvalidIp2 + "\tsome txt3\n";
	in.str(std::move(list));


	ASSERT_NO_THROW(readIpAdresses(in, addresses));
	ASSERT_EQ(addresses.size(), expectedSize);
	ASSERT_EQ(addresses.front().str(), expectedIp);
}

TEST_F(IO_ip, CorrectPrint)
{
	std::ostringstream out;
	addresses = {
		ipv4_address(unvalidIp1),
		ipv4_address(validIp1),
		ipv4_address(unvalidIp2)
	};
	std::string expectedOut = validIp1 + "\n";

	ASSERT_NO_THROW(printIpAddresses(out, addresses));
	ASSERT_EQ(out.str(), expectedOut);
};


