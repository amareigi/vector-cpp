#ifndef S21_CONTAINERS_ARRAY_TPP
#define S21_CONTAINERS_ARRAY_TPP

#include "s21_array.h"

namespace s21 {

// Vector Member functions

template <typename T, size_t N>
array<T, N>::array(std::initializer_list<T> const &items) : size_(N) {
  for (size_type i = 0; i < size_; ++i) data_[i] = *(items.begin() + i);
}

template <typename T, size_t N>
array<T, N>::array(const array &other) : size_(N) {
  for (size_type i = 0; i < size_; i++) data_[i] = other.data_[i];
}

template <typename T, size_t N>
typename array<T, N>::array &array<T, N>::operator=(const array &other) {
  if (this != &other) {
    size_ = other.size_;
    for (size_type i = 0; i < size_; i++) data_[i] = other.data_[i];
  }
  return *this;
}

template <typename T, size_t N>
array<T, N>::array(array &&other) : size_(other.size_) {
  for (size_type i = 0; i < size_; i++) {
    data_[i] = std::move(other.data_[i]);
    // other.data_[i] = T();
  }
  // other.size_ = 0;
}

template <typename T, size_t N>
typename array<T, N>::array &array<T, N>::operator=(array &&other) {
  if (this != &other) {
    size_ = other.size_;
    for (size_type i = 0; i < size_; i++) data_[i] = std::move(other.data_[i]);
  }
  return *this;
}

template <typename T, size_t N>
void array<T, N>::swap(array<T, N> &other) {
  std::swap(data_, other.data_);
}

template <typename T, size_t N>
void array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < size_; i++) data_[i] = value;
}

}  // namespace s21

#endif  // S21_CONTAINERS_ARRAY_TPP