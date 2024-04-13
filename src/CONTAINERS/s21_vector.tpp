#ifndef S21_CONTAINERS_VECTOR_TPP
#define S21_CONTAINERS_VECTOR_TPP

#include "s21_vector.h"

namespace s21 {

// Vector Member functions

template <typename T>
vector<T>::vector(size_type size_)
    : data_(new T[size_]), capacity_(size_), size_(size_) {
  if (data_ == nullptr) throw "Memory allocation failed";
  for (size_type i = 0; i < size_; ++i) data_[i] = T();
}
template <typename T>
vector<T>::vector(std::initializer_list<T> const& items)
    : capacity_(items.size()), size_(items.size()) {
  data_ = new T[capacity_];
  if (data_ == nullptr) throw "Memory allocation failed";
  for (size_type i = 0; i < size_; ++i) data_[i] = *(items.begin() + i);
}
template <typename T>
vector<T>::vector(const vector& other)
    : data_(new T[other.size_]),
      capacity_(other.capacity_),
      size_(other.size_) {
  if (data_ == nullptr) throw "Memory allocation failed";
  for (size_type i = 0; i < size_; i++) data_[i] = other.data_[i];
}
template <typename T>
typename vector<T>::vector& vector<T>::operator=(const vector& other) {
  if (this != &other) {
    capacity_ = other.capacity_;
    size_ = other.size_;
    data_ = new T[size_];
    if (data_ == nullptr) throw "Memory allocation failed";
    for (size_type i = 0; i < size_; i++) data_[i] = other.data_[i];
  }
  return *this;
}
template <typename T>
vector<T>::vector(vector&& other)
    : data_(other.data_), capacity_(other.capacity_), size_(other.size_) {
  other.capacity_ = 0;
  other.size_ = 0;
  other.data_ = nullptr;
}
template <typename T>
typename vector<T>::vector& vector<T>::operator=(vector&& other) {
  if (this != &other) {
    capacity_ = other.capacity_;
    size_ = other.size_;
    data_ = other.data_;
    other.capacity_ = 0;
    other.size_ = 0;
    other.data_ = nullptr;
  }
  return *this;
}

// Vector capacity

template <typename T>
void vector<T>::reserve(size_type new_capacity) {
  if (new_capacity > capacity_) {
    T* new_data = new T[new_capacity];
    if (new_data == nullptr) throw "Memory allocation failed";
    for (size_type i = 0; i < size_; ++i) {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
  }
}
template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    T* new_data = new T[size_];
    if (new_data == nullptr) throw "Memory allocation failed";
    for (size_type i = 0; i < size_; ++i) {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = size_;
  }
}

// Vector Modifiers

template <typename T>
void vector<T>::clear() {
  for (size_type i = 0; i < size_; i++) data_[i] = 0;
  size_ = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type index = pos - begin();
  if (size_ == capacity_) reserve(capacity_ * 2);
  for (size_type i = size_; i > index; --i) data_[i] = data_[i - 1];
  data_[index] = value;
  size_++;
  return begin() + index;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  size_type index = pos - begin();
  for (size_type i = index; i < size_ - 1; ++i) data_[i] = data_[i + 1];
  size_--;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (size_ == capacity_)
    (capacity_ == 0) ? reserve(1) : reserve(capacity_ * 2);
  data_[size_++] = value;
}

template <typename T>
void vector<T>::pop_back() {
  if (size_ > 0) {
    data_[size_ - 1] = 0;
    size_--;
  }
}
template <typename T>
void vector<T>::swap(vector<T>& other) {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

// Insert_many
template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args&&... args) {
  size_type index = pos - begin();
  size_type args_count = sizeof...(Args);

  // Ensure capacity
  if (size_ + args_count > capacity_) {
    reserve(size_ + args_count);
  }

  // Shift elements to the right to make space for new ones
  for (size_type i = size_ + args_count - 1; i > index + args_count - 1; --i) {
    data_[i] = std::move(data_[i - args_count]);
  }

  size_type i = 0;
  (void)std::initializer_list<int>{
      ((data_[index + i++] = std::forward<Args>(args)), 0)...};

  size_ += args_count;

  return begin() + index;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args&&... args) {
  size_type args_count = sizeof...(Args);

  // Ensure capacity
  if (size_ + args_count > capacity_) {
    reserve(size_ + args_count);
  }

  // Вставляем новые элементы в конец
  size_type i = 0;
  (void)std::initializer_list<int>{
      ((data_[size_ + i++] = std::forward<Args>(args)), 0)...};
  size_ += args_count;
}

}  // namespace s21

#endif  // S21_CONTAINERS_VECTOR_TPP
