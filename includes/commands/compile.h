#ifndef G_COMMAND_COMPILE_H
#define G_COMMAND_COMPILE_H

#include "../commander.h"

OptionListener helpOption = {
    .type = BooleanOption,
    .help = "print help for compile command",
    .hasListener = false,
};

namespace Commands {
    class Compile : public Command {
        void run() override;
        public:
        Compile();
    };

    Compile::Compile() {
        name = "compile";
        usage = "compile [source files...]";
        description = "compile a gecko source file or project";

        options = {
            {
                "help", &helpOption
            }
        };
    }

    void Compile::run() {
        bool printHelp = values["help"] == "true";
        
        if (printHelp || positionals.size() == 0) {
            printf("%s\n", buildHelp().c_str());
            return;
        }

        std::vector<std::string> files = positionals;


        for (auto file : files) {
            std::string content = Gecko::readfile(file.c_str());
            Gecko::Lexer* lexer = new Gecko::Lexer(content + "\n\n", {':', '=', ';'});

            vector<Gecko::lexer_node_t>* result = lexer->parse();
            Gecko::Parser parser(result);

            parser.registerKeyword(new GeckoConst);

            parser.parse();
        }
    };
}

#endif