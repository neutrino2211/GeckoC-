#ifndef G_LEXER_H
#define G_LEXER_H

#include<string>
#include<vector>
#include "utils.h"
#include <stdint.h>

using namespace std;

namespace Gecko {

	struct lexer_position_node_t {
		uint32_t line;
		uint32_t column;
	};

	struct lexer_node_options_t {
		bool isCodeBlock;
	};
	

	struct lexer_child_string_t {
		string value;
		lexer_position_node_t* position;
		lexer_node_options_t* options;
	};

	struct lexer_node_t {
		string consumer_label;
		lexer_node_t* next;
		lexer_node_t* prev;
		vector<lexer_child_string_t*> children;
	};

	class Lexer {
	private:
		bool bParse = true;
		bool bIsCodeBlock = false;
		bool bIgnoreNextChar = false;
		int curvedBraceLevel = 0;
		int squiglyBraceLevel = 0;
		int squareBraceLevel = 0;
		bool isInQuote = false;

		string mInput = "";
	public:

		Lexer(string input);

		vector<lexer_node_t>* parse();

	};

	static void init_node(lexer_node_t* node) {
		node->consumer_label = string();
		node->children = vector<lexer_child_string_t*>();
		node->next = nullptr;
		node->prev = nullptr;
	}

	char* lexer_node_to_string(lexer_node_t* node);

	void print_lexer_node(lexer_node_t* node);
}
#endif // !G_LEXER_H
