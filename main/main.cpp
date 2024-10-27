// Copyright 2024 atikdd.t.me

#include <massive.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <list>

#ifdef EXAMPLE
#include <easy_example.h>

void EasyExample() {
    int a, b;
    float result;

    a = 1;
    b = 4;

    try {
        result = division(a, b);
        std::cout << a << " / " << b << " = "
                  << std::setprecision(2) << result << std::endl;
    } catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
    }

    a = 1;
    b = 0;

    try {
        result = division(a, b);
        std::cout << a << " / " << b << " = "
                  << std::setprecision(2) << result << std::endl;
    } catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
    }
}
#endif
#ifdef MASSIVE

#include "../main/utilities.h"

enum Actions { EXIT, INSERT, FIND, REMOVE, CLEAN };

void MassiveExample() {
    TMassive<int> massive;
    size_t n, pos;
    int* values = nullptr;
    int user;

    bool exit = false;
    bool success;
    InputSystem::InsertMode mode;

    while (!exit) {
        system("cls");
        OutputSystem::show(massive);
        std::cout << "Menu:\n 1. Insert,\n 2. Find,"<<
                        "\n 3. Remove,\n 4. Clean,\n 0. Exit.\nYour choice: ";
        std::cin >> user;
        switch (user) {
        case Actions::EXIT:
            exit = true;
            break;
        case Actions::INSERT:
            if (values != nullptr) {
                delete[] values;
                values = nullptr;
            }
            values = InputSystem::insert<int>(&n, &pos, &mode);
            success = false;
            try {
                if (mode == InputSystem::InsertMode::Back) {
                    massive.push_back(values[0]);
                    success = true;
                } else if (mode == InputSystem::InsertMode::Front) {
                    massive.push_front(values[0]);
                    success = true;
                } else if (mode == InputSystem::InsertMode::OneValue) {
                    massive.insert(values[0], pos);
                    success = true;
                } else if (mode == InputSystem::InsertMode::SeveralValues) {
                    massive.insert(values, n, pos);
                    success = true;
                }
            }
            catch (std::exception& err) {
                std::cerr << err.what() << std::endl;
                success = false;
            }
            if (success) {
                OutputSystem::insert();
            }
            if (values != nullptr) {
                delete[] values;
                values = nullptr;
            }
            system("pause");
            break;
        case Actions::FIND:
        {
            int value = InputSystem::get_value<int>();
            try {
                size_t index = massive.find_first(value);
                std::cout << "First occurrence at index: " <<
                            index << std::endl;
                size_t* indices = massive.find_all(value);
                size_t count = indices[0] + 1;
                if (indices != nullptr) {
                    std::cout << "All occurrences at indices: ";
                    for (size_t i = 1; i < count; ++i) {
                        std::cout << indices[i] << " ";
                    }
                    std::cout << std::endl;
                    delete[] indices;
                } else {
                    std::cout << "Value not found." << std::endl;
                }
            }
            catch (std::exception& err) {
                std::cerr << err.what() << std::endl;
            }
            system("pause");
            break;
        }
        case Actions::REMOVE:
        {
            std::cout << "Choose remove mode:\n";
            std::cout << "1 - Remove by index,\n";
            std::cout << "2 - Remove first occurrence,\n";
            std::cout << "3 - Remove last occurrence,\n";
            std::cout << "4 - Remove all occurrences.\n";
            std::cout << "Your choice: ";
            std::cin >> user;
            try {
                if (user == 1) {
                    size_t pos = InputSystem::get_position();
                    massive.remove_by_index(pos);
                } else if (user == 2) {
                    int value = InputSystem::get_value<int>();
                    massive.remove_first(value);
                } else if (user == 3) {
                    int value = InputSystem::get_value<int>();
                    massive.remove_last(value);
                } else if (user == 4) {
                    int value = InputSystem::get_value<int>();
                    massive.remove_all(value);
                }
                OutputSystem::show_message("Removal completed successfully.");
            }
            catch (std::exception& err) {
                std::cerr << err.what() << std::endl;
            }
            system("pause");
            break;
        }
        case Actions::CLEAN:
            massive.clear();
            OutputSystem::show_message("massive cleaned.");
            system("pause");
            break;
        default:
            std::cout << "Invalid choice." << std::endl;
            system("pause");
            break;
        }
    }
}
#endif
#ifdef LIST

#include <list.h>

void ListExample() {
    TList<int> list;

    list.push_back(10);
    list.push_front(5);
    list.insert_at(1, 7);

    std::cout << "List after insertions: " << list << std::endl;

    TNode<int>* node = list.find(7);
    if (node != nullptr) {
        std::cout << "Found node with value: " << node->getValue() << std::endl;
    }

    list.replace(node, 8);
    std::cout << "List after replacing value: " << list << std::endl;

    list.remove(node);
    std::cout << "List after removing node: " << list << std::endl;

    list.remove_at(1);
    std::cout << "List after removing at position 1: " << list << std::endl;

    if (list.isEmpty()) {
        std::cout << "List is empty." << std::endl;
    } else {
        std::cout << "List is not empty." << std::endl;
    }

    list.pop_front();
    if (list.isEmpty()) {
        std::cout << "List is empty after pop_front." << std::endl;
    }
}

#endif

int main() {
    #ifdef EXAMPLE
    EasyExample();
    #endif

    #ifdef MASSIVE
    MassiveExample();
    #endif

    #ifdef LIST
    ListExample();
    #endif

    return 0;
}

