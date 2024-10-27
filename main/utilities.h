// Copyright 2024 atikdd.t.me

#pragma once

#include <massive.h>
#include <iostream>
#include <Windows.h>
#include <string>


namespace InputSystem {
enum InsertMode { Back, Front, OneValue, SeveralValues };

template <typename T>
T* insert(size_t* n,
size_t* pos,
InputSystem::InsertMode* mode) noexcept {
    T* value = nullptr;
    *mode = Back;
    int user;
    std::cout << "Choose insert mode:\n";
    std::cout << "1 - to the back,\n";
    std::cout << "2 - to the front,\n";
    std::cout << "3 - at given position.\n";
    std::cout << "Your choice: ";
    std::cin >> user;
    if (user == 1) {
        *mode = Back;
    } else if (user == 2) {
        *mode = Front;
    } else if (user == 3) {
        std::cout << "How many values need to insert:\n";
        std::cout << "1 - one value,\n";
        std::cout << "2 - several values.\n";
        std::cout << "Your choice: ";
        std::cin >> user;
        if (user == 1) {
            *mode = OneValue;
        } else if (user == 2) {
            *mode = SeveralValues;
        } else {
            *mode = OneValue;
        }
    } else {
        *mode = Back;
    }
    if (*mode == Back || *mode == Front || *mode == OneValue) {
        *n = 1;
        value = new T[*n];
        std::cout << "Input value for insert: ";
        std::cin >> value[0];
    }
    if (*mode == SeveralValues) {
        std::cout << "Input number of values to insert: ";
        std::cin >> *n;
        value = new T[*n];
        std::cout << "Input values for insert (separated by space): ";
        for (size_t i = 0; i < *n; i++) {
            std::cin >> value[i];
        }
    }
    if (*mode == OneValue || *mode == SeveralValues) {
        std::cout << "Input position for insert: ";
        std::cin >> *pos;
    }
    return value;
}

    // Добавим функции для других действий
template <typename T>
T get_value() noexcept {
    T value;
    std::cout << "Input value: ";
    std::cin >> value;
    return value;
}

size_t get_position() noexcept {
    size_t pos;
    std::cout << "Input position: ";
    std::cin >> pos;
    return pos;
}
}  // namespace InputSystem


namespace OutputSystem {
static void setCursor(int column, int line) {
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord);
}

static void getCursor(int* column, int* line) noexcept {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo
    (GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        if (column != nullptr) {
            *column = csbi.dwCursorPosition.X;
        }
        if (line != nullptr) {
            *line = csbi.dwCursorPosition.Y;
        }
    } else {
        if (column != nullptr) {
            *column = 0;
        }
        if (line != nullptr) {
            *line = 0;
        }
    }
}

static void insert() noexcept {
    std::cout << "Insertion completed successfully." << std::endl;
}

static void show_message(const std::string& message) noexcept {
    std::cout << message << std::endl;
}

template <typename T>
void show(const TMassive<T>& archive) noexcept {
    std::cout << "Archive: { ";
    archive.print(std::cout);
    if (!archive.empty()) {
        // Удаляем последнюю запятую
        int column, line;
        getCursor(&column, &line);
        column -= 2;
        setCursor(column, line);
    }
    std::cout << " }" << std::endl;
}

template <typename T>
static void show_indices(const size_t* indices, size_t count) noexcept {
    std::cout << "Found at indices: ";
    for (size_t i = 0; i < count; ++i) {
        std::cout << indices[i] << " ";
    }
    std::cout << std::endl;
}
}  // namespace OutputSystem
