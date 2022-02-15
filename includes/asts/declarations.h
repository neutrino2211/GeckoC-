#pragma once

#include "../ast.h"

namespace Gecko {
	namespace AST {

		static struct declarations_ast_node_t {
			bool is_constant;
			std::string type_string;
			ast_node_t* expression;
		};

	}
}