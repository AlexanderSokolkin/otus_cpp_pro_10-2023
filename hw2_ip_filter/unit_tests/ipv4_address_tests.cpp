#include <gtest/gtest.h>
#include "ipv4_address.h"


TEST(ipv4_address_test, CreateDefaultInstance)
{
	ASSERT_NO_THROW(ipv4_address());
};

TEST(ipv4_address_test, DefaultInstanceIsInvalid)
{
	ipv4_address ip;
	ASSERT_FALSE(ip.isValid());
};

TEST(ipv4_address_test, CreateInstanseFromStr)
{
	std::string ipStr = "192.168.131.33";
	ASSERT_NO_THROW(ipv4_address(ipStr));
};

TEST(ipv4_address_test, CreateValidInstanseFromStr)
{
	std::string ipStr = "192.168.131.33";
	ipv4_address ip(ipStr);

	ASSERT_TRUE(ip.isValid());
};

TEST(ipv4_address_test, CreateInvalidInstanseFromStr)
{
	std::string ipStr = "192.256.131.33";
	ipv4_address ip(ipStr);

	ASSERT_FALSE(ip.isValid());
};

TEST(ipv4_address_test, GetValidStrFromValidIp)
{
	std::string ipStr = "192.168.131.33";
	ipv4_address ip(ipStr);

	EXPECT_TRUE(ip.isValid());
	ASSERT_EQ(ipStr, ip.str());
};

TEST(ipv4_address_test, GetEmptyStrFromInvalidIp)
{
	std::string ipStr = "256.12.56.7";
	std::string emptyStr{};
	ipv4_address ip(ipStr);

	EXPECT_FALSE(ip.isValid());
	ASSERT_EQ(emptyStr, ip.str());
};

TEST(ipv4_address_test, GetOctetsValues)
{
	uint8_t octets[4] = {255, 12, 56, 7};
	std::string ipStr;
	ipStr.reserve(12);
	for (int i = 0; i < 4; ++i) {
		ipStr += std::to_string(octets[i]);
		ipStr += (i == 3 ? "" : ".");
	}

	ipv4_address ip(ipStr);

	EXPECT_TRUE(ip.isValid());
	for (int i = 0; i < 4; ++i) {
		EXPECT_EQ(ip.octetValue(static_cast<ipv4_address::Octet>(i)),
				  octets[i]) << "invalid " << i << " octet!";
	}
};

TEST(ipv4_address_test, OperatorLess)
{
	ipv4_address ipLess("10.2.0.10");
	ipv4_address ipGreater("10.10.0.10");

	ASSERT_LT(ipLess, ipGreater);
};
