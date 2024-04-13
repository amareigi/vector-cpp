#ifndef S21_CONTAINERS_STACK_H
#define S21_CONTAINERS_STACK_H

#include "deque.h"

namespace s21 {

template <typename T, typename parrent_t = deque<T>>
class stack : public deque<T> {
 public:
  using value_type = T;
  using const_reference = const T&;

  using deque<T>::deque;

  stack(std::initializer_list<value_type> const& items) : parrent_t() {
    for (value_type item : items) {
      this->push(item);
    }
  };

  const_reference top() { return this->_node->data; };

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    std::initializer_list<value_type> items = {args...};
    for (const_reference item : items) {
      parrent_t::push(item);
    }
  };
};

}  // namespace s21

#endif  // S21_CONTAINERS_STACK_H