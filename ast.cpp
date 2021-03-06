#include "includes/ast.h"

namespace Gecko {

	namespace AST {

		namespace Utils {
			
			bool isValidDeclaration (Gecko::lexer_node_t* n) {
				std::string var_name = n->next->value;
				std::string possible_type = n->next->next->value;

				if (var_name.back() == ':') {
					var_name = var_name.substr(0, var_name.length() - 2);
				}
				else if (possible_type == ":") {
					possible_type = n->next->next->value;
				}
				else if (possible_type.at(0) == ':') {
					printf("%s\n", possible_type.c_str());
					//possible_type = possible_type.substr(1);
				}
				else {
					return false;
				}

				return true;
			}

			bool isImplicitDeclaration(Gecko::lexer_node_t* n) {
				// The second text-node is an "=" sign therefore no type declrations
				return n->next->next->value == "=";
			}
		
		}

	}

}