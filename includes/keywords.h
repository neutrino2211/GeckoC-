#ifndef G_KEYWORDS_H
#define G_KEYWORDS_H

#include <string>
#include <vector>
#include "lexer.h"

class keyword
{
    /* data */
    std::string name;

    std::vector<std::vector<std::string>> modifiers;

    virtual bool consume(Gecko::lexer_node_t* node);
    virtual bool shouldAwaitCodeBlock();
};


#endif