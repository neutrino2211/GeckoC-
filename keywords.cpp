#include "includes/keywords.h"

GeckoConst::GeckoConst() {
    name = "const";
    modifiers = { {"private", "public", "protected"} };
    isModifier = false;
    // const hello: string = "Hello World"

    KeywordRules* implicitRules = new KeywordRules(this);
    KeywordRules* explicitRules = new KeywordRules(this);

    implicitRules
    ->Expect("=")
    ->CaptureUntilNext("expression")
    ->End();

    explicitRules
    ->Next()
    ->Capture("type")
    ->Expect("=")
    ->CaptureUntilNext("expression")
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