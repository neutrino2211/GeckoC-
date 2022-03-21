#include "includes/keywords.h"

GeckoConst::GeckoConst() {
    name = "const";
    modifiers = { {"private", "public", "protected"} };
    // const hello: string = "Hello World"

    KeywordRules* implicitRules = new KeywordRules(this);
    KeywordRules* explicitRules = new KeywordRules(this);

    implicitRules
    ->Expect("=")
    ->CaptureUntilNext("expression");

    explicitRules
    ->Next()
    ->Capture("type")
    ->Expect("=")
    ->CaptureUntilNext("expression");

    rules
    ->Next()
    ->Capture("name")
    ->If(":", explicitRules)
    ->Or("=", implicitRules)
    ->EndIf();
}

bool GeckoConst::shouldAwaitCodeBlock() {
    return false;
}

bool GeckoConst::shouldConsume(Gecko::lexer_node_t* node) {
    return true;
}

void GeckoConst::processNode(Gecko::AST::ast_node_t* node) {
    return;
}