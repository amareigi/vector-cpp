#ifndef CONTAINERS_VECTOR_H_
#define CONTAINERS_VECTOR_H_

#include <initializer_list>
#include <limits>
namespace s21 {
template <typename T, typename Alloc = std::allocator<T>>
class vector {
 public:
  using value_type = T;
  using value_type_ptr = T*;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
  using AllocTraits = std::allocator_traits<Alloc>;

 private:
  Alloc alloc_;
  size_type sz_;
  size_type cap_;
  value_type_ptr ptr_;

  template <bool IsConst>
  class base_iterator;

 public:
  // iterators
  using iterator = base_iterator<false>;
  using const_iterator = base_iterator<true>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;

  // main methods
  vector(const Alloc& alloc = Alloc());  // default constructor
  vector(size_type n, const_reference value = value_type(),
         const Alloc& alloc = Alloc());  // param
  vector(std::initializer_list<value_type> const& items,
         const Alloc& alloc = Alloc());
  vector(const vector& v);                           // copy
  vector(vector&& v, const Alloc& alloc = Alloc());  // move
  vector& operator=(const vector& v);                // copy assignment
  vector& operator=(vector&& v);                     // move assignment
  ~vector();

  // access methods
  reference at(size_type pos);  // access with bounds cheking
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  const_reference front();  // access first element
  const_reference back();   // access last element
  T* data();                // direct access

  // capacity methods
  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  // modifiers
  void clear();
  iterator insert(const_iterator pos, const_reference value);
  iterator erase(const_iterator pos);
  template <typename... U>
  reference emplace_back(U&&... value);
  template <typename U>
  void push_back(U&& value);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector& other);
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);

  // private
};
}  // namespace s21
// сделать ещё вектор булей, специализацию, но не уверен, что это нужно
// сделать разбивку на много .inc по всем группам методов, т.е. main, midifiers,
// capacity  и т.д.
#include "./inc/vector_capacity_methods.inc"
#include "./inc/vector_elements_methods.inc"
#include "./inc/vector_iterator_methods.inc"
#include "./inc/vector_main_methods.inc"
#include "./inc/vector_modifiers_methods.inc"

#endif  // CONTAINERS_VECTOR_H_
