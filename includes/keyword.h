#ifndef G_KEYWORD_H
#define G_KEYWORD_H

#include <string>
#include <vector>
#include "lexer.h"
#include "ast.h"
#include "errors.h"

class Keyword;

class KeywordRules {
    std::vector<std::string> instructions;
    Keyword* parent;
    Gecko::Error::Scope* error;
    public:

    KeywordRules(Keyword* k);

    KeywordRules* Capture(std::string keywordStorageKey);
    KeywordRules* Expect(std::string token);
    KeywordRules* Or(std::string token);
    KeywordRules* CaptureBlock(std::string keywordStorageKey);
    KeywordRules* CaptureUntilNext(std::string keywordStorageKey);

    bool Validate(Gecko::lexer_node_t* node);
};

class Keyword {
    public:
    /* data */
    Keyword() {
        rules = new KeywordRules(this);
    };
    std::string name;
    KeywordRules* rules;

    std::vector<std::vector<std::string>> modifiers;
    std::map<std::string, std::string> data;

    virtual bool shouldConsume(Gecko::lexer_node_t* node) = 0;
    virtual void processNode(Gecko::AST::ast_node_t* ast) = 0;
    virtual bool shouldAwaitCodeBlock() = 0;
};
#endif