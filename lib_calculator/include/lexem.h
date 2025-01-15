// Copyright 2024 atikdd.t.me

#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <list.h>

enum LexemType {
    BRACKET,
    VARIABLE,
    OPERATION,
    FUNCTION,
    INT_CONST,
    FLOAT_CONST
};


class Lexem {
 protected:
    std::string _name;
    LexemType _type;

 public:
    Lexem(std::string name, LexemType type): _name(name), _type(type) {}
    virtual ~Lexem() = default;

    std::string name() const { return _name; }
    LexemType type() const { return _type; }

    friend std::ostream& operator<<(std::ostream& out, const Lexem& lex) {
        out << lex._name;
        return out;
    }
};

class FloatConst : public Lexem {
    float _value;
 public:
    explicit FloatConst(const std::string& exp):
            Lexem(exp, FLOAT_CONST),
            _value(std::stof(exp)) {}
    float value() const { return _value; }
};

class IntConst : public Lexem {
    int _value;
 public:
    explicit IntConst(const std::string& exp):
        Lexem(exp, INT_CONST),
        _value(std::stoi(exp)) {}
    int value() const { return _value; }
};

class Variable : public Lexem {
 public:
    explicit Variable(const std::string& name):
        Lexem(name, VARIABLE) {}
};

class Function : public Lexem {
 public:
    explicit Function(const std::string& name):
        Lexem(name, FUNCTION) {}
};

class Operation : public Lexem {
 public:
    explicit Operation(const std::string& op):
        Lexem(op, OPERATION) {}
};

class Bracket : public Lexem {
 public:
    explicit Bracket(const std::string& name):
        Lexem(name, BRACKET) {}
};

class LexemFactory {
 public:
    static Lexem* create(const std::string& token);

 private:
    static bool isFunction(const std::string& token);
    static bool isOperator(const std::string& token);
    static bool isBracket(const std::string& token);
    static bool isNumber(const std::string& token);
};

void delete_speces(std::string* exp);

TList<Lexem*> parse(const std::string& input);
