#ifndef H_TYD_CPP
#define H_TYD_CPP

#include <string>
#include <iostream>
#include "Nodes/TydNode.hpp"

namespace Tyd {
	enum SymbolType {
		RecordName,
		AttributeName,
		AttributeValue
	};

	enum StringFormat {
		Naked,
		Quoted,
		Vertical
	};

	static void Parse(std::string text) {
		std::cout << "Parse " << text << std::endl;
	}

	static void Parse(std::string text, int startIndex, Tyd::Nodes::TydNode parent, bool expectNames = true) {
		std::cout << "Parse " << text << std::endl;
	}
}

#endif
