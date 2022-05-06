#include "includes/parser.h"
#include "includes/errors.h"

Gecko::Error::Scope* scope = new Gecko::Error::Scope("Parser");
template<typename K, typename V>
		std::ostream &operator<<(std::ostream &os,
								const std::map<K, V> &m) {
			for (const std::pair<K, V> &p: m) {
				os << "{" << p.first << ": " << p.second << "}\n";
			}
			return os;
		}
namespace Gecko {

	Parser::Parser(vector<lexer_node_t*>* nodes) {
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

		vector<lexer_node_t*>* lNodes = new vector<lexer_node_t*>;

		uint64_t nodeIndex = 0;
		for (lexer_node_t* node : *mNodes) {
			Gecko::Utils::trim(node->value);
			if (node->value != "") {
				lNodes->push_back(node);
			};
		}

		for (lexer_node_t* node : *lNodes) {
			if(nodeIndex == 0) {
				node->prev = nullptr;
			} else if (nodeIndex < lNodes->size() - 1) {
				node->prev = lNodes->at(nodeIndex - 1);
				node->prev->next = node;
				node->next = lNodes->at(nodeIndex + 1);
			} else {
				node->next = nullptr;
			}
			nodeIndex++;
		}

		// mNodes = lNodes;
		lexer_node_t* node = lNodes->at(0);
		// print_lexer_node(node);
		while (node->next != nullptr) {
			printf("Node: %s\n", node->value.c_str());
			if (node->value != "") {
				Keyword* k = ((Keyword*) keywords[node->value]);

				if (!k) {
					scope->raise(
						Gecko::Error::SourceFileParsingError,
						("\"" + node->value + "\" is not a valid keyword").c_str(),
						"InvalidKeyword",
						node
					);
					return;
				};

				k = k->New();

				if (k->isModifier) {
					activeModifiers.push_back(k);
					node = node->next;
					continue;
				}

				if (matchedKeyword != nullptr) {
					std::string message = "Not expecting keyword \"" + node->value + "\" at this location\n";
					// sprintf(message, node.value.c_str());
					// printf("ERROR\n");
					scope->raise(Gecko::Error::SourceFileParsingError, message.c_str(), "SyntaxError", node); 
				}

				if (k->name == node->value) {
					// matchedKeyword = k;
					// printf("should consume: %i\n", k->shouldConsume(&node));
					printf("START\n");
					k->rules->Validate(*node);
					// for (auto i : k->rules->GetInstructions()) {
					// 	printf("Instructions: %s [%s]\n", i.c_str(), node->value.c_str());
					// 	node = node->next;
					// }
					for (auto mod : activeModifiers) {
						k->modifierData[mod->name] = true;
					}

					printf("MAP\n");
					// Gecko::Utils::printMap<std::string, std::string>(k->data);
					std::cout << k->data;
					std::cout << k->modifierData;

					activeModifiers = {};
				}
			}

			// printf("%i\n\n", node == nullptr);
			// node = node->next;
			// printf("%i\n\n", node == nullptr);
		}
	}
}