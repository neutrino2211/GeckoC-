#ifndef G_KEYWORDS_H
#define G_KEYWORDS_H

#include <string>
#include <vector>
#include "lexer.h"
#include "ast.h"

class keyword
{
    public:
    /* data */
    std::string name;

    std::vector<std::vector<std::string>> modifiers;

    virtual bool shouldConsume(Gecko::lexer_node_t* node);
    virtual void processNode(Gecko::AST::ast_node_t* ast);
    virtual bool shouldAwaitCodeBlock();
};

void keyword::processNode(Gecko::AST::ast_node_t* ast) {};
bool keyword::shouldAwaitCodeBlock() {
    return false;
}
bool keyword::shouldConsume(Gecko::lexer_node_t* node) {
    return false;
}

class GeckoConst : public keyword {

    GeckoConst();

    bool shouldAwaitCodeBlock() override;
};

GeckoConst::GeckoConst() {
    name = "const";
    modifiers = { {"private", "public", "protected"}, {"async"} };
}

bool GeckoConst::shouldAwaitCodeBlock() {
    return false;
}



#endif