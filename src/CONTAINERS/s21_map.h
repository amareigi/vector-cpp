#ifndef S21_CONTAINERS_MAP_H
#define S21_CONTAINERS_MAP_H

#include "RB_Tree.h"

namespace s21 {

template <typename Key, typename T>
class map : RB_Tree<Key, T, false> {
 public:
  using key_type = Key;
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using parent_t = RB_Tree<Key, T, false>;
  using node_t = typename parent_t::node_t;
  using iterator = typename parent_t::treeIterator;
  using const_iterator = typename parent_t::constTreeIterator;

  using RB_Tree<Key, T, false>::RB_Tree;

  map() : parent_t(){};
  map(std::initializer_list<std::pair<key_type, value_type>> const &items) {
    for (std::pair<key_type, value_type> item : items) {
      parent_t::insertData(item.first, item.second);
    }
  }
  map(const map &other) : parent_t(other){};
  map(map &&other) : parent_t(std::move(other)){};
  ~map(){};

  map &operator=(const map &other) {
    parent_t::copy(other);
    return *this;
  };

  map &operator=(map &&other) {
    parent_t::move(std::move(other));
    return *this;
  };

  reference operator[](const key_type &key) {
    node_t *node = parent_t::findNode(key);
    if (!node) {
      node = new node_t(nullptr, nullptr, nullptr, parent_t::RED, key,
                        value_type{});
      parent_t::insertNode(node);
    };
    return node->getValueNonConst();
  };

  std::pair<iterator, bool> insert(
      const std::pair<key_type, value_type> &value) {
    return parent_t::insertData(value.first, value.second);
  };

  std::pair<iterator, bool> insert(const key_type &key, const value_type &obj) {
    return parent_t::insertData(key, obj);
  };

  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const value_type &obj) {
    std::pair<iterator, bool> val = parent_t::insertData(key, obj);
    if (!val.second) {
      val.first.getPos()->getValueNonConst() = obj;
    }
    return val;
  };

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::initializer_list<std::pair<key_type, value_type>> items = {args...};
    vector<std::pair<iterator, bool>> temp;

    for (const std::pair<key_type, value_type> &item : items) {
      temp.push_back(insert(item));
    }
    return temp;
  };

  void clear() { parent_t::clearTree(); };
  void erase(iterator pos) { parent_t::erase(pos); };
  bool empty() { return parent_t::empty(); };
  bool contains(const value_type &key) { return parent_t::contains(key); };
  void swap(map &other) { return parent_t::swap(other); };
  void merge(map &other) { return parent_t::merge(other); };

  size_type size() { return parent_t::size(); };
  size_type max_size() { return parent_t::max_size(); };
  iterator begin() { return parent_t::begin(); };
  iterator end() { return parent_t::end(); };
  const_iterator cbegin() { return parent_t::cbegin(); };
  const_iterator cend() { return parent_t::cend(); };

  reference at(const key_type &key) {
    if (!parent_t::contains(key)) {
      throw std::out_of_range("Element does not exist");
    };
    return parent_t::findNode(key)->getValueNonConst();
  };
};

}  // namespace s21

#endif  // S21_CONTAINERS_MAP_H