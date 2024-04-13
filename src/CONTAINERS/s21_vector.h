#ifndef S21_CONTAINERS_VECTOR_H
#define S21_CONTAINERS_VECTOR_H

#include <initializer_list>

namespace s21 {
template <typename T>

class vector {
 private:
  T* data_;
  size_t capacity_;
  size_t size_;

 public:
  // Vector Member type
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

  // Vector Member functions
  vector() : data_(nullptr), capacity_(0), size_(0){};
  vector(size_type size_);
  vector(std::initializer_list<T> const& items);
  vector(const vector& other);
  vector(vector&& other);
  ~vector() { delete[] data_; }
  vector& operator=(vector&& other);
  vector& operator=(const vector& other);

  // Vector Element access
  reference at(size_type pos) { return data_[pos]; }
  reference operator[](size_type pos) { return data_[pos]; }
  const_reference front() { return data_[0]; }
  const_reference back() { return data_[size_ - 1]; }
  T* data() { return data_; }

  // Vector Iterators
  iterator begin() { return data_; }
  iterator end() { return data_ + size_; }

  // Vector capacity
  bool empty() const { return size_ == 0; }
  size_type size() const { return size_; }
  size_type max_size() {
    return std::numeric_limits<std::size_t>::max() / sizeof(value_type) / 2;
  }
  void reserve(size_type new_capacity);
  size_type capacity() const { return capacity_; }
  void shrink_to_fit();

  // Vector Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector& other);

  void SetCapacity(size_type cap) { capacity_ = cap; }
  void SetSize(size_type sz) { size_ = sz; }
  void SetData(T* dt) { data_ = dt; }

  // Insert_many
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);
};

}  // namespace s21

#include "s21_vector.tpp"
#endif  // S21_CONTAINERS_VECTOR_H
