// Copyright 2024 atikdd.t.me

#ifndef LIB_PAIR_PAIR_H_
#define LIB_PAIR_PAIR_H_

#include <iostream>

// Forward declaration of template class TPair
template <class T1, class T2>
class TPair;

// Overloaded insertion operator for TPair
template <class T1, class T2>
std::ostream& operator<<(std::ostream& out, const TPair<T1, T2>& obj) noexcept;

template <class T1, class T2>
class TPair {
    T1 _first;
    T2 _second;

 public:
    // Default constructor
    TPair();
    // Parameterized constructor
    TPair(const T1& first, const T2& second);
    // Copy constructor
    TPair(const TPair& pair);
    // Destructor
    ~TPair();

    // Accessor for first element
    inline T1 first() const noexcept;
    // Accessor for second element
    inline T2 second() const noexcept;
    // Mutator for first element
    inline void set_first(const T1& value) noexcept;
    // Mutator for second element
    inline void set_second(const T2& value) noexcept;

    // Assignment operator
    TPair& operator=(const TPair& pair) noexcept;
    // Equality operator
    bool operator==(const TPair& pair) const noexcept;

    // Friend function for output
    friend std::ostream& operator<< <>(
        std::ostream& out,
        const TPair<T1, T2>& obj) noexcept;
};

// Default constructor
template <class T1, class T2>
TPair<T1, T2>::TPair() : _first(), _second() { }

// Parameterized constructor
template <class T1, class T2>
TPair<T1, T2>::TPair(const T1& first, const T2& second)
    : _first(first), _second(second) { }

// Copy constructor
template <class T1, class T2>
TPair<T1, T2>::TPair(const TPair& pair)
    : _first(pair._first), _second(pair._second) { }

// Destructor
template <class T1, class T2>
TPair<T1, T2>::~TPair() { }

// Accessor for first element
template <class T1, class T2>
T1 TPair<T1, T2>::first() const noexcept {
  return _first;
}

// Accessor for second element
template <class T1, class T2>
T2 TPair<T1, T2>::second() const noexcept {
  return _second;
}

// Mutator for first element
template <class T1, class T2>
void TPair<T1, T2>::set_first(const T1& value) noexcept {
  _first = value;
}

// Mutator for second element
template <class T1, class T2>
void TPair<T1, T2>::set_second(const T2& value) noexcept {
  _second = value;
}

// Assignment operator
template <class T1, class T2>
TPair<T1, T2>& TPair<T1, T2>::operator=(const TPair& pair) noexcept {
  if (this != &pair) {
    _first = pair._first;
    _second = pair._second;
  }
  return *this;
}

// Equality operator
template <class T1, class T2>
bool TPair<T1, T2>::operator==(const TPair& pair) const noexcept {
  return (_first == pair._first) && (_second == pair._second);
}

// Overloaded insertion operator for output
template <class T1, class T2>
std::ostream& operator<<(std::ostream& out, const TPair<T1, T2>& obj) noexcept {
  out << '(' << obj._first << ", " << obj._second << ')';
  return out;
}

#endif  // LIB_PAIR_PAIR_H_
