# CMakeList.txt : CMake project for Gecko, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Gecko")

# Add source to this project's executable.
add_executable (Gecko "Gecko.cpp" "Gecko.h" "readfile.cpp" "commander.cpp" "includes/readfile.h" "lexer.cpp" "includes/lexer.h"  "utils.cpp" "includes/utils.h" "ast.cpp" "includes/ast.h" "parser.cpp" "includes/parser.h" "includes/directives.h"  "includes/asts/declarations.h" "includes/directives/declarations.h")

# TODO: Add tests and install targets if needed.
