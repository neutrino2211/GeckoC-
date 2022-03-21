#include "includes/parser.h"
#include "includes/errors.h"

Gecko::Error::Scope* scope = new Gecko::Error::Scope("Parser");

namespace Gecko {

	Parser::Parser(vector<lexer_node_t*>* nodes) {
		mNodes = nodes;
	}

	void Parser::register_handler(string directive, ParserUtils::DirectiveHandler h) {
		handlers[directive] = h;
	}

	void Parser::registerKeyword(Keyword* k) {
		keywords[k->name] = k;
	}

	void Parser::parse() {
		Keyword* matchedKeyword = nullptr;

		vector<lexer_node_t*>* lNodes = new vector<lexer_node_t*>;

		uint64_t nodeIndex = 0;
		for (lexer_node_t* node : *mNodes) {
			Gecko::Utils::trim(node->value);
			if (node->value != "") {
				lNodes->push_back(node);
			};
		}

		for (lexer_node_t* node : *lNodes) {
			if(nodeIndex == 0) {
				node->prev = nullptr;
			} else if (nodeIndex < lNodes->size() - 1) {
				node->prev = lNodes->at(nodeIndex - 1);
				node->prev->next = node;
				node->next = lNodes->at(nodeIndex + 1);
			} else {
				node->next = nullptr;
			}
			nodeIndex++;
		}

		// mNodes = lNodes;

		for (lexer_node_t* node : *lNodes) {

			if (node->value != "") {
				Keyword* k = keywords[node->value];

				if (!k) {
					printf("Error: %s -> %s has no handler\n", node->value.c_str(), node->next->value.c_str());
					continue;
				};

				if (matchedKeyword != nullptr) {
					std::string message = "Not expecting keyword \"" + node->value + "\" at this location\n";
					// sprintf(message, node.value.c_str());
					// printf("ERROR\n");
					scope->raise(Gecko::Error::SourceFileParsingError, message.c_str(), "SyntaxError", node); 
				}

				if (k->name == node->value) {
					// matchedKeyword = k;
					// printf("should consume: %i\n", k->shouldConsume(&node));
					k->rules->Validate(node);
					printf("MAP\n");
					Gecko::Utils::printMap(k->data);
				}
			}
		}
	}
}