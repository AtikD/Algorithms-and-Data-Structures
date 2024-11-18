// Copyright 2024 atikdd.t.me

#include "../include/parser.h"
#include <cctype>
#include <string>

bool ExpressionParser::isValidExpression(const std::string* expression) {
    if (expression == nullptr) {
        return false;
    }

    for (size_t i = 0; i < expression->length(); ++i) {
        char c = (*expression)[i];
        if (!isAllowedCharacter(c)) {
            return false;
        }
    }

    if (!areBracketsBalanced(expression)) {
        return false;
    }

    return true;
}

bool ExpressionParser::isAllowedCharacter(char c) {
    // Допустимые символы
    return std::isalnum(static_cast<unsigned char>(c)) || c == '+' ||
           c == '-' || c == '*' || c == '/' || c == '^' || c == '|' ||
           c == '(' || c == ')' || c == '[' || c == ']' || c == '{' ||
           c == '}' || c == ' ' || c == '.';
}

bool ExpressionParser::areBracketsBalanced(const std::string* expression) {
    Stack<char> bracketStack;
    for (size_t i = 0; i < expression->length(); ++i) {
        char c = (*expression)[i];
        if (c == '(' || c == '[' || c == '{' || c == '|') {
            if (
                c == '|' &&
                !bracketStack.empty() &&
                bracketStack.top() == '|'
            ) {
                bracketStack.pop();
            } else {
                bracketStack.push(c);
            }
        } else if (c == ')' || c == ']' || c == '}' || c == '|') {
            if (bracketStack.empty()) {
                return false;
            }
            char top = bracketStack.top();
            if ((c == ')' && top == '(') ||
                (c == ']' && top == '[') ||
                (c == '}' && top == '{') ||
                (c == '|' && top == '|')) {
                bracketStack.pop();
            } else {
                return false;
            }
        }
    }
    return bracketStack.empty();
}
