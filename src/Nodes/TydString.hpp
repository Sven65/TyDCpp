#ifndef HPP_TYD_STRING
#define HPP_TYD_STRING

#include "TydNode.hpp"
#include <string>

namespace Tyd {
	namespace Nodes {
		typedef struct TydString : public Tyd::Nodes::TydNode {
			private:
				std::string val;
			public:
				std::string getValue() { return val; };
				TydString(std::string name, std::string val, Tyd::Nodes::TydNode *parent, int docLine = -1) : Tyd::Nodes::TydNode(name, parent, docLine) {
					this->val = val;
				};
				
				TydNode* DeepClone() {
					TydString *c = new TydString(name, val, parent, docLine);
					c->docIndexEnd = docIndexEnd;
					return c;
				};
		} TydString;
	};
};

#endif
