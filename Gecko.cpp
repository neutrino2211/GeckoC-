// Gecko.cpp : Defines the entry point for the application.
//

#include "Gecko.h"

using namespace std;

int main()
{
	string txt = Gecko::readfile("../../../tests/test.gecko");
	
	Gecko::Lexer lexer(txt + "\n");

	vector<Gecko::lexer_node_t>* result = lexer.parse();

	Gecko::Parser parser(result);
	parser.register_handler("//", commentHandler);
	parser.register_handler("const", declarationsHandler);
	parser.register_handler("let", declarationsHandler);
	parser.parse();
	return 0;
}
