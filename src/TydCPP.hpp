#ifndef H_TYD_CPP
#define H_TYD_CPP

#include <string>
#include <iostream>
#include <vector>
#include "TydParser.hpp"

namespace Tyd {
	static std::vector<Tyd::Nodes::TydNode*> Parse(std::string text) {
		return Tyd::Parser::parse(text);
	}
}

#endif
