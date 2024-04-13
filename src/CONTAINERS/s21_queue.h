#ifndef S21_CONTAINERS_QUEUE_H
#define S21_CONTAINERS_QUEUE_H

#include "deque.h"

namespace s21 {

template <typename T, typename parrent_t = deque<T>>
class queue : public deque<T> {
 public:
  using value_type = T;
  using const_reference = const T&;

  using deque<T>::deque;

  queue(std::initializer_list<value_type> const& items) : parrent_t() {
    for (value_type item : items) {
      this->pushBack(item);
    }
  };

  const_reference front() { return this->_node->data; };

  const_reference back() {
    auto* temp = this->_node;
    while (temp->next) temp = temp->next;
    return temp->data;
  };

  void push(const_reference value) { this->pushBack(value); };

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    std::initializer_list<value_type> items = {args...};
    for (const_reference item : items) {
      parrent_t::pushBack(item);
    }
  };
};

}  // namespace s21

#endif  // S21_CONTAINERS_QUEUE_H