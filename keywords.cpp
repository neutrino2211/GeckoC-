#include "includes/keywords.h"

GeckoConst::GeckoConst() {
    name = "const";
    modifiers = { {"private", "public", "protected"} };
    // const hello: string = "Hello World"
    rules
    ->Capture("name")
    ->Expect(":")
    ->Capture("type")
    ->Or("=")
    ->CaptureUntilNext("expression");
}

bool GeckoConst::shouldAwaitCodeBlock() {
    return false;
}

bool GeckoConst::shouldConsume(Gecko::lexer_node_t* node) {
    bool isImplicit = node->next->next->value == "=";
    std::string type = "";

    if (!isImplicit) {
        type = node->next->next->next->value;
        printf("Help: %s\n", node->next->next->next->value.c_str());
    }

    printf("type: %s\n", type.c_str());

    return isImplicit;
}

void GeckoConst::processNode(Gecko::AST::ast_node_t* node) {
    return;
}