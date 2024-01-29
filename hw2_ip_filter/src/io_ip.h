#pragma once
#include "ipv4_address.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>
#include <sstream>


using Addresses = std::vector<ipv4_address>;


template <typename Elem, typename Traits>
void readIpAdresses(std::basic_istream<Elem, Traits>& in, Addresses& addresses)
{
	std::string line, ipStr;
	std::istringstream strStream;
	while (std::getline(in, line)) {
		strStream.str(std::move(line));
		strStream >> ipStr;
		ipv4_address ip(ipStr);
		if (ip.isValid()) {
			addresses.push_back(ip);
		}
	}
}

template <typename Elem, typename Traits>
void printIpAddresses(std::basic_ostream<Elem, Traits>& out,
					  const Addresses& addresses)
{
	for (auto& elem : addresses) {
		if (elem.isValid()) {
			out << elem.str() << "\n";
		}
	}
}

template <typename Elem, typename Traits>
void printIpAddresses_if(std::basic_ostream<Elem, Traits>& out,
						 const Addresses& addresses,
						 std::function<bool(const ipv4_address&)> pred)
{
	auto sepFunc = [pred, &out] (const ipv4_address& elem) {
		if (elem.isValid() && pred(elem)) {
			out << elem.str() << "\n";
		}
	};
	std::for_each(addresses.begin(), addresses.end(), sepFunc);
}
