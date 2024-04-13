#ifndef S21_CONTAINERS_ARRAY_H
#define S21_CONTAINERS_ARRAY_H

#include <cstddef>
#include <initializer_list>

namespace s21 {
template <typename T, size_t N>

class array {
 private:
  T data_[N];
  size_t size_ = N;

 public:
  // Array Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // Array Member functions
  array() : size_(N) {
    for (size_t i = 0; i < size_; ++i) data_[i] = T();
  }
  array(std::initializer_list<T> const &items);
  array(const array &other);
  array(array &&other);
  ~array() {}
  array &operator=(array &&other);
  array &operator=(const array &other);

  // Array Element access
  reference at(size_type pos) { return data_[pos]; }
  reference operator[](size_type pos) { return data_[pos]; }
  const_reference front() { return data_[0]; }
  const_reference back() { return data_[size_ - 1]; }
  T *data() { return data_; }

  // Array Iterators
  iterator begin() { return data_; }
  iterator end() { return data_ + size_; }

  // Array capacity
  bool empty() const { return size_ == 0; }
  size_type size() const { return size_; }
  size_type max_size() { return size_; }

  // Array Modifiers
  void swap(array &other);
  void fill(const_reference value);
};

}  // namespace s21

#include "s21_array.tpp"
#endif  // S21_CONTAINERS_ARRAY_H
