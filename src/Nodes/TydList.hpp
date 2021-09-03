#ifndef HPP_TYD_LIST
#define HPP_TYD_LIST

#include "TydCollection.hpp"
#include <string>
#include <vector>

namespace Tyd {
	namespace Nodes {
		typedef struct TydList : public Tyd::Nodes::TydCollection {
			public:
				TydList(std::string name, Tyd::Nodes::TydNode *parent, int docLine = -1) : Tyd::Nodes::TydCollection(name, parent, docLine) {};

				Tyd::Nodes::TydNode* DeepClone() {
					TydList *c = new TydList(name, parent, docLine);
					CopyDataFrom(c);
					return c;
				};
		} TydList;
	};
};

#endif