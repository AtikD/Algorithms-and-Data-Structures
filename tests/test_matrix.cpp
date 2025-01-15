// Copyright 2024 atikdd.t.me


#include <gtest/gtest.h>
#include <matrix.h>

TEST(TMatrixTest, DefaultConstructor) {
    TMatrix<int> mat;
    EXPECT_EQ(mat.rows(), 0);
    EXPECT_EQ(mat.cols(), 0);
}

TEST(TMatrixTest, ParameterizedConstructor_SetsCorrectSize) {
    TMatrix<int> mat(3, 4);
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 4);
}

TEST(TMatrixTest, ParameterizedConstructor_InitializesElementsToZero) {
    TMatrix<int> mat(2, 2);
    EXPECT_EQ(mat[0][0], 0);
    EXPECT_EQ(mat[0][1], 0);
    EXPECT_EQ(mat[1][0], 0);
    EXPECT_EQ(mat[1][1], 0);
}

TEST(TMatrixTest, CopyConstructor) {
    TMatrix<int> mat(3, 4);
    TMatrix<int> mat2(mat);
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 4);
}

// Тесты оператора присваивания
TEST(TMatrixTest, AssignmentOperator) {
    TMatrix<int> mat1(2, 2);
    mat1[0][0] = 1;
    mat1[0][1] = 2;
    mat1[1][0] = 3;
    mat1[1][1] = 4;

    TMatrix<int> mat2;
    mat2 = mat1;

    EXPECT_EQ(mat2[0][0], 1);
    EXPECT_EQ(mat2[0][1], 2);
    EXPECT_EQ(mat2[1][0], 3);
    EXPECT_EQ(mat2[1][1], 4);
}

// Тесты оператора сложения
TEST(TMatrixTest, AdditionOperator_ReturnsCorrectResult) {
    TMatrix<int> mat1(2, 2);
    TMatrix<int> mat2(2, 2);

    mat1[0][0] = 1;
    mat1[0][1] = 2;
    mat1[1][0] = 3;
    mat1[1][1] = 4;

    mat2[0][0] = 5;
    mat2[0][1] = 6;
    mat2[1][0] = 7;
    mat2[1][1] = 8;

    TMatrix<int> result = mat1 + mat2;

    EXPECT_EQ(result[0][0], 6);
    EXPECT_EQ(result[0][1], 8);
    EXPECT_EQ(result[1][0], 10);
    EXPECT_EQ(result[1][1], 12);
}

TEST(TMatrixTest, AdditionOperator_ThrowsOnSizeMismatch) {
    TMatrix<int> mat1(2, 2);
    TMatrix<int> mat2(3, 3);
    EXPECT_THROW(mat1 + mat2, std::logic_error);
}

// Тесты оператора вычитания
TEST(TMatrixTest, SubtractionOperator) {
    TMatrix<int> mat1(2, 2);
    TMatrix<int> mat2(2, 2);

    mat1[0][0] = 10;
    mat1[0][1] = 20;
    mat1[1][0] = 30;
    mat1[1][1] = 40;

    mat2[0][0] = 1;
    mat2[0][1] = 2;
    mat2[1][0] = 3;
    mat2[1][1] = 4;

    TMatrix<int> result = mat1 - mat2;

    EXPECT_EQ(result[0][0], 9);
    EXPECT_EQ(result[0][1], 18);
    EXPECT_EQ(result[1][0], 27);
    EXPECT_EQ(result[1][1], 36);
}

TEST(TMatrixTest, SubtractionOperator_ThrowsOnSizeMismatch) {
    TMatrix<int> mat1(2, 2);
    TMatrix<int> mat2(3, 3);
    EXPECT_THROW(mat1 - mat2, std::logic_error);
}

// Тесты оператора умножения матриц
TEST(TMatrixTest, MultiplicationOperator) {
    TMatrix<int> mat1(2, 3);
    TMatrix<int> mat2(3, 2);

    mat1[0][0] = 1;
    mat1[0][1] = 2;
    mat1[0][2] = 3;
    mat1[1][0] = 4;
    mat1[1][1] = 5;
    mat1[1][2] = 6;

    mat2[0][0] = 7;
    mat2[0][1] = 8;
    mat2[1][0] = 9;
    mat2[1][1] = 10;
    mat2[2][0] = 11;
    mat2[2][1] = 12;

    TMatrix<int> result = mat1 * mat2;

    EXPECT_EQ(result[0][0], 58);
    EXPECT_EQ(result[0][1], 64);
    EXPECT_EQ(result[1][0], 139);
    EXPECT_EQ(result[1][1], 154);
}

TEST(TMatrixTest, MultiplicationOperator_ThrowsOnIncompatibleMatrices) {
    TMatrix<int> mat1(2, 3);
    TMatrix<int> mat2(4, 2);
    EXPECT_THROW(mat1 * mat2, std::logic_error);
}

TEST(TMatrixTest, Determinant) {
    TMatrix<double> mat(2, 2);
    mat[0][0] = 4;
    mat[0][1] = 7;
    mat[1][0] = 2;
    mat[1][1] = 6;

    double det = mat.determinant();
    EXPECT_NEAR(det, 10.0, 1e-9);
}

TEST(TMatrixTest, Determinant_ThrowsOnNonSquareMatrix) {
    TMatrix<double> mat(2, 3);
    EXPECT_THROW(mat.determinant(), std::logic_error);
}

TEST(TMatrixTest, Inverse) {
    TMatrix<double> mat(2, 2);
    mat[0][0] = 4;
    mat[0][1] = 7;
    mat[1][0] = 2;
    mat[1][1] = 6;

    TMatrix<double> inv = mat.inverse();

    EXPECT_NEAR(inv[0][0], 0.6, 1e-9);
    EXPECT_NEAR(inv[0][1], -0.7, 1e-9);
    EXPECT_NEAR(inv[1][0], -0.2, 1e-9);
    EXPECT_NEAR(inv[1][1], 0.4, 1e-9);
}

TEST(TMatrixTest, Inverse_ThrowsOnSingularMatrix) {
    TMatrix<double> mat(2, 2);
    mat[0][0] = 1;
    mat[0][1] = 2;
    mat[1][0] = 2;
    mat[1][1] = 4;
    EXPECT_THROW(mat.inverse(), std::logic_error);
}

TEST(TMatrixTest, Transpose) {
    TMatrix<int> mat(2, 3);
    mat[0][0] = 1;
    mat[0][1] = 2;
    mat[0][2] = 3;
    mat[1][0] = 4;
    mat[1][1] = 5;
    mat[1][2] = 6;

    TMatrix<int> transposed = mat.transpose();

    EXPECT_EQ(transposed.rows(), 3);
    EXPECT_EQ(transposed.cols(), 2);

    EXPECT_EQ(transposed[0][0], 1);
    EXPECT_EQ(transposed[0][1], 4);
    EXPECT_EQ(transposed[1][0], 2);
    EXPECT_EQ(transposed[1][1], 5);
    EXPECT_EQ(transposed[2][0], 3);
    EXPECT_EQ(transposed[2][1], 6);
}

TEST(TMatrixTest, Transpose_EmptyMatrixReturnsEmptyMatrix) {
    TMatrix<int> mat;
    TMatrix<int> transposed = mat.transpose();

    EXPECT_EQ(transposed.rows(), 0);
    EXPECT_EQ(transposed.cols(), 0);
}

TEST(TMatrixTest, AccessOperator_ThrowsOnInvalidColumnIndex) {
    TMatrix<int> mat(3, 3);

    EXPECT_THROW(mat[0][3], std::out_of_range);
    EXPECT_THROW(mat[0][-1], std::out_of_range);
}
