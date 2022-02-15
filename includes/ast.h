#pragma once
#include <string>
#include "lexer.h"

namespace Gecko {

	namespace AST {

		static struct ast_node_t {
			std::string type;
			void* data;
		};

		static struct class_node_t {
			std::string name;
		};

		static struct typeref_node_t {
			std::string name;
			bool is_gecko_type;

			std::string c_type_alias;
			class_node_t* gecko_class;
		};

		static struct variable_node_t {
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
	}

}