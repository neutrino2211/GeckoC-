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
    std::vector<KeywordRules*> branches;
    Keyword* parent;
    Gecko::Error::Scope* error;
    public:

    KeywordRules(Keyword* k);

    std::vector<std::string> GetInstructions();

    KeywordRules* Capture(std::string keywordStorageKey);
    KeywordRules* Expect(std::string token);
    KeywordRules* If(std::string token, KeywordRules* rules);
    KeywordRules* Or(std::string token, KeywordRules* rules);
    KeywordRules* EndIf();
    KeywordRules* Next();
    void End();
    KeywordRules* CaptureBlock(std::string keywordStorageKey);
    KeywordRules* CaptureUntilNext(std::string keywordStorageKey);


    bool Validate(Gecko::lexer_node_t& node);
};

class Keyword {
    public:
    bool isModifier;
    /* data */
    Keyword() {
        rules = new KeywordRules(this);
    };
    std::string name;
    KeywordRules* rules;

    std::vector<std::vector<std::string>> modifiers;
    std::map<std::string, std::string> data;
    std::map<std::string, bool> modifierData;

    virtual Keyword* New() = 0;
};
#endif