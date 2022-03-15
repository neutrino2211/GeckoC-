#include "includes/keyword.h"

KeywordRules::KeywordRules (Keyword* k) {
    parent = k;
    error = new Gecko::Error::Scope(parent->name.c_str());
}

KeywordRules* KeywordRules::Capture(std::string store) {
    instructions.push_back("s " + store);

    return this;
}

KeywordRules* KeywordRules::Expect(std::string token) {
    instructions.push_back("e " + token);

    return this;
}

KeywordRules* KeywordRules::Or(std::string token) {
    instructions.push_back("o " + token);

    return this;
}

KeywordRules* KeywordRules::CaptureUntilNext(std::string store) {
    instructions.push_back("u " + store);

    return this;
}

KeywordRules* KeywordRules::CaptureBlock(std::string store) {
    instructions.push_back("b " + store);

    return this;
}

bool KeywordRules::Validate(Gecko::lexer_node_t* node) {
    Gecko::lexer_node_t* l_node = &(*node); // Copy node for local use
    Gecko::lexer_node_t* encounteredErrorNode = nullptr;
    
    for (auto instruction : instructions) {
        std::string value = instruction.substr(2);
        if (instruction[0] == 's') parent->data[value] = l_node->value;
        else if (instruction[0] == 'e' && value != l_node->value) encounteredErrorNode = l_node;
        else if (instruction[0] == 'o' && value != l_node->value) encounteredErrorNode = l_node;
        else if (instruction[0] == 'b') {
            if (l_node->options->isCodeBlock) {
                parent->data[value] = l_node->value.substr(1, l_node->value.length() - 1);
            } else {
                encounteredErrorNode = l_node;
            }
        } else if (instruction[0] == 'u') {
            if (parent->data[value] == "") {
                parent->data[value] = l_node->value;
            } else {
                parent->data[value] += " " + l_node->value;
            }
        }

        l_node = l_node->next;
    }

    if (encounteredErrorNode != nullptr) {
        error->raise(
            Gecko::Error::KeywordValidationError, 
            ("not expecting \"" + encounteredErrorNode->value + "\" at this point").c_str(), "ValidationError", 
            encounteredErrorNode
        );
        return false;
    }
    return true;
}