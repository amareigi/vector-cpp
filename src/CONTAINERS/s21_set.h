#ifndef S21_CONTAINERS_SET_H
#define S21_CONTAINERS_SET_H

#include "RB_Tree.h"

namespace s21 {

template <typename Key>
class set : RB_Tree<Key, Key, false> {
 public:
  using value_type = Key;
  using key_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using parent_t = RB_Tree<Key, Key, false>;
  using iterator = typename parent_t::treeIterator;
  using const_iterator = typename parent_t::constTreeIterator;

  using RB_Tree<Key, Key, false>::RB_Tree;

  set() : parent_t(){};
  set(std::initializer_list<value_type> const &items) {
    for (const_reference item : items) {
      parent_t::insertData(item, item);
    }
  }
  set(const set &other) : parent_t(other){};
  set(set &&other) : parent_t(std::move(other)){};
  ~set(){};

  set &operator=(const set &other) {
    parent_t::copy(other);
    return *this;
  };

  set &operator=(set &&other) {
    parent_t::move(std::move(other));
    return *this;
  };

  std::pair<iterator, bool> insert(const value_type &value) {
    return parent_t::insertData(value, value);
  };

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::initializer_list<key_type> items = {args...};
    vector<std::pair<iterator, bool>> temp;

    for (const_reference item : items) {
      temp.push_back(insert(item));
    }
    return temp;
  };

  void clear() { parent_t::clearTree(); };
  bool empty() { return parent_t::empty(); };
  void erase(iterator pos) { parent_t::erase(pos); };
  void swap(set &other) { return parent_t::swap(other); };
  void merge(set &other) { return parent_t::merge(other); };
  bool contains(const value_type &key) { return parent_t::contains(key); };

  size_type size() { return parent_t::size(); };
  size_type max_size() { return parent_t::max_size(); };

  iterator begin() { return parent_t::begin(); };
  iterator end() { return parent_t::end(); };

  const_iterator cbegin() { return parent_t::cbegin(); };
  const_iterator cend() { return parent_t::cend(); };

  iterator find(const value_type &key) {
    return iterator{parent_t::findNode(key), nullptr};
  };
};

}  // namespace s21

#endif  // S21_CONTAINERS_SET_H