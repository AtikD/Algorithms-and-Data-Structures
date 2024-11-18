// Copyright 2024 atikdd.t.me

#pragma once

#include <vector.h>
#include <stdexcept>

template <typename T>
class TMatrix {
 protected:
    TVector<TVector<T>> _data;

 public:
    TMatrix();
    TMatrix(size_t rows, size_t cols);
    TMatrix(const TMatrix<T>& other);

    ~TMatrix();

    TMatrix<T>& operator=(const TMatrix<T>& other);

    TVector<T>& operator[](size_t index);
    const TVector<T>& operator[](size_t index) const;

    TMatrix<T> operator+(const TMatrix<T>& other) const;
    TMatrix<T> operator-(const TMatrix<T>& other) const;
    TMatrix<T> operator*(const TMatrix<T>& other) const;

    TMatrix<T>& operator+=(const TMatrix<T>& other);
    TMatrix<T>& operator-=(const TMatrix<T>& other);

    TMatrix<T> operator*(const T& scalar) const;
    TMatrix<T>& operator*=(const T& scalar);

    bool operator==(const TMatrix<T>& other) const;
    bool operator!=(const TMatrix<T>& other) const;

    size_t rows() const;
    size_t cols() const;
    void resize(size_t new_rows, size_t new_cols);
    void clear();

    void print(std::ostream& out = std::cout) const;

    TMatrix<T> transpose() const;
    T determinant() const;
    TMatrix<T> inverse() const;

 private:
    T determinant_recursive(const TMatrix<T>& mat) const;
    TMatrix<T> get_submatrix(size_t exclude_row,
                             size_t exclude_col) const;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& out,
                                const TMatrix<U>& matrix);
};

template <typename T>
TMatrix<T>::TMatrix() : _data() {}

template <typename T>
TMatrix<T>::TMatrix(size_t rows, size_t cols) : _data(rows) {
    for (size_t i = 0; i < rows; ++i) {
        _data[i] = TVector<T>(cols);
    }
}

template <typename T>
TMatrix<T>::TMatrix(const TMatrix<T>& other) : _data(other._data) {}

template <typename T>
TMatrix<T>::~TMatrix() {}

template <typename T>
TMatrix<T>& TMatrix<T>::operator=(const TMatrix<T>& other) {
    if (this != &other) {
        _data = other._data;
    }
    return *this;
}

template <typename T>
TVector<T>& TMatrix<T>::operator[](size_t index) {
    if (index >= rows()) {
        throw std::out_of_range("Индекс строки вне диапазона");
    }
    return _data[index];
}

template <typename T>
const TVector<T>& TMatrix<T>::operator[](size_t index) const {
    if (index >= rows()) {
        throw std::out_of_range("Индекс строки вне диапазона");
    }
    return _data[index];
}

template <typename T>
size_t TMatrix<T>::rows() const {
    return _data.size();
}

template <typename T>
size_t TMatrix<T>::cols() const {
    return rows() > 0 ? _data[0].size() : 0;
}

template <typename T>
void TMatrix<T>::resize(size_t new_rows, size_t new_cols) {
    _data.resize(new_rows);
    for (size_t i = 0; i < new_rows; ++i) {
        _data[i].resize(new_cols);
    }
}

template <typename T>
void TMatrix<T>::clear() {
    _data.clear();
}

template <typename T>
void TMatrix<T>::print(std::ostream& out) const {
    for (size_t i = 0; i < rows(); ++i) {
        _data[i].print(out);
        out << std::endl;
    }
}

template <typename T>
TMatrix<T> TMatrix<T>::operator+(const TMatrix<T>& other) const {
    if (rows() != other.rows() || cols() != other.cols()) {
        throw std::logic_error("Размеры матриц не совпадают для сложения");
    }
    TMatrix<T> result(rows(), cols());
    for (size_t i = 0; i < rows(); ++i) {
        result[i] = _data[i] + other._data[i];
    }
    return result;
}

template <typename T>
TMatrix<T> TMatrix<T>::operator-(const TMatrix<T>& other) const {
    if (rows() != other.rows() || cols() != other.cols()) {
        throw std::logic_error("Размеры матриц не совпадают для вычитания");
    }
    TMatrix<T> result(rows(), cols());
    for (size_t i = 0; i < rows(); ++i) {
        result[i] = _data[i] - other._data[i];
    }
    return result;
}

template <typename T>
TMatrix<T> TMatrix<T>::operator*(const TMatrix<T>& other) const {
    if (cols() != other.rows()) {
        throw std::logic_error("Матрицы несовместимы для умножения");
    }
    TMatrix<T> result(rows(), other.cols());
    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < other.cols(); ++j) {
            T sum = T();
            for (size_t k = 0; k < cols(); ++k) {
                sum += _data[i][k] * other._data[k][j];
            }
            result[i][j] = sum;
        }
    }
    return result;
}

template <typename T>
TMatrix<T>& TMatrix<T>::operator+=(const TMatrix<T>& other) {
    *this = *this + other;
    return *this;
}

template <typename T>
TMatrix<T>& TMatrix<T>::operator-=(const TMatrix<T>& other) {
    *this = *this - other;
    return *this;
}

template <typename T>
TMatrix<T> TMatrix<T>::operator*(const T& scalar) const {
    TMatrix<T> result(*this);
    for (size_t i = 0; i < rows(); ++i) {
        result[i] *= scalar;
    }
    return result;
}

template <typename T>
TMatrix<T>& TMatrix<T>::operator*=(const T& scalar) {
    for (size_t i = 0; i < rows(); ++i) {
        _data[i] *= scalar;
    }
    return *this;
}

template <typename T>
bool TMatrix<T>::operator==(const TMatrix<T>& other) const {
    if (rows() != other.rows() || cols() != other.cols()) {
        return false;
    }
    for (size_t i = 0; i < rows(); ++i) {
        if (_data[i] != other._data[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool TMatrix<T>::operator!=(const TMatrix<T>& other) const {
    return !(*this == other);
}


template <typename T>
TMatrix<T> TMatrix<T>::transpose() const {
    size_t new_rows = cols();
    size_t new_cols = rows();
    TMatrix<T> result(new_rows, new_cols);

    for (size_t i = 0; i < new_rows; ++i) {
        for (size_t j = 0; j < new_cols; ++j) {
            result[i][j] = _data[j][i];
        }
    }
    return result;
}

template <typename T>
T TMatrix<T>::determinant() const {
    if (rows() != cols()) {
        throw std::logic_error("Матрица не квадратная");
    }
    if (rows() == 0) {
        throw std::logic_error("Матрица пустая");
    }
    return determinant_recursive(*this);
}

template <typename T>
T TMatrix<T>::determinant_recursive(const TMatrix<T>& mat) const {
    size_t n = mat.rows();
    if (n == 1) {
        return mat[0][0];
    }
    if (n == 2) {
        return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    }

    T det = T();
    for (size_t p = 0; p < n; ++p) {
        TMatrix<T> submat = mat.get_submatrix(0, p);
        T sign = (p % 2 == 0) ? 1 : -1;
        det += sign * mat[0][p] * determinant_recursive(submat);
    }
    return det;
}

template <typename T>
TMatrix<T> TMatrix<T>::get_submatrix(size_t exclude_row,
                                     size_t exclude_col) const {
    size_t n = rows();
    TMatrix<T> submat(n - 1, n - 1);
    size_t row = 0;
    for (size_t i = 0; i < n; ++i) {
        if (i == exclude_row) continue;
        size_t col = 0;
        for (size_t j = 0; j < n; ++j) {
            if (j == exclude_col) continue;
            submat[row][col] = _data[i][j];
            ++col;
        }
        ++row;
    }
    return submat;
}

template <typename T>
TMatrix<T> TMatrix<T>::inverse() const {
    T det = determinant();
    if (det == T()) {
        throw std::logic_error("Матрица вырожденная, обратной матрицы нет");
    }
    size_t n = rows();
    TMatrix<T> adjoint(n, n);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            TMatrix<T> submat = get_submatrix(i, j);
            T sign = ((i + j) % 2 == 0) ? 1 : -1;
            adjoint[j][i] = sign * submat.determinant();
        }
    }
    return adjoint * (1 / det);
}

template <typename U>
std::ostream& operator<<(std::ostream& out, const TMatrix<U>& matrix) {
    for (size_t i = 0; i < matrix.rows(); ++i) {
        out << "{ ";
        for (size_t j = 0; j < matrix.cols(); ++j) {
            out << matrix[i][j];
            if (j < matrix.cols() - 1) {
                out << ", ";
            }
        }
        out << " }";
        if (i < matrix.rows() - 1) {
            out << std::endl;
        }
    }
    return out;
}
