#include "includes/lexer.h"

using namespace std;

namespace Gecko {

	Lexer::Lexer(string input) {
		mInput = input;
	}

	vector<lexer_node_t>* Lexer::parse() {
		char* arr = Utils::string_to_chr_array(mInput);
		string tmp = "";
		vector<lexer_node_t>* nodes = new vector<lexer_node_t>();
		lexer_node_t* next_node = new lexer_node_t;
		init_node(next_node);


		uint32_t line = 1;
		uint32_t column = 1;
		while (*arr != '\0') {

			if (*arr == '(') curvedBraceLevel++;
			else if (*arr == ')') curvedBraceLevel--;

			if (*arr == '{') squiglyBraceLevel++;
			else if (*arr == '}') squiglyBraceLevel--;

			if (*arr == '[') squareBraceLevel++;
			else if (*arr == ']') squareBraceLevel--;

			if (*arr == '"') isInQuote = !isInQuote;

			if (squareBraceLevel == 0 && squiglyBraceLevel == 0 && curvedBraceLevel == 0 && !isInQuote) bParse = true;
			else bParse = false;

			if (bParse == false && squiglyBraceLevel > 0) bIsCodeBlock = true;

			if (*arr == ' ' && bParse && tmp != "") {
				Gecko::Utils::ltrim(tmp);
				if (next_node->consumer_label.empty()) {
					// printf("[TMP]%s", tmp.c_str());
					Utils::ltrim(tmp);
					next_node->consumer_label = tmp.c_str();
				}
				else {
					Gecko::lexer_position_node_t* pos = new Gecko::lexer_position_node_t;
					Gecko::lexer_child_string_t* child = new Gecko::lexer_child_string_t;
					Gecko::lexer_node_options_t* options = new Gecko::lexer_node_options_t;

					pos->column = column;
					pos->line = line;

					child->position = pos;
					child->value = tmp.c_str();
					child->options = options;
					next_node->children.push_back(child);
				}

				// tmp has been comitted to a node, reset it
				tmp = "";
			}
			else if (*arr == '\n' && bParse && tmp != "") {
				Gecko::Utils::ltrim(tmp);
				//print_lexer_node(next_node);
				Gecko::lexer_position_node_t* pos = new Gecko::lexer_position_node_t;
				Gecko::lexer_child_string_t* child = new Gecko::lexer_child_string_t;

				// Set the token position
				pos->column = column;
				pos->line = line;
				child->position = pos;

				// Set the value of the token
				child->value = tmp.c_str();

				// Add this last identified token to the node's children vector
				next_node->children.push_back(child);

				// Make a copy of the completed node
				lexer_node_t n = *next_node;
				
				// Clear the node
				init_node(next_node);

				// Set the current node's prev as the just completed node
				next_node->prev = &n;
				// Set the next of the just completed node to this new node
				n.next = next_node;

				// Push the completed node to the nodes vector
				nodes->push_back(n);

				// printf("%s\n", tmp.c_str());

				// tmp has been comitted to a node, reset it
				tmp = "";

				// Reset the column count to 1 since we are on a new line
				column = 1;

				// Increase the line count
				line++;
			} else if (*arr == '\n') {
				line++;
			}

			//if (bParse) printf("NL: %s\n", tmp.c_str());
			//printf("( = %i, { = %i, [ = %i\n", curvedBraceLevel, squiglyBraceLevel, squareBraceLevel);

			// Add the character to tmp
			tmp += *arr;

			// Move to next character
			arr++;

			// Increase column count
			column++;
		}

		Gecko::lexer_position_node_t* pos = new Gecko::lexer_position_node_t;
		Gecko::lexer_child_string_t* child = new Gecko::lexer_child_string_t;

		pos->column = column;
		pos->line = line;

		child->position = pos;

		next_node->children.push_back(child);

		return nodes;
	}

	char* lexer_node_to_string(lexer_node_t* node) {
		char* s = new char[1024];
		sprintf(s, "-> %s", node->consumer_label.c_str());
		return s;
	};

	void print_lexer_node(lexer_node_t* node) {
		lexer_node_t* n = node;
		printf("Directive: %s\n", n->consumer_label.c_str());
		vector<Gecko::lexer_child_string_t*> children = n->children;

		for (int i = 0; i < children.size(); i++) {
			printf("[%i] %s\n", i, children[i]->value.c_str());
		}
		printf("\n");
	};
}