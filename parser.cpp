#include "includes/parser.h"
#include "includes/errors.h"

Gecko::Error::Scope* scope = new Gecko::Error::Scope("Parser");

namespace Gecko {

	Parser::Parser(vector<lexer_node_t>* nodes) {
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
		for (lexer_node_t node : *mNodes) {

			if (node.value != "") {
				Keyword* k = keywords[node.value];

				if (!k) {
					printf("Error: %s has no handler\n", node.value.c_str());
					continue;
				};

				if (matchedKeyword != nullptr) {
					std::string message = "Not expecting keyword \"" + node.value + "\" at this location\n";
					// sprintf(message, node.value.c_str());
					// printf("ERROR\n");
					scope->raise(Gecko::Error::SourceFileParsingError, message.c_str(), "SyntaxError", &node); 
				}

				if (k->shouldConsume(&node)) {
					// matchedKeyword = k;
					// printf("should consume: %i\n", k->shouldConsume(&node));
					k->rules->Validate(&node);
					Gecko::Utils::printMap(k->data);
				}
			}
		}
	}
}