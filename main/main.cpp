// Copyright 2024 atikdd.t.me

#include <easy_example.h>
#include <queue.h>
#include <massive.h>
#include <cycle_detector.h>
#include <vector.h>
#include <list.h>
#include <stack.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <chrono> // NOLINT [build/c++11]
#include <cstdint>

#ifdef EXAMPLE
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

#ifdef VECTOR
void VectorExample() {
    TVector<int> vec1(3, 0);
    vec1[0] = 1;
    vec1[1] = 2;
    vec1[2] = 3;

    TVector<int> vec2(3, 0);
    vec2[0] = 4;
    vec2[1] = 5;
    vec2[2] = 6;

    TVector<int> vecSum = vec1 + vec2;
    vecSum.print();

    int scalarProduct = vec1 * vec2;
    std::cout << "Scalar product: " << scalarProduct << std::endl;

    TVector<int> vecScaled = vec1 * 2;
    vecScaled.print();

    if (vec1 == vec1) {
        std::cout << "Vectors are equal." << std::endl;
    }

    TVector<int> vec3 = vec1;
    vec3.print();

    vec3.resize(5);
    vec3.print();
}

#endif

#ifdef STACK
void StackExample() {
    Stack<int> s;

    s.push(10);
    s.push(20);
    s.push(30);

    std::cout << "Размер стека: " << s.size() << std::endl;

    std::cout << "Верхний элемент: " << s.top() << std::endl;

    s.pop();
    std::cout << "Верхний элемент после pop(): " << s.top() << std::endl;

    s.clear();
    std::cout << "Стек пуст? " << (s.empty() ? "Да" : "Нет") << std::endl;
}
#endif

#ifdef QUEUE
void QueueExample() {
    // Создаем очередь целых чисел с емкостью 5
    TQueue<int> intQueue(5);

    // Добавляем элементы в очередь
    std::cout << "Adding elements to intQueue:" << std::endl;
    for (int i = 1; i <= 5; ++i) {
        intQueue.push(i * 10);
        std::cout << "Added element: " << i * 10 << std::endl;
    }

    // Попытка добавить элемент в полную очередь (выбросит исключение)
    try {
        intQueue.push(60);
    } catch (const std::overflow_error& e) {
        std::cout << "Error while adding: " << e.what() << std::endl;
    }

    // Выводим состояние очереди
    std::cout << "State of intQueue after adding elements:" << std::endl;
    intQueue.print();

    // Удаляем два элемента из очереди
    std::cout << "Removing two elements from intQueue:" << std::endl;
    std::cout << "Removed element: " << intQueue.pop() << std::endl;
    std::cout << "Removed element: " << intQueue.pop() << std::endl;

    // Выводим состояние очереди
    std::cout << "State of intQueue after removing elements:" << std::endl;
    intQueue.print();

    // Проверяем, пуста ли очередь
    if (intQueue.is_empty()) {
        std::cout << "intQueue is empty." << std::endl;
    } else {
        std::cout << "intQueue is not empty." << std::endl;
    }

    // Проверяем, полна ли очередь
    if (intQueue.is_full()) {
        std::cout << "intQueue is full." << std::endl;
    } else {
        std::cout << "intQueue is not full." << std::endl;
    }

    // Добавляем еще элементы в очередь
    std::cout << "Adding elements to intQueue after removal:" << std::endl;
    intQueue.push(60);
    std::cout << "Added element: 60" << std::endl;
    intQueue.push(70);
    std::cout << "Added element: 70" << std::endl;

    // Выводим текущее состояние очереди
    std::cout << "Current state of intQueue:" << std::endl;
    intQueue.print();

    // Создаем массив TMassive<double> и заполняем его
    TMassive<double> doubleMassive;
    doubleMassive.push_back(1.1);
    doubleMassive.push_back(2.2);
    doubleMassive.push_back(3.3);

    // Создаем очередь на основе TMassive<double>
    TQueue<double> doubleQueue(doubleMassive);

    // Выводим состояние очереди doubleQueue
    std::cout << "State of doubleQueue created from TMassive<double>:"
              << std::endl;
    doubleQueue.print();

    // Удаляем элементы из doubleQueue
    std::cout << "Removing elements from doubleQueue:" << std::endl;
    while (!doubleQueue.is_empty()) {
        std::cout << "Removed element: " << doubleQueue.pop() << std::endl;
    }

    // Проверяем состояние очереди
    if (doubleQueue.is_empty()) {
        std::cout << "doubleQueue is now empty." << std::endl;
    }

    // Использование очереди строк
    TQueue<std::string> stringQueue;
    stringQueue.push("First");
    stringQueue.push("Second");
    stringQueue.push("Third");

    // Выводим состояние очереди stringQueue
    std::cout << "State of stringQueue:" << std::endl;
    stringQueue.print();

    // Удаляем элемент из очереди строк
    std::cout << "Removed element from stringQueue: " << stringQueue.pop()
              << std::endl;

    // Выводим текущее состояние очереди строк
    std::cout << "Current state of stringQueue:" << std::endl;
    stringQueue.print();

    // Очистка очереди строк
    stringQueue.clear();
    std::cout << "stringQueue after clearing:" << std::endl;
    if (stringQueue.is_empty()) {
        std::cout << "stringQueue is empty." << std::endl;
    }

    // Демонстрация циклического поведения очереди
    TQueue<int> cycleQueue(4);
    cycleQueue.push(100);
    cycleQueue.push(200);
    cycleQueue.push(300);
    cycleQueue.push(400);

    // Очередь полна, индексы top и back
    std::cout << "Indices top and back in full cycleQueue:" << std::endl;
    std::cout << "top = " << cycleQueue.get_top() << "; back = "
              << cycleQueue.get_back() << std::endl;

    // Удаляем два элемента
    std::cout << "Removing two elements from cycleQueue:" << std::endl;
    std::cout << "Removed element: " << cycleQueue.pop() << std::endl;
    std::cout << "Removed element: " << cycleQueue.pop() << std::endl;

    // Добавляем еще два элемента, индексы должны обернуться
    cycleQueue.push(500);
    std::cout << "Added element: 500" << std::endl;
    cycleQueue.push(600);
    std::cout << "Added element: 600" << std::endl;

    // Выводим состояние очереди
    std::cout << "State of cycleQueue after circular addition:" << std::endl;
    cycleQueue.print();

    // Индексы top и back после циклического добавления
    std::cout << "Indices top and back after circular addition:" << std::endl;
    std::cout << "top = " << cycleQueue.get_top() << "; back = "
              << cycleQueue.get_back() << std::endl;

    // Удаляем все элементы из cycleQueue
    std::cout << "Removing all remaining elements from cycleQueue:"
              << std::endl;
    while (!cycleQueue.is_empty()) {
        std::cout << "Removed element: " << cycleQueue.pop() << std::endl;
    }

    // Проверяем состояние очереди
    if (cycleQueue.is_empty()) {
        std::cout << "cycleQueue is now empty." << std::endl;
    }
}
#endif

#ifdef ALGORITHMS
template <typename T>
TList<T>* generateList(size_t size, bool createCycle) {
    TList<T>* list = new TList<T>();
    for (size_t i = 0; i < size; ++i) {
        list->push_back(static_cast<T>(i));
    }

    if (createCycle && size > 0) {
        TNode<T>* tail = list->getTail();
        TNode<T>* head = list->getHead();
        tail->setNext(head);
    }
    return list;
}


template <typename Func, typename T>
int64_t measureAlgorithmTime(Func algorithm, TList<T>* list) {
    auto start = std::chrono::high_resolution_clock::now();
    bool result = algorithm(list);
    auto end = std::chrono::high_resolution_clock::now();
    int64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>
                                                     (end - start).count();
    return duration;
}

void compareAlgorithms() {
    TMassive<size_t> sizes;
    sizes.push_back(1000);
    sizes.push_back(10000);
    sizes.push_back(100000);

    for (size_t i = 0; i < sizes.size(); ++i) {
        size_t size = sizes[i];

        // Создаем списки
        TList<int>* linearList = generateList<int>(size, false);
        TList<int>* cyclicList = generateList<int>(size, true);

        // Измеряем время для линейного списка
        int64_t timeFloydLinear = measureAlgorithmTime(
            hasCycleFloyd<int>, linearList);
        int64_t timeReverseLinear = measureAlgorithmTime(
            hasCycleReverse<int>, linearList);

        // Измеряем время для циклического списка
        int64_t timeFloydCyclic = measureAlgorithmTime(
            hasCycleFloyd<int>, cyclicList);
        int64_t timeReverseCyclic = measureAlgorithmTime(
            hasCycleReverse<int>, cyclicList);

        // Выводим результаты
        std::cout << "Size: " << size << "\n";
        std::cout << "Linear List:\n";
        std::cout << "  Floyd's Algorithm Time: "
                  << timeFloydLinear << " ns\n";
        std::cout << "  Reverse Pointer Algorithm Time: "
                  << timeReverseLinear << " ns\n";
        std::cout << "Cyclic List:\n";
        std::cout << "  Floyd's Algorithm Time: "
                  << timeFloydCyclic << " ns\n";
        std::cout << "  Reverse Pointer Algorithm Time: "
                  << timeReverseCyclic << " ns\n\n";

        // Очищаем память
        delete linearList;
        delete cyclicList;
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

    #ifdef VECTOR
    VectorExample();
    #endif

    #ifdef STACK
    StackExample();
    #endif

    #ifdef QUEUE
    QueueExample();
    #endif

    #ifdef LIST
    ListExample();
    #endif

    #ifdef ALGORITHMS
    compareAlgorithms();
    #endif

    return 0;
}
