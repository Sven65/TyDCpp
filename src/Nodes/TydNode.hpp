#ifndef HPP_TYD_NODE
#define HPP_TYD_NODE

#include <type_traits>
#include <cstddef>
#include <string>

namespace Tyd {
	namespace Nodes {
		enum TydNodeType : std::underlying_type_t<std::byte> {
			String,
			Table,
			Document,
			List
		};

		typedef struct TydNode {
			protected:
				std::string name;
			public:
				Tyd::Nodes::TydNode *parent;
				int docLine = -1;
				int docIndexEnd = -1;
				TydNode(std::string name, Tyd::Nodes::TydNode *parent, int docLine = -1) {
					this->parent = parent;
					this->name = name;
					this->docLine = docLine;
				};

				virtual TydNode *DeepClone();
		} TydNode;
	};
};

#endif
