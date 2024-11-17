// Copyright 2024 atikdd.t.me

#pragma once

#include <string>
#include <stack.h>

class ExpressionParser {
 public:
    bool isValidExpression(const std::string* expression);

 private:
    // Вспомогательный метод для проверки скобок
    bool areBracketsBalanced(const std::string* expression);

    // Проверяет, является ли символ допустимым
    bool isAllowedCharacter(char c);
};

