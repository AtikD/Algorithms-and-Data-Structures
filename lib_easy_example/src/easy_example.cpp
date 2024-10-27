// Copyright 2024 atikdd.t.me

#include "../include/easy_example.h"
#include <stdexcept>

float division(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("Input Error: can't divide by zero!");
    }
    return static_cast<float>(a) / b;
}
