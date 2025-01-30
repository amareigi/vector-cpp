#ifndef CONTAINERS_TESTS_GTEST_START_POINT_H_
#define CONTAINERS_TESTS_GTEST_START_POINT_H_

#include <gtest/gtest.h>

#include <vector>

#include "../s21_containers.h"

// для проверки работы аллокаторов
template <typename T>
class allocator_t {
 public:
  allocator_t<T>(const allocator_t<T>&) {}
  allocator_t<T>& operator=(allocator_t<T>& v) { return v; }
  allocator_t<T>() {}
  using value_type = T;
  using propagate_on_container_swap = std::true_type;
  T* allocate(size_t count) const {
    return reinterpret_cast<T*>(::operator new(count * sizeof(T)));
  }
  void deallocate(T* ptr, size_t) { ::operator delete(ptr); }
  bool operator==(allocator_t) { return true; }
};

template <typename T>
class allocator_f {
 public:
  allocator_f<T>(const allocator_f<T>&) {}
  allocator_f<T>& operator=(allocator_f<T>& v) { return v; }
  allocator_f<T>() {}
  using value_type = T;
  T* allocate(size_t count) const {
    return reinterpret_cast<T*>(::operator new(count * sizeof(T)));
  }
  void deallocate(T* ptr, size_t) { ::operator delete(ptr); }
  bool operator==(allocator_f) { return false; }
};
#endif  // CONTAINERS_TESTS_GTEST_START_POINT_H_
