#include "includes/keyword.h"

KeywordRules::KeywordRules (Keyword* k) {
    parent = k;
    error = new Gecko::Error::Scope(parent->name.c_str());
}

std::vector<std::string> KeywordRules::GetInstructions() {
    return instructions;
}

KeywordRules* KeywordRules::Capture(std::string store) {
    instructions.push_back("s " + store);

    return this;
}

KeywordRules* KeywordRules::Expect(std::string token) {
    instructions.push_back("e " + token);

    return this;
}

KeywordRules* KeywordRules::EndIf() {
    instructions.push_back("x ");
    return this;
}

KeywordRules* KeywordRules::Or(std::string token, KeywordRules* rules) {
    instructions.push_back("o " + token);
    branches.push_back(rules);
    return this;
}

KeywordRules* KeywordRules::If(std::string token, KeywordRules* rules) {
    instructions.push_back("i " + token);
    branches.push_back(rules);
    return this;
}

KeywordRules* KeywordRules::Next() {
    instructions.push_back("n ");
    return this;
}

void KeywordRules::End() {
    instructions.push_back("t ");
}

KeywordRules* KeywordRules::CaptureUntilNext(std::string store) {
    instructions.push_back("u " + store);

    return this;
}

KeywordRules* KeywordRules::CaptureBlock(std::string store) {
    instructions.push_back("b " + store);

    return this;
}

bool KeywordRules::Validate(Gecko::lexer_node_t& node) {
    Gecko::lexer_node_t* l_node = &node; 
    Gecko::lexer_node_t* encounteredErrorNode = nullptr;
    uint16_t branch = 0;
    bool evaluateBranches = true;
    
    printf("loop\n");
    for (auto instruction : instructions) {
        if (encounteredErrorNode != nullptr) break;
        printf("[%s] [%s] [%i]\n", instruction.c_str(), l_node->value.c_str(), encounteredErrorNode == nullptr);

        std::string value = instruction.substr(2);
        if (instruction[0] == 's') parent->data[value] = l_node->value;
        else if(instruction[0] == 'n') ; // Do nothing
        else if (instruction[0] == 'e' && value != l_node->value) encounteredErrorNode = &(*l_node) ; // Copy node for local use
        else if ((instruction[0] == 'o' || instruction[0] == 'i') && evaluateBranches) {
            printf("Pre-error %s %s\n", l_node->value.c_str(), value.c_str());
            if(value != l_node->value && branch == branches.size() - 1) {
                encounteredErrorNode = &(*l_node); // Copy node for local use
            } else if (value == l_node->value) {
                auto branch_valid = branches.at(branch)->Validate(*l_node);
                if(!branch_valid) encounteredErrorNode = &(*l_node);
                evaluateBranches = false;
            } else {
                l_node = l_node->prev;
            }
            branch++;

        } else if (instruction[0] == 'x') {
            evaluateBranches = false;
        } else if (instruction[0] == 'b') {
            if (l_node->options->isCodeBlock) {
                parent->data[value] = l_node->value.substr(1, l_node->value.length() - 1);
            } else {
                encounteredErrorNode = &(*l_node); // Copy node for local use
            }
        } else if (instruction[0] == 'u') {
            if (parent->data[value] == "") {
                parent->data[value] = l_node->value;
            } else {
                parent->data[value] += " " + l_node->value;
            }
            printf("end u\n");
        } else if (instruction[0] == 't') {
            node = *l_node;
            printf("endloop\n");
            return true;
        }

        if (evaluateBranches && l_node->next != nullptr) l_node = l_node->next;
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