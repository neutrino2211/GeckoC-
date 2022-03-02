#ifndef G_DECLARATIONS_DIRECTIVE_H
#define G_DECLARATIONS_DIRECTIVE_H

#include "../ast.h"
#include "../parser.h"

void declarationsHandler (Gecko::lexer_node_t n) {
	Gecko::AST::variable_node_t* v = new Gecko::AST::variable_node_t;

	printf("%s\n", n.consumer_label.c_str());

	if (!Gecko::AST::Utils::isValidDeclaration(&n)) {
		printf("Declaration Error: %s\n", n.children.at(0)->value.c_str());
		return;
	}

	printf("GGG: %s\n", n.consumer_label.c_str());
}

#endif
