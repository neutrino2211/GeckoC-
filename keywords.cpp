#include "includes/keywords.h"
#include "includes/expressions.h"

GeckoConst::GeckoConst() {
    name = "const";
    modifiers = { {"private", "public", "protected"} };
    isModifier = false;

    Gecko::Expressions::ExpressionKeyword* expression = new Gecko::Expressions::ExpressionKeyword;
    // const hello: string = "Hello World"

    KeywordRules* implicitRules = new KeywordRules(this);
    KeywordRules* explicitRules = new KeywordRules(this);

    implicitRules
    ->Expect("=")
    ->Next()
    ->Branch(expression->rules)
    ->End();

    explicitRules
    ->Next()
    ->Capture("type")
    ->Expect("=")
    ->Branch(expression->rules)
    ->End();

    rules
    ->Next()
    ->Capture("name")
    ->If(":", explicitRules)
    ->Or("=", implicitRules)
    ->EndIf()
    ->End();
}

Keyword* GeckoConst::New() {
    return new GeckoConst();
}

GeckoPrivateModifier::GeckoPrivateModifier() {
    isModifier = true;

    name = "private";

    rules->End();
}

Keyword* GeckoPrivateModifier::New() {
    return new GeckoPrivateModifier();
}

GeckoPublicModifier::GeckoPublicModifier() {
    isModifier = true;

    name = "public";

    rules->End();
}

Keyword* GeckoPublicModifier::New() {
    return new GeckoPublicModifier();
}

GeckoProtectedModifier::GeckoProtectedModifier() {
    isModifier = true;

    name = "protected";

    rules->End();
}

Keyword* GeckoProtectedModifier::New() {
    return new GeckoProtectedModifier();
}