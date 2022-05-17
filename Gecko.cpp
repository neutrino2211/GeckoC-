// Gecko.cpp : Defines the entry point for the application.
//

#include "Gecko.h"
#include "golang/build/go-parser.h"

using namespace std;

int main(int argc, char** argv)
{
    Commander* c = new Commander(argc, argv);

	Commands::Compile* compileCommand = new Commands::Compile();

	GoParser("32 + 4 - \"this is a help string\"");

	c->registerCommand("compile", compileCommand);
	c->parse();
	// string txt = Gecko::readfile("../tests/test.gecko");
	

	// vector<char> forcedTokenizedChars = {':', '=', ';'};
	// Gecko::Lexer lexer(txt + "\n", forcedTokenizedChars);

	// vector<Gecko::lexer_node_t>* result = lexer.parse();

	// Gecko::Parser parser(result);
	// parser.parse();
    // system("pwd");
    // system("read -n1 -r -p \"Press any key to continue...\"");
	return 0;
}
