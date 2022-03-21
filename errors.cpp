
#include "includes/errors.h"
#include "includes/utils.h"
#include "includes/colors.h"
#include <iostream>

std::string generateCodeErrorFromNode(Gecko::lexer_node_t* node) {
    std::string r = "";

    if (node == nullptr) return r.c_str();

    std::vector<std::string>* lines = Gecko::Utils::split(node->lexer->source(), "\n");

    std::string preceeding_line =  lines->at(node->position->line - 2);
    std::string line = lines->at(node->position->line - 1);
    std::string next_line = lines->at(node->position->line);

    std::string underline = "";

    for (int i = 0; i < line.length(); i++) {
        if (i >= node->position->column - node->value.length() - 1 && i < node->position->column - 1) underline += colors::style::bold(colors::bg::red(" "));
        else underline += " ";
    }

    r += "\t  " + std::to_string(node->position->line - 1) + "| " + preceeding_line + '\n';
    r += "\t> " + std::to_string(node->position->line) + "| " + line + '\n';
    r += "\t     " + underline + "\n";
    r += "\t  " + std::to_string(node->position->line + 1) + "| " + next_line + '\n';

    r += '\n';
    return r;
}

namespace Gecko {
    namespace Error {
        Scope::Scope(const char* scope) {
            mScope = scope;
        }

        void Scope::raise(ExitCodes code, const char* message, const char* errorType = "Error") {
            printf("%s: [%s] %s", errorType, mScope, message);
            exit(code);
        }

        void Scope::raise(ExitCodes code, const char* message, const char* errorType = "Error", Gecko::lexer_node_t* node = nullptr) {
            printf("%s: [%s] %s\n%s", errorType, mScope, message, generateCodeErrorFromNode(node).c_str());
            exit(code);
        } 
    }
}