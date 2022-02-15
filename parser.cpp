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

			if (node.consumer_label != "") {
				ParserUtils::DirectiveHandler h = handlers[node.consumer_label];

				if (h) h(node);
				else printf("Error: %s has no handler\n", node.consumer_label.c_str());
			}
		}
	}
}