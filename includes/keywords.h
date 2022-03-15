#ifndef G_KEYWORDS_H
#define G_KEYWORDS_H

#include "./keyword.h"

class GeckoConst : public Keyword {

    public:
    GeckoConst();

    bool shouldAwaitCodeBlock() override;
    void processNode(Gecko::AST::ast_node_t* node) override;
    bool shouldConsume(Gecko::lexer_node_t* node) override;
};



#endif