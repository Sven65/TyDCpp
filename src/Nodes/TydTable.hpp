#ifndef HPP_TYD_TABLE
#define HPP_TYD_TABLE

#include "TydCollection.hpp"
#include <string>
#include <algorithm>

namespace Tyd {
	namespace Nodes {
		typedef struct TydTable : public Tyd::Nodes::TydCollection {
			public:
					  TydNode& operator[](std::string name)       { return std::find_if(nodes.begin(), nodes.end(), [&](const TydNode &node) { return node.name == name; }); };
    			const TydNode& operator[](std::string name) const { return std::find_if(nodes.begin(), nodes.end(), [&](const TydNode &node) { return node.name == name; }); };

				TydTable(std::string name, Tyd::Nodes::TydNode *parent, int docLine = -1) : Tyd::Nodes::TydNode(name, parent, docLine) {};
				
				TydNode *DeepClone() {
					TydTable *c = new TydTable(name, parent, docLine);
					CopyDataFrom(c);
					return c;
				};
		} TydTable;
	};
};

#endif