// Copyright 2024 atikdd.t.me

#include "../include/lexem.h"
#include <parser.h>
#include <iostream>
#include <string>
#include <vector>

bool LexemFactory::isFunction(const std::string& token) {
    static const std::vector<std::string> funcs = {"sin", "cos", "tg", "ctg"};
    return std::find(funcs.begin(), funcs.end(), token) != funcs.end();
}

bool LexemFactory::isOperator(const std::string& token) {
    static const std::string ops = "+-*/^";
    return token.size() == 1 && ops.find(token[0]) != std::string::npos;
}

bool LexemFactory::isBracket(const std::string& token) {
    return token == "(" || token == ")";
}

bool LexemFactory::isNumber(const std::string& token) {
    if (token.empty()) return false;
    bool hasDigit = false;
    for (char c : token) {
        if (!(std::isdigit(static_cast<unsigned char>(c)) || c== '.'))
            return false;
        if (std::isdigit(static_cast<unsigned char>(c)))
            hasDigit = true;
    }
    return hasDigit;
}

Lexem* LexemFactory::create(const std::string& token) {
    if (isFunction(token)) return new Function(token);
    if (isOperator(token)) return new Operation(token);
    if (isBracket(token)) return new Bracket(token);
    if (isNumber(token)) {
        if (token.find('.') != std::string::npos)
            return new FloatConst(token);
        else
            return new IntConst(token);
    }
    return new Variable(token);
}

void delete_spaces(std::string* exp) {
    if (exp == nullptr) return;
    exp->erase(std::remove_if(exp->begin(), exp->end(), isspace), exp->end());
}

static bool isOperatorChar(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

TList<Lexem*> parse(const std::string& input) {
    std::string exp = input;
    ExpressionParser v;
    if (!v.isValidExpression(&input))
        throw std::runtime_error("The brackets are specified incorrectly.");
    delete_spaces(&exp);
    TList<Lexem*> lexems;

    size_t i = 0;
    Lexem* prev_lex = nullptr;
    while (i< exp.size()) {
        char c = exp[i];

        if (std::isdigit(static_cast<unsigned char>(c)) || c == '.') {
            std::string number;
            number += c;
            i++;
            while (i < exp.size()
                    && (std::isdigit(static_cast<unsigned char>(exp[i]))
                    || exp[i] == '.')) {
                number += exp[i];
                i++;
            }
            lexems.push_back(LexemFactory::create(number));
            prev_lex = nullptr;
            continue;
        }

        if (std::isalpha(static_cast<unsigned char>(c))) {
            std::string name;
            name += c;
            i++;
            while (i < exp.size() &&
                (std::isalnum(static_cast<unsigned char>(exp[i])))) {
                name += exp[i];
                i++;
            }
            lexems.push_back(LexemFactory::create(name));
            prev_lex = nullptr;
            continue;
        }

        if (c == '(' || c == ')') {
            if (c == ')')
                if (prev_lex && prev_lex->type() == OPERATION)
                throw std::runtime_error("Invalid operator sequence detected.");
            std::string bracket(1, c);
            lexems.push_back(LexemFactory::create(bracket));
            i++;
            prev_lex = nullptr;
            continue;
        }

        if (isOperatorChar(c)) {
            if (prev_lex && prev_lex->type() == OPERATION)
                throw std::runtime_error("Invalid operator sequence detected.");
            std::string op(1, c);
            Lexem* new_op = LexemFactory::create(op);
            lexems.push_back(new_op);
            prev_lex = new_op;
            i++;
            continue;
        }

        throw std::runtime_error("An unknown character was found.");
        i++;
    }

    return lexems;
}
