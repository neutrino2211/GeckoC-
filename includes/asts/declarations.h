#ifndef G_AST_DECLARATIONS_H
#define G_AST_DECLARATIONS_H

#include "../ast.h"

namespace Gecko {
	namespace AST {

		struct declarations_ast_node_t {
			bool is_constant;
			bool is_nullable;
			std::string type_string;
			ast_node_t* expression;
		};

	}
}

#endif // G_AST_DECLARATIONS_H
