#ifndef _SYMBOL_HPP_
#define _SYMBOL_HPP_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "key.hpp"

class Symbol {
public:
	std::vector<Key> T;
	Symbol(const std::string&);
	void decrypt(const std::string&);
};

#endif
