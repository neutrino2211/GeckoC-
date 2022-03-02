#ifndef G_DIRECTIVE_H
#define G_DIRECTIVE_H
#include "parser.h"

void commentHandler(Gecko::lexer_node_t n) {
	char* comment;
	string commentString = "";

	for (Gecko::lexer_child_string_t* childNode : n.children) {
		string commentNode = childNode->value;
		// Gecko::Utils::trim(commentString);
		if (commentString[0] == '{') {
			commentString = Gecko::Utils::string_to_chr_array(commentString.substr(1, commentString.length() - 2));
		}

		commentString += commentNode;
	}

	comment = Gecko::Utils::string_to_chr_array(commentString);

	//if (commentString[0] == '{') comment = Gecko::Utils::string_to_chr_array(commentString.substr(1, commentString.length() - 2));
	//else comment = Gecko::Utils::string_to_chr_array(commentString);

	printf("Comment: %s\n", comment);

	//Gecko::print_lexer_node(n.next);
}

#endif // G_DIRECTIVE_H
