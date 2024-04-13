#ifndef CONTAINERS_H_
#define CONTAINERS_H_

#include <stdio.h>

#include <cstddef>
#include <initializer_list>
#include <limits>
namespace s21 {

template <class T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  /************************** List Functions *******************************/
  list() {
    _size = 0;
    head = nullptr;
    tail = nullptr;
  }

  list(size_type n) : list() {
    if (n < 1) throw "incorrect size";
    for (size_type i = 0; i < n; i++) {
      private_add_back();
      _size++;
    }
  }

  list(std::initializer_list<value_type> const &items) : list() {
    for (auto i = items.begin(); i != items.end(); i++) push_back(*i);
  }

  list(const list &l) : list() {
    Node *tmp = l.head;
    while (tmp) {
      push_back(tmp->value);
      tmp = tmp->next;
    }
  }

  list(list &&l) {
    _size = l._size;
    head = l.head;
    tail = l.tail;
    l._size = 0;
    l.head = nullptr;
    l.tail = nullptr;
  }

  ~list() {
    while (head) {
      Node *tmp = head;
      head = head->next;
      delete tmp;
    }
    _size = 0;
  }

  list &operator=(list &&l) {
    if (this != &l) {
      this->~list();
      _size = l._size;
      head = l.head;
      tail = l.tail;
      l._size = 0;
      l.head = nullptr;
      l.tail = nullptr;
    }
    return *this;
  }

  /************************ List Element access *****************************/

  const_reference front() { return head->value; }

  const_reference back() { return tail->value; }

  /************************ List Capacity *****************************/
  bool empty() { return head == nullptr; }

  size_type size() { return _size; }

  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(Node) / 2;
  }

  /************************ List Modifiers *****************************/

  void clear() { this->~list(); }

  void push_back(const_reference data) {
    private_add_back();
    tail->value = data;
    _size++;
  }

  void pop_back() {
    if (tail) {
      Node *node = tail;
      tail = tail->prev;
      if (tail) {
        tail->next = nullptr;
      } else {
        head = nullptr;
      }
      delete node;
      _size--;
    }
  }

  void push_front(const_reference data) {
    Node *node = new Node(data);
    node->next = head;
    node->prev = nullptr;
    if (head) {
      head->prev = node;
    }
    head = node;
    if (tail == nullptr) {
      tail = node;
    }
    _size++;
  }

  void pop_front() {
    if (head) {
      Node *node = head;
      head = head->next;
      if (head) {
        head->prev = nullptr;
      } else {
        tail = nullptr;
      }
      delete node;
      _size--;
    }
  }

  void swap(list &other) {
    if (this != &other) {
      std::swap(head, other.head);
      std::swap(_size, other._size);
    }
  }

  void merge(list &other) {
    if (this != &other) {
      iterator this_begin = begin();
      iterator this_end = end();
      iterator other_begin = other.begin();
      iterator other_end = other.end();
      while (this_begin != this_end && other_begin != other_end) {
        if (*other_begin < *this_begin) {
          Node *tmp = other_begin.node_;
          ++other_begin;
          tmp->UnAttach();
          --other._size;
          this_begin.node_->AttachPrev(tmp);
          ++_size;
        } else {
          ++this_begin;
        }
      }
      splice(end(), other);
      other.~list();
    }
  }

  void reverse() {
    if (this->_size > 1) {
      Node *node = this->head;
      for (size_type i = 0; i < this->_size; ++i) {
        std::swap(node->prev, node->next);
        node = node->prev;
      }
      std::swap(this->head, this->tail);
    }
  }

  void unique() {
    if (!this->empty()) {
      for (iterator it_last = begin(); it_last != end();) {
        iterator it_next = it_last;
        ++it_next;
        if (it_next.node_ == nullptr) {
          break;
        } else if (*it_last == *it_next) {
          erase(it_next);
        } else {
          ++it_last;
        }
      }
    }
  }

  void sort() {
    if (head != nullptr && _size > 1) {
      size_type i, j;
      for (i = 0; i <= _size; i++) {
        Node **h;
        h = &head;
        int swapped;
        swapped = 0;
        for (j = 0; j < _size - i - 1; j++) {
          Node *p1 = *h;
          Node *p2 = p1->next;
          if (p1->value > p2->value) {
            *h = swap(p1, p2);
            swapped = 1;
          }
          h = &(*h)->next;
        }
        if (swapped == 0) break;
      }
      // тут восстанавливаем указатели на prev
      Node *tmp = head;
      while (tmp->next != nullptr) {
        tmp->next->prev = tmp;
        tmp = tmp->next;
      }
      tail = tmp;
    }
  }

  /************************ List Iterators *****************************/

  friend class ListIterator;
  class ListIterator {
    friend class list<T>;

   public:
    ListIterator() {}
    ListIterator(class list<T>::Node *node) : node_(node) {}
    ListIterator(class list<T>::Node *node, class list<T>::Node *last_node)
        : node_(node), last_node_(last_node) {}

    reference operator*() const { return node_->value; }

    value_type *operator->() const { return &node_->value; }

    ListIterator &operator++() {
      last_node_ = node_;
      node_ = node_->next;
      return *this;
    }

    ListIterator operator++(int) {
      ListIterator it = *this;
      node_ = node_->next;
      return it;
    }

    ListIterator &operator--() {
      if (node_ == nullptr) {
        node_ = last_node_;
      } else {
        node_ = node_->prev;
      }
      return *this;
    }

    ListIterator operator--(int) {
      ListIterator it = *this;
      node_ = node_->prev;
      return it;
    }

    bool operator==(const ListIterator &other) const {
      return node_ == other.node_;
    }

    bool operator!=(const ListIterator &other) const {
      return node_ != other.node_;
    }

   protected:
    class list<T>::Node *node_;
    class list<T>::Node *last_node_;
  };

  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator() : ListIterator(){};
    ListConstIterator(const ListIterator &node_) : ListIterator(node_){};
    const_reference operator*() const { return ListIterator::operator*(); }
  };

  using iterator = ListIterator;

  using const_iterator = ListConstIterator;

  iterator begin() { return iterator(this->head); }

  iterator end() {
    return this->head ? iterator(this->tail->next, this->tail) : begin();
  }

  iterator insert(iterator pos, const_reference value) {
    if (pos == begin()) {
      push_front(value);
      pos = this->head;
    } else if (pos == this->end()) {
      push_back(value);
      pos = this->tail;
    } else {
      Node *current = pos.node_;
      Node *blank = new Node(value);
      blank->next = current;
      blank->prev = current->prev;
      current->prev->next = blank;
      current->prev = blank;
      this->_size++;
      return iterator(blank);
    }
    return pos;
  }

  void erase(iterator pos) {
    if (pos == begin()) {
      pop_front();
    } else if (pos.node_ == this->tail) {
      pop_back();
    } else {
      Node *node = pos.node_;
      node->prev->next = node->next;
      node->next->prev = node->prev;
      delete node;
      this->_size--;
    }
  }

  void splice(const_iterator pos, list &other) {
    if (!other.empty())
      for (iterator it = other.begin(); it != other.end(); ++it)
        insert(pos, *it);
  }

  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    for (const auto &arg : {args...}) {
      insert(pos, arg);
    }
    return pos;
  }
  template <class... Args>
  void insert_many_back(Args &&...args) {
    for (const auto &arg : {args...}) {
      push_back(arg);
    }
  }
  template <class... Args>
  void insert_many_front(Args &&...args) {
    for (const auto &arg : {args...}) {
      push_front(arg);
    }
  }

 protected:
  class Node {
   public:
    value_type value;
    Node *next;
    Node *prev;
    Node(value_type val = value_type(), Node *next_node = nullptr,
         Node *prev_node = nullptr)
        : value(val), next(next_node), prev(prev_node) {}

    void AttachPrev(Node *new_node) {
      new_node->next = this;
      new_node->prev = prev;
      prev->next = new_node;
      prev = new_node;
    }

    void UnAttach() {
      prev->next = next;
      next->prev = prev;
      next = this;
      prev = this;
    }
  };

  Node *swap(Node *ptr1, Node *ptr2) {
    Node *tmp = ptr2->next;
    ptr2->next = ptr1;
    ptr1->next = tmp;
    return ptr2;
  }

  void private_add_back() {
    Node *new_node = new Node();
    new_node->prev = tail;
    new_node->next = nullptr;
    if (tail) {
      tail->next = new_node;
    }
    tail = new_node;
    if (head == nullptr) {
      head = new_node;
    }
  }

  size_type _size;
  Node *head;
  Node *tail;
};

}  // namespace s21
#endif
