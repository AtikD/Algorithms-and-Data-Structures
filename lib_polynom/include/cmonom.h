// Copyright 2024 atikdd.t.me

#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <cctype>
#include <sstream>
#include <string>
#include <utility>
#include <algorithm>

class CMonom {
 private:
    double coef;
    std::vector<int> powers;

    // Проверка согласованности размеров
    void checkSameSize(const CMonom& other) const {
        if (powers.size() != other.powers.size())
            throw std::runtime_error(
                "Monoms have different number of variables.");
    }

    void delete_spaces(std::string* exp) {
        if (exp == nullptr) return;
        exp->erase(std::remove_if(
            exp->begin(), exp->end(), ::isspace), exp->end());
    }

    void parseFromString(const std::string& s) {
        std::string temp = s;
        delete_spaces(&temp);
        std::istringstream iss(temp);

        bool negative = false;
        if (iss.peek() == '+' || iss.peek() == '-') {
            char sign = iss.get();
            if (sign == '-') negative = true;
        }

        if (std::isdigit(iss.peek()) || iss.peek() == '.') {
            iss >> coef;
        }
        if (negative) coef = -coef;

        int maxIndex = 0;
        std::vector<std::pair<int, int>> parsedPowers;

        while (iss.peek() == '*' || iss.peek() == 'x') {
            if (iss.peek() == '*') {
                iss.get();

                if (std::isdigit(iss.peek()) || iss.peek() == '.') {
                    double localCoef;
                    iss >> localCoef;
                    coef *= localCoef;
                    continue;
                }
            }

            if (iss.peek() != 'x') {
                throw std::runtime_error("Invalid format: Expected 'x' after '*' or at the beginning"); // NOLINT [build/c++11]
            }
            iss.get();

            int index = 0;
            if (!std::isdigit(iss.peek())) {
                throw std::runtime_error("Invalid format: Expected digit after 'x'"); // NOLINT [build/c++11]
            }
            while (std::isdigit(iss.peek())) {
                index = index * 10 + (iss.get() - '0');
            }

            if (index < 1) {
                throw std::runtime_error("Invalid variable index in monom");
            }

            int power = 1;
            if (iss.peek() == '^') {
                iss.get();
                if (!(iss >> power)) {
                    throw std::runtime_error("Invalid power format");
                }
                if (power < 0) {
                    throw std::runtime_error("Negative powers are not allowed");
                }
            }

            maxIndex = std::max(maxIndex, index);
            parsedPowers.emplace_back(index - 1, power);
        }

        powers.resize(maxIndex, 0);
        for (const auto& pair : parsedPowers) {
            int idx = pair.first;
            int p = pair.second;
            powers[idx] = p;
        }

        if (parsedPowers.empty())
            throw std::runtime_error("No variables defined for monom.");
    }


 public:
    CMonom(double c, const std::vector<int>& p) : coef(c), powers(p) {
        if (p.empty())
            throw std::runtime_error("No variables defined for monom.");
        for (int pw : powers)
            if (pw < 0)
                throw std::runtime_error(
                    "Negative power is not allowed in monom.");
    }

    explicit CMonom(const std::string& s) : coef(1.0), powers() {
        parseFromString(s);
    }


    CMonom(const CMonom& other) : coef(other.coef), powers(other.powers) {}

    CMonom& operator=(const CMonom& other) {
        if (this != &other) {
            coef = other.coef;
            powers = other.powers;
        }
        return *this;
    }

    bool operator==(const CMonom& other) const {
        checkSameSize(other);
        return (powers == other.powers);
    }

    bool operator!=(const CMonom& other) const {
        return !(*this == other);
    }

    CMonom operator+(const CMonom& other) const {
        checkSameSize(other);
        if (*this != other)
            throw std::runtime_error(
                "Cannot add monoms with different powers.");
        return CMonom(coef + other.coef, powers);
    }

    CMonom operator-(const CMonom& other) const {
        checkSameSize(other);
        if (*this != other)
            throw std::runtime_error(
                "Cannot subtract monoms with different powers.");
        return CMonom(coef - other.coef, powers);
    }

    CMonom operator*(const CMonom& other) const {
        checkSameSize(other);
        std::vector<int> newPowers(powers.size());
        for (size_t i = 0; i < powers.size(); i++)
            newPowers[i] = powers[i] + other.powers[i];
        return CMonom(coef * other.coef, newPowers);
    }

    CMonom operator/(const CMonom& other) const {
        checkSameSize(other);
        if (other.coef == 0.0) {
            throw std::runtime_error("Division by zero monom coefficient.");
        }
        std::vector<int> newPowers(powers.size());
        for (size_t i = 0; i < powers.size(); i++) {
            int diff = powers[i] - other.powers[i];
            if (diff < 0)
                throw std::runtime_error("Division results in negative power.");
            newPowers[i] = diff;
        }
        return CMonom(coef / other.coef, newPowers);
    }

    CMonom operator*(double c) const {
        return CMonom(coef * c, powers);
    }

    CMonom operator/(double c) const {
        if (c == 0.0) {
            throw std::runtime_error("Division by zero constant.");
        }
        return CMonom(coef / c, powers);
    }

    // Унарный минус
    CMonom operator-() const {
        return CMonom(-coef, powers);
    }

    CMonom& operator+=(const CMonom& other) {
        *this = *this + other;
        return *this;
    }

    CMonom& operator-=(const CMonom& other) {
        *this = *this - other;
        return *this;
    }

    CMonom& operator*=(const CMonom& other) {
        *this = *this * other;
        return *this;
    }

    CMonom& operator/=(const CMonom& other) {
        *this = *this / other;
        return *this;
    }

    CMonom& operator*=(double c) {
        *this = *this * c;
        return *this;
    }

    CMonom& operator/=(double c) {
        *this = *this / c;
        return *this;
    }

    // Вычисление значения в точке
    double value(const std::vector<double>& x) const {
        if (x.size() != powers.size())
            throw std::runtime_error(
                "Point dimension does not match monom dimension.");
        double val = coef;
        for (size_t i = 0; i < powers.size(); i++) {
            if (powers[i] > 0)
                val *= std::pow(x[i], powers[i]);
        }
        return val;
    }

    double getCoef() const { return coef; }
    const std::vector<int>& getPowers() const { return powers; }

    // Вывод монома
    friend std::ostream& operator<<(std::ostream& os, const CMonom& m) {
        if (m.coef == 0.0) {
            os << "0";
            return os;
        }
        os << m.coef;
        for (size_t i = 0; i < m.powers.size(); i++) {
            int p = m.powers[i];
            if (p > 0) {
                os << "*x" << (i+1) << "^" << p;
            }
        }
        return os;
    }

    // Ввод монома из потока
    friend std::istream& operator>>(std::istream& is, CMonom& m) {
        std::string s;
        is >> s;

        if (s.empty()) {
            is.setstate(std::ios::failbit);
            return is;
        }

        try {
            m.parseFromString(s);
        }
        catch (const std::runtime_error& e) {
            is.setstate(std::ios::failbit);
        }

        return is;
    }
};
