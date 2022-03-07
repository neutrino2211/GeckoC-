#include "includes/parser.h"

namespace Gecko {

	Parser::Parser(vector<lexer_node_t>* nodes) {
		mNodes = nodes;
	}

	void Parser::register_handler(string directive, ParserUtils::DirectiveHandler h) {
		handlers[directive] = h;
	}

	void Parser::registerKeyword(keyword* k) {
		keywords[k->name] = k;
	}

	void Parser::parse() {
		vector<keyword*> matchedKeywords = {};
		for (lexer_node_t node : *mNodes) {

			if (node.value != "") {
				keyword* k = keywords[node.value];

				if (k) printf("chould consume: %i\n", k->shouldConsume(&node));
				else printf("Error: %s has no handler\n", node.value.c_str());


			}
		}
	}
}