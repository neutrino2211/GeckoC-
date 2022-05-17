#ifndef GECKO_EXPRESSIONS_H
#define GECKO_EXPRESSIONS_H

#include <string>
#include <iostream>
#include "keyword.h"

struct Expression {
    Expression* left;
    Expression* right;

    char op;

    std::string value;
};

namespace Gecko {
    namespace Expressions {
        Expression* Parse(std::string input) {
            Gecko::Lexer* l = new Gecko::Lexer(input + " \n\n", {'*', '+', '-', '/', '%', '&', '!', '|'});
            std::vector<Gecko::lexer_node_t*>* nodes = l->parse();
            printf("SIZE: %s\n", nodes->at(0)->value.c_str());
            Expression* exp = new Expression;

            

            return exp;
        }

        class ExpressionKeyword: public Keyword {
            public:

            ExpressionKeyword() {
                name = "expression";

                KeywordRules* unaryExpression = new KeywordRules(this);
                unaryExpression->Capture("unary_operator")->Capture("unary_operand");

                KeywordRules* binaryExpression = new KeywordRules(this);
                binaryExpression->Capture("binary_operator")->Capture("binary_operand_2");

                vector<map<string, string>>* expressions = new vector<map<string, string>>;
                map<string, string>* data_pointer = &this->data;

                rules
                // Unary expressions
                ->If("+", unaryExpression)
                ->Or("-", unaryExpression)
                ->Or("/", unaryExpression)
                ->Or("*", unaryExpression)
                // binary expressions
                ->Capture("binary_operand_1")
                ->If("+", binaryExpression)
                ->Or("-", binaryExpression)
                ->Or("/", binaryExpression)
                ->Or("*", binaryExpression)
                ->Run([data_pointer, expressions](){
                    printf("%i %i\n", data_pointer, expressions);
                    expressions->push_back(*data_pointer);
                })
                ->If("+", rules)
                ->Or("-", rules)
                ->Or("/", rules)
                ->Or("*", rules)
                ->EndIf()
                ->Run([expressions](){
                    for (auto expr : *expressions) {
                        for (auto expr_data : expr) {
                            std::cout << "{" << expr_data.first << ": " << expr_data.second << "}\n";
                        }
                    }
                });
            }

            Keyword* New() {
                return new ExpressionKeyword();
            }
        };
    }
}

#endif // GECKO_EXPRESSIONS_H