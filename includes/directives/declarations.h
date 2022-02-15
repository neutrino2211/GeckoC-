#pragma once

#include "../ast.h"
#include "../parser.h"

void declarationsHandler (Gecko::lexer_node_t n) {
	Gecko::AST::variable_node_t* v = new Gecko::AST::variable_node_t;

	if (!Gecko::AST::Utils::isValidDeclaration(&n)) {
		printf("Declaration Error: %s\n", n.children.at(0));
		return;
	}

	printf("GGG: %s\n", n.consumer_label.c_str());
}