#ifndef G_AST_H
#define G_AST_H
#include <string>
#include <map>
#include "lexer.h"

namespace Gecko {

	namespace AST {

		struct ast_node_t {
			std::string type;
			void* data;
		};

		struct class_node_t {
			std::string name;
		};

		struct typeref_node_t {
			std::string name;
			bool is_gecko_type;

			std::string c_type_alias;
			class_node_t* gecko_class;
		};

		struct variable_node_t {
			std::string name;
			bool is_constant;
			bool is_nullable;

			typeref_node_t* type;
			std::string visibility;
		};

		namespace Utils {
			bool isValidDeclaration(Gecko::lexer_node_t*);
			bool isImplicitDeclaration(Gecko::lexer_node_t*);
		}

		class Ast {
		private:
			std::map<std::string, class_node_t*> classes;
			std::map<std::string, variable_node_t*> variables;
			
		};
	}

}
#endif
