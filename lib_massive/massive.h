// Copyright 2024 atikdd.t.me
#include <utility>


#pragma once
#define STEP_CAPACITY 15

enum State { empty, busy, deleted };


template <typename T>
class TMassive {
    T* _data;
    State* _states;
    size_t _capacity;
    size_t _size;
    size_t _deleted;

 public:
    TMassive();

    ~TMassive();

    void print(std::ostream& out) const noexcept;

    inline bool empty() const noexcept;
    inline bool full() const noexcept;

    // size_t size();
    // size_t capacity();
    // const T* data();

    // void swap(TMassive& archive);

    // TMassive& assign(const TMassive& archive);

    // void clear();
    // void resize(size_t n, T value);
    void reserve(size_t new_capacity);

    // void push_back(T value);             // âñòàâêà ýëåìåíòà (â êîíåö)
    // void pop_back();                     // óäàëåíèå ýëåìåíòà (èç êîíöà)
    // void push_front(T value);            // âñòàâêà ýëåìåíòà (â íà÷àëî)
    // void pop_front();                    // óäàëåíèå ýëåìåíòà (èç íà÷àëà)

    // TMassive& insert(const T* arr, size_t n, size_t pos);
    TMassive& insert(const T& value, size_t pos);

    // TMassive& replace(size_t pos, T new_value);

    TMassive& erase(size_t pos, size_t n);
    // TMassive& remove_all(T value);
    // TMassive& remove_first(T value);
    // TMassive& remove_last(T value);
    // TMassive& remove_by_index(size_t pos);

    // size_t* find_all(T value) const noexcept;
    // size_t find_first(T value);
    // size_t find_last(T value);
 private:
    // size_t count_value(T value);
};

template <typename T>
TMassive<T>::TMassive() {
    _size = 0;
    _capacity = STEP_CAPACITY;
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (size_t i = 0; i < STEP_CAPACITY; i++) {
        _states[i] = State::empty;
    }
}

template <typename T>
TMassive<T>::~TMassive() {
    delete[] _data;
    _data = nullptr;
}

template <typename T>
inline bool TMassive<T>::empty() const noexcept {
    return _size == 0;
}

template <typename T>
inline bool TMassive<T>::full() const noexcept {
    return _size == _capacity;
}



template <typename T>
void TMassive<T>::reserve(size_t new_capacity) {
    if (new_capacity <= _capacity) return;
    T* new_data = new T[new_capacity];
    State* new_states = new State[new_capacity];
    // Copy existing data
    for (size_t i = 0; i < _size; ++i) {
        new_data[i] = _data[i];
        new_states[i] = _states[i];
    }
    // Initialize remaining states
    for (size_t i = _size; i < new_capacity; ++i) {
        new_states[i] = State::empty;
    }
    delete[] _data;
    delete[] _states;
    _data = new_data;
    _states = new_states;
    _capacity = new_capacity;
}


template <typename T>
TMassive<T>& TMassive<T>::insert(const T& value, size_t pos) {
    if (pos > _size) {
        throw std::out_of_range("Insert position is out of range.");
    }
    if (_size >= _capacity) {
        reserve(_capacity + STEP_CAPACITY);
    }
    for (size_t i = _size; i > pos; --i) {
        _data[i] = _data[i - 1];
        _states[i] = _states[i - 1];
    }
    _data[pos] = value;
    _states[pos] = State::busy;
    ++_size;
    return *this;
}

template <typename T>
TMassive<T>& TMassive<T>::erase(size_t pos, size_t n) {
    if (pos >= _size) {
        throw std::out_of_range("Erase position is out of range.");
    }
    if (n == 0) {
        return *this;
    }
    size_t erase_count = n;
    if (pos + n > _size) {
        erase_count = _size - pos;
    }
    for (size_t i = pos; i + erase_count < _size; ++i) {
        _data[i] = _data[i + erase_count];
        _states[i] = _states[i + erase_count];
    }
    for (size_t i = _size - erase_count; i < _size; ++i) {
        _states[i] = State::empty;
    }
    _size -= erase_count;
    return *this;
}

template <typename T>
void TMassive<T>::print(std::ostream& out) const noexcept {
    for (size_t i = 0; i < _size; ++i) {
        if (_states[i] != State::deleted) {
            out << _data[i] << ", ";
        }
    }
}

/*
// ïðèìåð ðåàëèçàöèè ñ âîçâðàòîì ìàññèâà íàéäåííûõ ïîçèöèé
template <typename T>
size_t* TMassive<T>::find_all (T value) const noexcept {
    size_t count = this->count_value(value);
    if (count == 0) { return nullptr; }
    int* found_positions = new int[count + 1];
    found_positions[0] = count;

    // TBD

    return found_positions;
}
*/
