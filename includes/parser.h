#ifndef G_PARSER_H
#define G_PARSER_H

#include "lexer.h"
#include "keyword.h"
#include <map>

namespace Gecko {

	namespace ParserUtils {
		typedef void (*DirectiveHandler) (lexer_node_t);
	}

	class Parser {

	private:
		vector<lexer_node_t*>* mNodes;
		map<string, Keyword*> keywords;
		map<string, ParserUtils::DirectiveHandler> handlers;

	public:
		Parser(vector<lexer_node_t*>* nodes);

		void register_handler(string directive, ParserUtils::DirectiveHandler h);
		void registerKeyword(Keyword* k);

		void parse();
	};

}

#endif // G_PARSER_H
