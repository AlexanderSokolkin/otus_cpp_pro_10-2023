#pragma once
#include <string>


class ipv4_address
{
public:
	enum Octet : unsigned {
		Octet_1 = 0,
		Octet_2 = 1,
		Octet_3 = 2,
		Octet_4 = 3
	};


public:
	ipv4_address() = default;
	ipv4_address(const std::string& ip);

	bool setAddress(const std::string& ip);
	std::string str() const;
	bool isValid() const;
	uint8_t octetValue(Octet octet) const;

	bool operator<(const ipv4_address& ip) const;
	bool operator>(const ipv4_address& ip) const;

private:
	uint8_t		m_octets[4]{};
	bool		m_isValid = false;
};