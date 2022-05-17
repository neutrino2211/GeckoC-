#ifndef G_KEYWORD_H
#define G_KEYWORD_H

#include <string>
#include <vector>
#include <functional>
#include "lexer.h"
#include "ast.h"
#include "errors.h"

extern map<string, void*>* GECKO_KEYWORDS;

class Keyword;

class KeywordRules {
    std::vector<std::string> instructions;
    std::vector<KeywordRules*> branches;
    std::vector<std::function<void ()>> ops;
    Keyword* parent;
    Gecko::Error::Scope* error;
    public:
    bool terminate = false;

    KeywordRules(Keyword* k);

    std::vector<std::string> GetInstructions();

    KeywordRules* Capture(std::string keywordStorageKey);
    KeywordRules* Expect(std::string token);
    KeywordRules* If(std::string token, KeywordRules* rules);
    KeywordRules* Or(std::string token, KeywordRules* rules);
    KeywordRules* Else(KeywordRules* rules);
    KeywordRules* EndIf();
    KeywordRules* Next();
    KeywordRules* Run(std::function<void ()>);
    KeywordRules* Branch(KeywordRules* rules);
    void End();
    KeywordRules* CaptureBlock(std::string keywordStorageKey);


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