#ifndef S21_CONTAINERS_MULTISET_H
#define S21_CONTAINERS_MULTISET_H

#include "RB_Tree.h"

namespace s21 {

template <typename Key>
class multiset : RB_Tree<Key, Key, true> {
 public:
  using value_type = Key;
  using key_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using parent_t = RB_Tree<Key, Key, true>;
  using iterator = typename parent_t::treeIterator;
  using const_iterator = typename parent_t::constTreeIterator;

  using RB_Tree<Key, Key, true>::RB_Tree;

  multiset() : parent_t(){};
  multiset(std::initializer_list<value_type> const &items) {
    for (const_reference item : items) {
      parent_t::insertData(item, item);
    }
  }
  multiset(const multiset &other) : parent_t(other){};
  multiset(multiset &&other) : parent_t(std::move(other)){};
  ~multiset(){};

  multiset &operator=(const multiset &other) {
    parent_t::copy(other);
    return *this;
  };

  multiset &operator=(multiset &&other) {
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
  void swap(multiset &other) { return parent_t::swap(other); };
  void merge(multiset &other) { return parent_t::merge(other); };
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

  std::pair<iterator, iterator> equal_range(const key_type &key) {
    iterator iter = find(key), iter_start{}, iter_end{};
    if (iter.getPos()) {
      while (iter.getPos() && iter.getPos()->getKey() == key) {
        iter_start = iter;
        --iter;
        if (iter.getPos() && iter.getPos()->getKey() == key) iter_start = iter;
      }

      iter = iter_start;
      while (iter.getPos() && iter.getPos()->getKey() == key) {
        ++iter;
      }
    }
    return {iter_start, iter};
  };

  size_type count(const key_type &key) {
    size_type count{};
    std::pair<iterator, iterator> range = equal_range(key);
    while (range.first != range.second) {
      ++count;
      ++range.first;
    }
    return count;
  };

  iterator lower_bound(const key_type &key) {
    std::pair<iterator, iterator> range = equal_range(key);
    if (contains(key)) {
      return range.first;
    } else {
      return nonEqalBound(key);
    }
  };

  iterator upper_bound(const key_type &key) {
    std::pair<iterator, iterator> range = equal_range(key);
    if (contains(key)) {
      return range.second;
    } else {
      return nonEqalBound(key);
    }
  };

 private:
  iterator nonEqalBound(const key_type &key) {
    iterator iter = begin();
    for (; iter != end(); ++iter) {
      if (iter.getPos()->getKey() > key) return iter;
    }
    return iterator{};
  };
};

}  // namespace s21

#endif  // S21_CONTAINERS_MULTISET_H