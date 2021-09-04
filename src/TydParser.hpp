#ifndef HPP_TYD_PARSER
#define HPP_TYD_PARSER

#include <string>
#include <iostream>
#include <exception>
#include <vector>
#include "TydNode.hpp"
#include "TydConstants.hpp"
#include "TydList.hpp"
#include "TydTable.hpp"
#include "TydString.hpp"

namespace Tyd {
	namespace Parser {
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

		static std::vector<Tyd::Nodes::TydNode*> Parse(std::string text) {
			return Parse(text, 0, NULL, true);
		}

		static std::vector<Tyd::Nodes::TydNode*> Parse(std::string text, int startIndex, Tyd::Nodes::TydNode *parent, bool expectNames = true) {
			int p = startIndex;

			while(p != text.length()) {
				std::string recordName = "";
				std::string recordAttHandle = "";
				std::string recordAttSource = "";
				bool recordAttAbstract = false;
				bool recordAttNoInherit = false;

				try {
					//Skip insubstantial chars
					p = NextSubstanceIndex(text, p);

					//We reached EOF, so we're finished
					if (p == text.length()) {
						if(parent != NULL) {
							throw new std::runtime_error("Missing closing brackets");
						}
						break;
					}

					//We reached a closing bracket, so we're finished with this record
					if (text[p] == Tyd::Constants::TableEndChar || text[p] == Tyd::Constants::ListEndChar) {
						break;
					}

					//Read the record name if we're not reading anonymous records
					if (expectNames) {
						recordName = ReadSymbol(text, SymbolType::RecordName, p);
					}

					// Skip whitespace
					p = NextSubstanceIndex(text, p);

					// Read attributes

					while (text[p] == Tyd::Constants::AttributeStartChar) {
						// Skip past the '*' character
						p++;

						std::string attName = ReadSymbol(text, SymbolType::AttributeName, p);

						if (attName == Tyd::Constants::AbstractAttributeName) {
							//Just reading the abstract name indicates it's abstract, no value is needed
							recordAttAbstract = true;
						} else if (attName == Tyd::Constants::NoInheritAttributeName) {
							//Just reading the noinherit name indicates it's noinherit, no value is needed
							recordAttNoInherit = true;
						} else {
							p = NextSubstanceIndex(text, p);

							// Read the att value

							std::string attVal = ReadSymbol(text, SymbolType::AttributeValue, p);
							
							if (attName == Tyd::Constants::HandleAttributeName) {
								recordAttHandle = attVal;
							} else if (attName == Tyd::Constants::SourceAttributeName) {
								recordAttSource = attVal;
							} else {
								throw new std::runtime_error("Unknown attribute name '" + attName + "' at " + LineColumnString(text, p) + "\n" + ErrorSectionString(text,p));
							}
						}

						p = NextSubstanceIndex(text, p);
					}
				} catch (const std::exception& e) {
					throw new std::runtime_error("Exception parsing Tyd headers at " + LineColumnString(text, p) + ": " + e.what() + "\n" + ErrorSectionString(text,p));
				}

				// Read the record value.
				// After this is complete, p should be pointing at the char after the last char of the record.

				if (text[p] == Tyd::Constants::TableStartChar) {
					//It's a table
					Tyd::Nodes::TydTable *newTable = new Tyd::Nodes::TydTable(recordName, parent, IndexToLine(text, p));

					//Skip past the opening bracket
					p++;

					p = NextSubstanceIndex(text, p);

					//Recursively parse all of new child's children
					for (auto subNode : Parse(text, p, newTable, true)) {
						newTable->AddChild(*subNode);
						p = subNode->docIndexEnd + 1;
					}

					p = NextSubstanceIndex(text, p);

					//Confirm that we are indeed on the closing bracket
					if (text[p] != Tyd::Constants::TableEndChar) {
						throw new std::runtime_error("Expected '" + std::to_string(Tyd::Constants::TableEndChar) + "' at " + LineColumnString(text, p) + "\n" + ErrorSectionString(text, p));
					}

					newTable->docIndexEnd = p;
					newTable->SetupAttributes(recordAttHandle, recordAttSource, recordAttAbstract, recordAttNoInherit);
					return std::vector<Tyd::Nodes::TydNode*>{newTable};

					//Move pointer one past the closing bracket
					p++;
				} else if (text[p] == Tyd::Constants::ListStartChar) {
					// It's a list
					Tyd::Nodes::TydList *newList = new Tyd::Nodes::TydList(recordName, parent, IndexToLine(text, p));

					//Skip past the opening bracket
					p++;

					p = NextSubstanceIndex(text, p);

					//Recursively parse all of new child's children and add them to it
					for (auto subNode : Parse(text, p, newList, true)) {
						newList->AddChild(*subNode);
						p = subNode->docIndexEnd + 1;
					}

					p = NextSubstanceIndex(text, p);
					if (text[p] != Tyd::Constants::ListEndChar){
						throw new std::runtime_error("Expected " + std::to_string(Tyd::Constants::ListEndChar) + " at " + LineColumnString(text, p) + "\n" + ErrorSectionString(text, p));
					}

					newList->docIndexEnd = p;
					newList->SetupAttributes(recordAttHandle, recordAttSource, recordAttAbstract, recordAttNoInherit);
					return std::vector<Tyd::Nodes::TydNode*>{newList};

					//Move pointer one past the closing bracket
					p++;
				} else {
					// It's a string
					int pStart = p;
					std::string val;
					ParseStringValue(text, p, val);

					Tyd::Nodes::TydString *strNode = new Tyd::Nodes::TydString(recordName, val, parent, IndexToLine(text, pStart));
					strNode->docIndexEnd = p - 1;
					return std::vector<Tyd::Nodes::TydNode*>{strNode};
				}

			};
		}

		static void ParseStringValue(std::string text, int &p, std::string &val) {}

		static std::string ResolveEscapeChars(std::string input) {}

		static char EscapedCharOf(char inputChar) {}

		static std::string ReadSymbol(std::string text, SymbolType symType, int &p) {}

		static std::string SymbolTypeName(SymbolType st) {}

		static bool IsSymbolChar(char c) {}

		static bool IsNewline(std::string text, int p) {}

		static bool IsNewlineLF(std::string text, int p) {}

		static bool IsNewlineCRLF(std::string text, int p) {}

		static std::string LineColumnString(std::string text, int index) {}

		static std::string ErrorSectionString(std::string text, int index) {}

		static int IndexToLine(std::string text, int index) {}

		static void IndexToLineColumn(std::string text, int index, int &line, int &colum) {}

		static int NextSubstanceIndex(std::string text, int p) {}
	};
}

#endif
