// Copyright 2024 atikdd.t.me

#include <gtest/gtest.h>
#include <lexem.h>
#include <list.h>
#include <string>

int CountLexems(const TList<Lexem*>& list) {
    int count = 0;
    for (auto it = list.begin(); it != list.end(); ++it) count++;
    return count;
}

void FreeLexems(TList<Lexem*>* list) {
    for (auto it = list->begin(); it != list->end(); ++it) {
        delete *it;
    }
}

TEST(LexemParseTest, EmptyString) {
    std::string input = "";
    TList<Lexem*> result;
    EXPECT_NO_THROW({
        result = parse(input);
    });

    EXPECT_EQ(CountLexems(result), 0);
    FreeLexems(&result);
}

TEST(LexemParseTest, SimpleIntExpressionNoThrow) {
    std::string input = "12+34";
    EXPECT_NO_THROW({
        TList<Lexem*> result = parse(input);
        FreeLexems(&result);
    });
}

TEST(LexemParseTest, SimpleIntExpressionTypesIsOk) {
    std::string input = "12+34";
    TList<Lexem*> result = parse(input);
    auto it = result.begin();
    EXPECT_EQ((*it)->type(), INT_CONST);
    it++;
    EXPECT_EQ((*it)->type(), OPERATION);
    it++;
    EXPECT_EQ((*it)->type(), INT_CONST);

    FreeLexems(&result);
}

TEST(LexemParseTest, SimpleFloatExpressionNoThrow) {
    std::string input = "3.14159+34.76";
    EXPECT_NO_THROW({
        TList<Lexem*> result = parse(input);
        FreeLexems(&result);
    });
}

TEST(LexemParseTest, SimpleFloatExpressionTypesIsOk) {
    std::string input = "3.14159+34.76";
    TList<Lexem*> result = parse(input);
    auto it = result.begin();
    EXPECT_EQ((*it)->type(), FLOAT_CONST);
    it++;
    EXPECT_EQ((*it)->type(), OPERATION);
    it++;
    EXPECT_EQ((*it)->type(), FLOAT_CONST);

    FreeLexems(&result);
}

TEST(LexemParseTest, SimpleFunctionNoThrow) {
    std::string input = "sin(45)";
    EXPECT_NO_THROW({
        TList<Lexem*> result = parse(input);
        FreeLexems(&result);
    });
}

TEST(LexemParseTest, SimpleFunctionTypesIsOk) {
    std::string input = "sin(45)";
    TList<Lexem*> result = parse(input);

    EXPECT_EQ(CountLexems(result), 4);
        auto it = result.begin();
    EXPECT_EQ((*it)->type(), FUNCTION);
    it++;
    EXPECT_EQ((*it)->type(), BRACKET);
    it++;
    EXPECT_EQ((*it)->type(), INT_CONST);
    it++;
    EXPECT_EQ((*it)->type(), BRACKET);

    FreeLexems(&result);
}

TEST(LexemParseTest, ComplexExpressionNoThrow) {
    std::string input = "sin(12*12)+(13+488)*5+(x-12^x)/sin(42)";
    EXPECT_NO_THROW({
        TList<Lexem*> result = parse(input);
        FreeLexems(&result);
    });
}


TEST(LexemParseTest, ComplexExpressionCountIsOk) {
    std::string input = "sin(12*12)+(13+488)*5+(x-12^x)/sin(42)";
    TList<Lexem*> result = parse(input);

    EXPECT_EQ(CountLexems(result), 27);
    FreeLexems(&result);
}

TEST(LexemParseTest, InvalidCharacter) {
    std::string input = "12+34@56";
    EXPECT_THROW({
        TList<Lexem*> result = parse(input);
    }, std::runtime_error);
}

TEST(LexemParseTest, DoublePlus) {
    std::string input = "12++34";
    EXPECT_THROW({
        TList<Lexem*> result = parse(input);
    }, std::runtime_error);
}

TEST(LexemParseTest, OperatorBeforeClosingBracket) {
    std::string input = "(12+)";
    EXPECT_THROW({
        TList<Lexem*> result = parse(input);
    }, std::runtime_error);
}
