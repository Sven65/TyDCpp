#ifndef HPP_TYD_DOCUMENT
#define HPP_TYD_DOCUMENT

#include "TydTable.hpp"
#include <string>
#include <vector>

namespace Tyd {
	namespace Nodes {
		typedef struct TydDocument : public Tyd::Nodes::TydTable {
			public:
				TydDocument(std::vector<TydNode> nodes) : Tyd::Nodes::TydTable(NULL, NULL, -1) {
					this->nodes = std::vector<TydNode>{};
					this->nodes.insert(this->nodes.end(), this->nodes.begin(), nodes.end());
				};
		} TydDocument;
	};
};

#endif