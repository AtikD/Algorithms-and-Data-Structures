// Copyright 2024 atikdd.t.me
#include <utility>
#include <ostream>

#pragma once
#define STEP_CAPACITY 15

enum State { empty, busy, deleted };


template <typename T>
class TMassive {
    T* _data;
    State* _states;
    size_t _capacity;
    size_t _size;

 public:
    TMassive();
    TMassive(const TMassive<T>& other);
    TMassive(TMassive<T>&& other) noexcept;
    ~TMassive();

    void print(std::ostream& out) const noexcept;

    inline bool empty() const noexcept;
    inline bool full() const noexcept;

    size_t size() const noexcept;
    size_t capacity() const noexcept;
    const T* data() const noexcept;

    void swap(TMassive& archive) noexcept;

    TMassive& assign(const TMassive& archive);

    void clear();
    void resize(size_t n, const T& value);
    void reserve(size_t new_capacity);

    void push_back(const T& value);
    void pop_back();
    void push_front(const T& value);
    void pop_front();

    TMassive& insert(const T* arr, size_t n, size_t pos);
    TMassive& insert(const T& value, size_t pos);

    TMassive& replace(size_t pos, const T& new_value);

    TMassive& erase(size_t pos, size_t n);
    TMassive& remove_all(const T& value);
    TMassive& remove_first(const T& value);
    TMassive& remove_last(const T& value);
    TMassive& remove_by_index(size_t pos);
    size_t find_last(const T& value) const;
    size_t find_first(const T& value) const;
    size_t* find_all(const T& value) const noexcept;
    TMassive<T>& operator=(const TMassive<T>& other);
    TMassive<T>& operator=(TMassive<T>&& other) noexcept;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

 private:
    size_t count_value(T value) const noexcept;
};

template <typename T>
TMassive<T>::TMassive() {
    _size = 0;
    _capacity = STEP_CAPACITY;
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (size_t i = 0; i < _capacity; ++i) {
        _states[i] = State::empty;
    }
}

template <typename T>
TMassive<T>::TMassive(const TMassive<T>& other) {
    _size = other._size;
    _capacity = other._capacity;
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (size_t i = 0; i < _capacity; ++i) {
        _states[i] = other._states[i];
        if (_states[i] == State::busy) {
            _data[i] = other._data[i];
        }
    }
}

template <typename T>
T& TMassive<T>::operator[](size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range.");
    }
    if (_states[index] != State::busy) {
        throw std::logic_error("Element at this index is not valid.");
    }
    return _data[index];
}

template <typename T>
const T& TMassive<T>::operator[](size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("Index out of range.");
    }
    if (_states[index] != State::busy) {
        throw std::logic_error("Element at this index is not valid.");
    }
    return _data[index];
}

template <typename T>
TMassive<T>::TMassive(TMassive<T>&& other) noexcept {
    _data = other._data;
    _states = other._states;
    _size = other._size;
    _capacity = other._capacity;

    other._data = nullptr;
    other._states = nullptr;
    other._size = 0;
    other._capacity = 0;
}

template <typename T>
TMassive<T>& TMassive<T>::operator=(const TMassive<T>& other) {
    if (this != &other) {
        delete[] _data;
        delete[] _states;

        _size = other._size;
        _capacity = other._capacity;
        _data = new T[_capacity];
        _states = new State[_capacity];
        for (size_t i = 0; i < _capacity; ++i) {
            _states[i] = other._states[i];
            if (_states[i] == State::busy) {
                _data[i] = other._data[i];
            }
        }
    }
    return *this;
}

template <typename T>
TMassive<T>& TMassive<T>::operator=(TMassive<T>&& other) noexcept {
    if (this != &other) {
        delete[] _data;
        delete[] _states;

        _data = other._data;
        _states = other._states;
        _size = other._size;
        _capacity = other._capacity;

        other._data = nullptr;
        other._states = nullptr;
        other._size = 0;
        other._capacity = 0;
    }
    return *this;
}


template <typename T>
TMassive<T>::~TMassive() {
    delete[] _data;
    delete[] _states;
    _data = nullptr;
    _states = nullptr;
}

template <typename T>
size_t TMassive<T>::size() const noexcept {
    return _size;
}

template <typename T>
size_t TMassive<T>::capacity() const noexcept {
    return _capacity;
}

template <typename T>
const T* TMassive<T>::data() const noexcept {
    return _data;
}

template <typename T>
void TMassive<T>::swap(TMassive& archive) noexcept {
    std::swap(_data, archive._data);
    std::swap(_states, archive._states);
    std::swap(_size, archive._size);
    std::swap(_capacity, archive._capacity);
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
TMassive<T>& TMassive<T>::assign(const TMassive& archive) {
    if (this != &archive) {
        delete[] _data;
        delete[] _states;

        _capacity = archive._capacity;
        _size = archive._size;

        _data = new T[_capacity];
        _states = new State[_capacity];

        for (size_t i = 0; i < _size; ++i) {
            _data[i] = archive._data[i];
            _states[i] = archive._states[i];
        }
        // Инициализируем оставшиеся состояния
        for (size_t i = _size; i < _capacity; ++i) {
            _states[i] = State::empty;
        }
    }
    return *this;
}


template <typename T>
void TMassive<T>::clear() {
    for (size_t i = 0; i < _size; ++i) {
        _states[i] = State::empty;
    }
    _size = 0;
}



template <typename T>
void TMassive<T>::resize(size_t n, const T& value) {
    if (n < _size) {
        for (size_t i = n; i < _size; ++i) {
            _states[i] = State::empty;
        }
        _size = n;
    } else if (n > _size) {
        if (n > _capacity) {
            reserve(n);
        }
        for (size_t i = _size; i < n; ++i) {
            _data[i] = value;
            _states[i] = State::busy;
        }
        _size = n;
    }
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
void TMassive<T>::push_back(const T& value) {
    insert(value, _size);
}

template <typename T>
void TMassive<T>::pop_back() {
    if (_size == 0) {
        throw std::out_of_range("Archive is empty.");
    }
    _states[_size - 1] = State::empty;
    --_size;
}


template <typename T>
void TMassive<T>::push_front(const T& value) {
    insert(value, 0);
}

template <typename T>
void TMassive<T>::pop_front() {
    if (_size == 0) {
        throw std::out_of_range("Archive is empty.");
    }
    erase(0, 1);
}

template <typename T>
TMassive<T>& TMassive<T>::insert(const T* arr, size_t n, size_t pos) {
    if (pos > _size) {
        throw std::out_of_range("Insert position is out of range.");
    }
    if (n == 0) {
        return *this;
    }
    if (_size + n > _capacity) {
        reserve(_size + n);
    }
    for (size_t i = _size; i > pos; --i) {
        _data[i + n - 1] = _data[i - 1];
        _states[i + n - 1] = _states[i - 1];
    }
    for (size_t i = 0; i < n; ++i) {
        _data[pos + i] = arr[i];
        _states[pos + i] = State::busy;
    }
    _size += n;
    return *this;
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
TMassive<T>& TMassive<T>::replace(size_t pos, const T& new_value) {
    if (pos >= _size) {
        throw std::out_of_range("Position is out of range.");
    }
    if (_states[pos] != State::busy) {
        throw std::logic_error("Cannot replace an empty or deleted position.");
    }
    _data[pos] = new_value;
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
TMassive<T>& TMassive<T>::remove_all(const T& value) {
    size_t i = 0;
    while (i < _size) {
        if (_states[i] == State::busy && _data[i] == value) {
            erase(i, 1);
        } else {
            ++i;
        }
    }
    return *this;
}

template <typename T>
TMassive<T>& TMassive<T>::remove_first(const T& value) {
    for (size_t i = 0; i < _size; ++i) {
        if (_states[i] == State::busy && _data[i] == value) {
            erase(i, 1);
            return *this;
        }
    }
    throw std::logic_error("Value not found in the archive.");
}

template <typename T>
TMassive<T>& TMassive<T>::remove_last(const T& value) {
    for (size_t i = _size; i > 0; --i) {
        size_t index = i - 1;
        if (_states[index] == State::busy && _data[index] == value) {
            erase(index, 1);
            return *this;
        }
    }
    throw std::logic_error("Value not found in the archive.");
}

template <typename T>
TMassive<T>& TMassive<T>::remove_by_index(size_t pos) {
    if (pos >= _size) {
        throw std::out_of_range("Index is out of range.");
    }
    erase(pos, 1);
    return *this;
}

template <typename T>
size_t TMassive<T>::find_last(const T& value) const {
    for (size_t i = _size; i > 0; --i) {
        size_t index = i - 1;
        if (_states[index] == State::busy && _data[index] == value) {
            return index;
        }
    }
    throw std::logic_error("Value not found in the archive.");
}

template <typename T>
size_t TMassive<T>::find_first(const T& value) const {
    for (size_t i = 0; i < _size; ++i) {
        if (_states[i] == State::busy && _data[i] == value) {
            return i;
        }
    }
    throw std::logic_error("Value not found in the archive.");
}

template <typename T>
size_t* TMassive<T>::find_all(const T& value) const noexcept {
    size_t count = count_value(value);
    if (count == 0) {
        return nullptr;
    }
    size_t* indices = new size_t[count+1];
    indices[0] = count;
    size_t idx = 1;
    for (size_t i = 0; i < _size; ++i) {
        if (_states[i] == State::busy && _data[i] == value) {
            indices[idx++] = i;
        }
    }
    return indices;
}



template <typename T>
size_t TMassive<T>::count_value(T value) const noexcept {
    size_t count = 0;
    for (size_t i = 0; i < _size; i++) {
        if (_data[i] == value) {
            count++;
        }
    }
    return count;
}

template <typename T>
void TMassive<T>::print(std::ostream& out) const noexcept {
    for (size_t i = 0; i < _size; ++i) {
        if (_states[i] != State::deleted) {
            out << _data[i] << ", ";
        }
    }
}
