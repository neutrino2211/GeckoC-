#include <algorithm>
#include "includes/lexer.h"

using namespace std;

namespace Gecko {

	Lexer::Lexer(string input, vector<char> forcedTokenizedChars) {
		mInput = input;
		mForcedTokenizedChars = forcedTokenizedChars;
	}

	vector<lexer_node_t>* Lexer::parse() {
		char* arr = Utils::string_to_chr_array(mInput);
		string tmp = "";
		vector<lexer_node_t>* nodes = new vector<lexer_node_t>();
		lexer_node_t* current_node = new lexer_node_t;
		init_node(current_node);


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

			if (std::find(mForcedTokenizedChars.begin(), mForcedTokenizedChars.end(), *arr) != mForcedTokenizedChars.end() && bParse) {

				Gecko::Utils::ltrim(tmp);
				Gecko::lexer_position_node_t* previous_pos = new Gecko::lexer_position_node_t;
				Gecko::lexer_position_node_t* current_token_pos = new Gecko::lexer_position_node_t;
				Gecko::lexer_node_options_t* options = new Gecko::lexer_node_options_t;

				Gecko::lexer_node_t* next = new Gecko::lexer_node_t;
				Gecko::lexer_node_t* previous = new Gecko::lexer_node_t;

				previous_pos->column = column-1;
				previous_pos->line = line;

				current_token_pos->column = column;
				current_token_pos->line = line;


				previous->value = current_node->value;
				previous->position = previous_pos;
				previous->options = options;
				previous->prev = current_node->prev;
				previous->next = current_node;

				current_node->value = tmp.substr(0, tmp.length()).c_str();
				current_node->position = current_token_pos;
				current_node->options = options;
				current_node->prev = previous;
				current_node->next = next;

				next->prev = current_node;
				next->value = *arr;

				nodes->push_back(*previous);
				nodes->push_back(*current_node);

				current_node = next;

				tmp = "";
				arr++;
			} else if (*arr == ' ' && bParse && tmp != "") {
				Gecko::Utils::ltrim(tmp);
				
				Gecko::lexer_position_node_t* pos = new Gecko::lexer_position_node_t;
				Gecko::lexer_node_options_t* options = new Gecko::lexer_node_options_t;

				pos->column = column;
				pos->line = line;

				options->isCodeBlock = bIsCodeBlock;
				
				if (current_node->value.empty()) {
					// printf("[TMP]%s", tmp.c_str());
					Utils::ltrim(tmp);
					current_node->value = tmp.c_str();
					current_node->position = pos;
					current_node->options = options;
				}
				else {

					Gecko::lexer_node_t* next = new Gecko::lexer_node_t;

					next->value = tmp.c_str();
					next->position = pos;
					next->options = options;

					current_node->next = next;
					next->prev = current_node;

					nodes->push_back(*current_node);

					current_node = next;
				}

				// tmp has been comitted to a node, reset it
				tmp = "";
				bIsCodeBlock = false;
			}
			else if (*arr == '\n' && bParse && tmp != "") {
				Gecko::Utils::ltrim(tmp);
				//print_lexer_node(current_node);
				Gecko::lexer_position_node_t* pos = new Gecko::lexer_position_node_t;
				Gecko::lexer_node_t* next = new Gecko::lexer_node_t;

				// Set the token position
				pos->column = column;
				pos->line = line;
				next->position = pos;

				// Set the value of the token
				next->value = tmp.c_str();

				// Add this last identified token to the node's children vector
				// current_node->children.push_back(child);

				// Make a copy of the completed node
				// lexer_node_t n = *current_node;
				
				// Clear the node
				// init_node(current_node);

				// Set the current node's prev as the just completed node
				next->prev = current_node;
				// Set the next of the just completed node to this new node
				current_node->next = next;

				// Push the completed node to the nodes vector
				nodes->push_back(*current_node);

				current_node = next;

				// printf("%s\n", tmp.c_str());

				// tmp has been comitted to a node, reset it
				tmp = "";

				bIsCodeBlock = false;

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
		Gecko::lexer_node_options_t* options = new Gecko::lexer_node_options_t;

		pos->column = column;
		pos->line = line;

		current_node->position = pos;

		options->isCodeBlock = bIsCodeBlock;

		current_node->options = options;

		bIsCodeBlock = false;

		return nodes;
	}

	char* lexer_node_to_string(lexer_node_t* node) {
		char* s = new char[1024];
		sprintf(s, "-> %s", node->value.c_str());
		return s;
	};

	void print_lexer_node(lexer_node_t* node) {
		lexer_node_t* n = node;
		printf("Directive: %s\n", n->value.c_str());
		printf("\n");
	};
}