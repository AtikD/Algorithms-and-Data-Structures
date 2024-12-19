// Copyright 2024 atikdd.t.me


#include <gtest/gtest.h>
#include <cmonom.h>

TEST(CMonomTest, EqualityTrue) {
    CMonom m1(2.0, {2, 1, 0});
    CMonom m2(3.0, {2, 1, 0});
    EXPECT_TRUE(m1 == m2);
}

TEST(CMonomTest, EqualityFalse) {
    CMonom m1(2.0, {2, 1, 0});
    CMonom m2(2.0, {2, 0, 0});
    EXPECT_FALSE(m1 == m2);
}

TEST(CMonomTest, NotEqualTrue) {
    CMonom m1(2.0, {2, 1, 0});
    CMonom m2(2.0, {2, 0, 0});
    EXPECT_TRUE(m1 != m2);
}

TEST(CMonomTest, NotEqualFalse) {
    CMonom m1(2.0, {2, 1, 0});
    CMonom m2(5.0, {2, 1, 0});
    EXPECT_FALSE(m1 != m2);
}

TEST(CMonomTest, AddSimilarMonoms) {
    CMonom m1(2.0, {2, 1, 0});
    CMonom m2(3.0, {2, 1, 0});
    CMonom sum = m1 + m2;
    EXPECT_DOUBLE_EQ(sum.getCoef(), 5.0);
}

TEST(CMonomTest, AddDifferentMonomsThrows) {
    CMonom m1(2.0, {2, 1, 0});
    CMonom m2(3.0, {2, 0, 0});
    EXPECT_THROW(m1 + m2, std::runtime_error);
}

TEST(CMonomTest, SubSimilarMonoms) {
    CMonom m1(5.0, {1, 1, 1});
    CMonom m2(2.0, {1, 1, 1});
    CMonom diff = m1 - m2;
    EXPECT_DOUBLE_EQ(diff.getCoef(), 3.0);
}

TEST(CMonomTest, SubDifferentMonomsThrows) {
    CMonom m1(5.0, {1, 1, 1});
    CMonom m2(1.0, {1, 2, 1});
    EXPECT_THROW(m1 - m2, std::runtime_error);
}

TEST(CMonomTest, MultiplyMonoms) {
    CMonom m1(2.0, {2, 1, 0});
    CMonom m2(3.0, {1, 2, 0});
    CMonom prod = m1 * m2;
    EXPECT_DOUBLE_EQ(prod.getCoef(), 6.0);
}

TEST(CMonomTest, DivideMonoms) {
    CMonom m1(6.0, {3, 2, 0});
    CMonom m2(2.0, {1, 2, 0});
    CMonom quot = m1 / m2;
    EXPECT_DOUBLE_EQ(quot.getCoef(), 3.0);
}

TEST(CMonomTest, DivideWithNegPowerThrows) {
    CMonom m1(6.0, {2, 1, 0});
    CMonom m2(2.0, {3, 1, 0});
    EXPECT_THROW(m1 / m2, std::runtime_error);
}

TEST(CMonomTest, MultiplyByConstant) {
    CMonom m(2.0, {2, 0, 1});
    CMonom res = m * 2.5;
    EXPECT_DOUBLE_EQ(res.getCoef(), 5.0);
}

TEST(CMonomTest, DivideByConstant) {
    CMonom m(10.0, {2, 0, 1});
    CMonom res = m / 5.0;
    EXPECT_DOUBLE_EQ(res.getCoef(), 2.0);
}

TEST(CMonomTest, DivideByZeroConstantThrows) {
    CMonom m(10.0, {2, 0, 1});
    EXPECT_THROW(m / 0.0, std::runtime_error);
}

TEST(CMonomTest, UnaryMinus) {
    CMonom m(3.0, {1, 1, 1});
    CMonom neg = -m;
    EXPECT_DOUBLE_EQ(neg.getCoef(), -3.0);
}

TEST(CMonomTest, ValueAtPoint) {
    CMonom m(2.0, {2, 1, 0});
    double val = m.value({3.0, 2.0, 1.0});  // 2 * 3^2 * 2^1 = 2*9*2=36
    EXPECT_DOUBLE_EQ(val, 36.0);
}

TEST(CMonomTest, ValueWrongDimensionThrows) {
    CMonom m(2.0, {2, 1, 0});
    EXPECT_THROW(m.value({2.0, 1.0}), std::runtime_error);
}

TEST(CMonomTest, OutputStream) {
    CMonom m(3.5, {2, 1, 0});
    std::ostringstream oss;
    oss << m;
    EXPECT_EQ(oss.str(), "3.5*x1^2*x2^1");
}

TEST(CMonomTest, InputStreamCorrect) {
    CMonom m(0, {0, 0, 0});
    std::istringstream iss("3*x1^2*x2^1");
    iss >> m;
    EXPECT_DOUBLE_EQ(m.getCoef(), 3.0);
    std::ostringstream oss;
    oss << m;
    EXPECT_EQ(oss.str(), "3*x1^2*x2^1");
}

TEST(CMonomTest, CopyRegularMonom) {
    CMonom original("3.5*x1^2*x2^1");
    CMonom copy(original);

    EXPECT_DOUBLE_EQ(copy.getCoef(), original.getCoef());
    EXPECT_EQ(copy.getPowers(), original.getPowers());
    EXPECT_TRUE(copy == original);
}

TEST(CMonomTest, ConstantMonom) {
    EXPECT_THROW(CMonom original("5"), std::runtime_error);
}

TEST(CMonomTest, FullMonom) {
    CMonom m("3.5*x1^2*x2^1");
    EXPECT_DOUBLE_EQ(m.getCoef(), 3.5);
    std::vector<int> expectedPowers = {2, 1};
    EXPECT_EQ(m.getPowers(), expectedPowers);

    std::ostringstream oss;
    oss << m;
    EXPECT_EQ(oss.str(), "3.5*x1^2*x2^1");
}

TEST(CMonomTest, DefaultCoefficient) {
    CMonom m("x1^2*x2^1");
    EXPECT_DOUBLE_EQ(m.getCoef(), 1.0);
    std::vector<int> expectedPowers = {2, 1};
    EXPECT_EQ(m.getPowers(), expectedPowers);

    std::ostringstream oss;
    oss << m;
    EXPECT_EQ(oss.str(), "1*x1^2*x2^1");
}

TEST(CMonomTest, DefaultPower) {
    CMonom m("3.5*x1*x2");
    EXPECT_DOUBLE_EQ(m.getCoef(), 3.5);
    std::vector<int> expectedPowers = {1, 1};
    EXPECT_EQ(m.getPowers(), expectedPowers);

    std::ostringstream oss;
    oss << m;
    EXPECT_EQ(oss.str(), "3.5*x1^1*x2^1");
}

TEST(CMonomTest, LocalCoefficients) {
    CMonom m("3*x1^2*2*x2^3");
    EXPECT_DOUBLE_EQ(m.getCoef(), 6.0);
    std::vector<int> expectedPowers = {2, 3};
    EXPECT_EQ(m.getPowers(), expectedPowers);

    std::ostringstream oss;
    oss << m;
    EXPECT_EQ(oss.str(), "6*x1^2*x2^3");
}

TEST(CMonomTest, NegativeCoefficient) {
    CMonom m("-2*x1^3*x3^4");
    EXPECT_DOUBLE_EQ(m.getCoef(), -2.0);
    std::vector<int> expectedPowers = {3, 0, 4};
    EXPECT_EQ(m.getPowers(), expectedPowers);

    std::ostringstream oss;
    oss << m;
    EXPECT_EQ(oss.str(), "-2*x1^3*x3^4");
}

TEST(CMonomTest, ZeroCoefficient) {
    CMonom m("0*x1^3*x2^2");
    EXPECT_DOUBLE_EQ(m.getCoef(), 0.0);
    std::vector<int> expectedPowers = {3, 2};
    EXPECT_EQ(m.getPowers(), expectedPowers);

    std::ostringstream oss;
    oss << m;
    EXPECT_EQ(oss.str(), "0");
}

TEST(CMonomTest, SingleVariable) {
    CMonom m("2*x1^5");
    EXPECT_DOUBLE_EQ(m.getCoef(), 2.0);
    std::vector<int> expectedPowers = {5};
    EXPECT_EQ(m.getPowers(), expectedPowers);

    std::ostringstream oss;
    oss << m;
    EXPECT_EQ(oss.str(), "2*x1^5");
}

// Тест 8: Конструктор с несколькими переменными
TEST(CMonomTest, MultipleVariables) {
    CMonom m("4*x1^2*x2^3*x3^4");
    EXPECT_DOUBLE_EQ(m.getCoef(), 4.0);
    std::vector<int> expectedPowers = {2, 3, 4};
    EXPECT_EQ(m.getPowers(), expectedPowers);

    std::ostringstream oss;
    oss << m;
    EXPECT_EQ(oss.str(), "4*x1^2*x2^3*x3^4");
}

TEST(CMonomTest, NegativePower) {
    EXPECT_THROW(CMonom m("3.5*x1^-2*x2^3"), std::runtime_error);
}

TEST(CMonomTest, InvalidVariableIndex) {
    EXPECT_THROW(CMonom m("3.5*x0^2*x2^3"), std::runtime_error);
}

TEST(CMonomTest, LargeIndicesAndPowers) {
    CMonom m("100000*x1^100*x2^200*x3^300");
    EXPECT_DOUBLE_EQ(m.getCoef(), 100000);
    std::vector<int> expectedPowers = {100, 200, 300};
    EXPECT_EQ(m.getPowers(), expectedPowers);

    std::ostringstream oss;
    oss << m;
    EXPECT_EQ(oss.str(), "100000*x1^100*x2^200*x3^300");
}

TEST(CMonomTest, EmptyString) {
    EXPECT_THROW(CMonom m(""), std::runtime_error);
}

TEST(CMonomTest, ExtraCharacters) {
    EXPECT_THROW(CMonom m("3.5*x1^2*x2^1*"), std::runtime_error);
}

TEST(CMonomTest, SpacesWithinString) {
    CMonom m("  3.5 * x1^2 * x2 ");
    EXPECT_DOUBLE_EQ(m.getCoef(), 3.5);
    std::vector<int> expectedPowers = {2, 1};
    EXPECT_EQ(m.getPowers(), expectedPowers);

    std::ostringstream oss;
    oss << m;
    EXPECT_EQ(oss.str(), "3.5*x1^2*x2^1");
}

TEST(CMonomTest, VariableWithoutCoefficientAndPower) {
    CMonom m("x1*x2");
    EXPECT_DOUBLE_EQ(m.getCoef(), 1.0);
    std::vector<int> expectedPowers = {1, 1};
    EXPECT_EQ(m.getPowers(), expectedPowers);

    std::ostringstream oss;
    oss << m;
    EXPECT_EQ(oss.str(), "1*x1^1*x2^1");
}

TEST(CMonomTest, VariableWithLocalCoefficientWithoutPower) {
    CMonom m("3*x1*2*x2");
    EXPECT_DOUBLE_EQ(m.getCoef(), 6.0);
    std::vector<int> expectedPowers = {1, 1};
    EXPECT_EQ(m.getPowers(), expectedPowers);

    std::ostringstream oss;
    oss << m;
    EXPECT_EQ(oss.str(), "6*x1^1*x2^1");
}

TEST(CMonomTest, VariableWithMultiDigitIndex) {
    CMonom m("3.5*x10^2*x2^3");
    EXPECT_DOUBLE_EQ(m.getCoef(), 3.5);
    std::vector<int> expectedPowers = {0, 3, 0, 0, 0, 0, 0, 0, 0, 2};

    EXPECT_EQ(m.getPowers().size(), 10);
    EXPECT_EQ(m.getPowers()[1], 3);
    EXPECT_EQ(m.getPowers()[9], 2);

    for (size_t i = 0; i < m.getPowers().size(); ++i) {
        if (i != 1 && i != 9)
            EXPECT_EQ(m.getPowers()[i], 0);
    }

    std::ostringstream oss;
    oss << m;
    EXPECT_EQ(oss.str(), "3.5*x2^3*x10^2");
}
