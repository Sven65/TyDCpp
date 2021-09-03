#ifndef HPP_TYD_COLLECTION
#define HPP_TYD_COLLECTION

#include "TydNode.hpp"
#include <string>
#include <vector>

namespace Tyd {
	namespace Nodes {
		typedef struct TydCollection : public Tyd::Nodes::TydNode {
			protected:
				std::vector<Tyd::Nodes::TydNode> nodes;
				std::string attHandle;
				std::string attSource;
				std::string attAbstract;
				std::string attNoInherit;

				void CopyDataFrom(TydCollection other) {
					other.docIndexEnd   = docIndexEnd;
					other.attHandle     = attHandle;
					other.attSource     = attSource;
					other.attAbstract   = attAbstract;
					other.attNoInherit  = attNoInherit;

					for(auto itr : nodes) {
						other.AddChild(*itr.DeepClone());
					}
				};
			public:
				TydCollection(std::string name, Tyd::Nodes::TydNode *parent, int docLine = -1) : Tyd::Nodes::TydNode(name, parent, docLine) {};
				void SetupAttributes(std::string attHandle, std::string attSource, bool attAbstract, bool attNoInherit) {
					this->attHandle = attHandle;
					this->attSource = attSource;
					this->attAbstract = attAbstract;
					this->attNoInherit = attNoInherit;
				};
				void AddChild(Tyd::Nodes::TydNode node) {
					nodes.push_back(node);
					node.parent = this;
				};

				void InsertChild(Tyd::Nodes::TydNode node, int index) {
					auto insertionPos = nodes.begin() + index;
					nodes.insert(insertionPos, node);
					node.parent = this;
				};
		} TydCollection;
	};
};

#endif
