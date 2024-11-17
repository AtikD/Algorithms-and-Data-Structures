// Copyright 2024 atikdd.t.me

#include <gtest/gtest.h>
#include <parser.h>
#include <cycle_detector.h>

TEST(ExpressionParserTest, ValidExpressions) {
    ExpressionParser parser;

    EXPECT_TRUE(parser.isValidExpression(new std::string(
                        "((x+y*5)*[x/6-y])+{((8+19)+|14x+56|)*[18y-65]}")));
    EXPECT_TRUE(parser.isValidExpression(new std::string("|a+b|*|3-x|")));
    EXPECT_TRUE(parser.isValidExpression(new std::string(
                                                "((x1 + y2) * (z3 - w4))")));
    EXPECT_TRUE(parser.isValidExpression(new std::string(
                                        "5 + (6 - (7 + [8 * {9 / 10}]))")));
    EXPECT_TRUE(parser.isValidExpression(new std::string("|x|")));
    EXPECT_TRUE(parser.isValidExpression(new std::string("||x + y||")));
}

TEST(ExpressionParserTest, InvalidExpressions) {
    ExpressionParser parser;

    EXPECT_FALSE(parser.isValidExpression(new std::string("((()())")));
    EXPECT_FALSE(parser.isValidExpression(new std::string("()([]{])")));
    EXPECT_FALSE(parser.isValidExpression(new std::string("(x + y]*z")));
    EXPECT_FALSE(parser.isValidExpression(new std::string("([x + y)]")));
    EXPECT_FALSE(parser.isValidExpression(new std::string("({x + y})]")));
    EXPECT_FALSE(parser.isValidExpression(new std::string("|x + y")));
    EXPECT_FALSE(parser.isValidExpression(new std::string("x + y|")));
    EXPECT_FALSE(parser.isValidExpression(new std::string("||x + y|")));
}

TEST(ExpressionParserTest, InvalidCharacters) {
    ExpressionParser parser;

    EXPECT_FALSE(parser.isValidExpression(new std::string("x + y @ z")));
    EXPECT_FALSE(parser.isValidExpression(new std::string("x % y")));
    EXPECT_FALSE(parser.isValidExpression(new std::string("x + y # z")));
    EXPECT_FALSE(parser.isValidExpression(new std::string("x + y ~ z")));
}

TEST(ExpressionParserTest, EmptyExpression) {
    ExpressionParser parser;

    EXPECT_TRUE(parser.isValidExpression(new std::string("")));
}

TEST(ExpressionParserTest, OnlyWhitespaces) {
    ExpressionParser parser;

    EXPECT_TRUE(parser.isValidExpression(new std::string("   ")));
}

TEST(ExpressionParserTest, ComplexNestedExpressions) {
    ExpressionParser parser;

    EXPECT_TRUE(parser.isValidExpression(new std::string("({[()]})")));
    EXPECT_FALSE(parser.isValidExpression(new std::string("({[([)])}))")));
    EXPECT_TRUE(parser.isValidExpression(new std::string("((((x))))")));
    EXPECT_FALSE(parser.isValidExpression(new std::string("((((x))")));
}

TEST(CycleDetectorTest, NotDetectsCycleFloyd) {
    TList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_FALSE(hasCycleFloyd(&list));
}

TEST(CycleDetectorTest, DetectsCycleFloyd) {
    TList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    // Создаем цикл: последний элемент ссылается на первый
    TNode<int>* tail = list.getTail();
    TNode<int>* head = list.getHead();
    tail->setNext(head);

    EXPECT_TRUE(hasCycleFloyd(&list));

    tail->setNext(nullptr);
}

TEST(CycleDetectorTest, NotDetectsCycleReverse) {
    TList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_FALSE(hasCycleReverse(&list));
}

TEST(CycleDetectorTest, DetectsCycleReverse) {
    TList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    // Создаем цикл: последний элемент ссылается на первый
    TNode<int>* tail = list.getTail();
    TNode<int>* head = list.getHead();
    tail->setNext(head);

    EXPECT_TRUE(hasCycleReverse(&list));

    tail->setNext(nullptr);
}
