#include "ipv4_address.h"
#include <regex>


static std::regex ipv4Reg("^([01]?\\d\\d?|2[0-4]\\d|25[0-5])"
						  "\\.([01]?\\d\\d?|2[0-4]\\d|25[0-5])"
						  "\\.([01]?\\d\\d?|2[0-4]\\d|25[0-5])"
						  "\\.([01]?\\d\\d?|2[0-4]\\d|25[0-5])$");


// ipv4_address::ipv4_address()
// {

// }

ipv4_address::ipv4_address(const std::string& ip)
{
	setAddress(ip);
}

bool ipv4_address::setAddress(const std::string& ip)
{
	std::smatch matches;
	if (std::regex_match(ip, matches, ipv4Reg)) {
		for (int i = 0; i < 4; ++i) {
			m_octets[i] = static_cast<uint8_t>(std::stoi(matches[i + 1].str()));
		}
		m_isValid = true;
	} else {
		m_isValid = false;
	}

	return m_isValid;
}

std::string ipv4_address::str() const
{
	if (!m_isValid) {
		return std::string{};
	}

	std::string result;
	for (int i = 0; i < 4; ++i) {
		result += std::to_string(m_octets[i]);
		result += (i != 3 ? "." : "");
	}
	return result;
}

bool ipv4_address::isValid() const
{
	return m_isValid;
}

uint8_t ipv4_address::octetValue(Octet octet) const
{
	return m_octets[octet];
}

bool ipv4_address::operator<(const ipv4_address& ip) const
{
	if (!m_isValid || !ip.m_isValid) {
		return false;
	}

	for (int i = 0; i < 4; ++i) {
		if (m_octets[i] < ip.m_octets[i]) {
			return true;
		} else if (m_octets[i] > ip.m_octets[i]) {
			return false;
		}
	}
	return false;
}

bool ipv4_address::operator>(const ipv4_address& ip) const
{
	return ip < *this;
}

