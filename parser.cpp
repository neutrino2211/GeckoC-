#include "includes/parser.h"

namespace Gecko {

	Parser::Parser(vector<lexer_node_t>* nodes) {
		mNodes = nodes;
	}

	void Parser::register_handler(string directive, ParserUtils::DirectiveHandler h) {
		handlers[directive] = h;
	}

	void Parser::parse() {
		for (lexer_node_t node : *mNodes) {

			if (node.value != "") {
				ParserUtils::DirectiveHandler h = handlers[node.value];

				if (h) h(node);
				else printf("Error: %s has no handler\n", node.value.c_str());
			}
		}
	}
}