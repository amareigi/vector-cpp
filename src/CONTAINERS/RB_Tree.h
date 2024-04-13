#ifndef S21_CONTAINERS_RB_TREE_H
#define S21_CONTAINERS_RB_TREE_H

#include <utility>

#include "s21_vector.h"

namespace s21 {

template <typename Key, typename T, bool multi>
class RB_Tree {
 public:
  using key_type = Key;
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;

  class node;
  class treeIterator;
  class constTreeIterator;

  using node_t = node;

 private:
  node *_root;
  size_type _size;

 public:
  RB_Tree();
  RB_Tree(const RB_Tree &other);
  RB_Tree(RB_Tree &&other);
  virtual ~RB_Tree();

  bool empty();
  void erase(treeIterator pos);

  void swap(RB_Tree &other);
  void merge(RB_Tree &other);
  bool contains(const key_type &key);

 protected:
  size_type size();
  size_type max_size();

  treeIterator begin();
  treeIterator end();
  constTreeIterator cbegin();
  constTreeIterator cend();

  enum node_color { RED, BLACK };
  enum direction { LEFT, RIGHT };

  void copy(const RB_Tree &other);
  void move(RB_Tree &&other);

  void clearTree();
  bool insertNode(node_t *node);
  node_t *findNode(const key_type &key);
  std::pair<treeIterator, bool> insertData(key_type key, value_type value);

 private:
  static node_t *minNode(node_t *node);
  static node_t *maxNode(node_t *node);

  static int compareKeys(const key_type &key_1, const key_type &key_2);
  void clearSubTree(node_t *node);
  void copyChild(node_t *from, node_t *to);

  void rotate(node_t *n, direction dir);

  void deleteNode(node_t *node);

  void insertCase1(node_t *node);
  void insertCase2(node_t *node);
  void insertCase3(node_t *node);
  void insertCase4(node_t *node);

  void deleteCase1(node_t *node);
  void deleteCase2(node_t *node);
  void deleteCase3(node_t *node);
  void deleteCase4(node_t *node);
  void deleteCase5(node_t *node);
};

/*               node                                         */

template <typename key_type, typename value_type, bool multi>
class RB_Tree<key_type, value_type, multi>::node {
 public:
  node_t *parent, *left, *right;
  node_color color;

 private:
  key_type key;
  value_type value;

 public:
  node() : parent(nullptr), left{nullptr}, right{nullptr} {};
  node(node_t *p, node_t *l, node_t *r, node_color c, const key_type &k,
       const value_type &v)
      : parent(p), left{l}, right{r}, color(c), key(k), value(v){};

  explicit node(const node_t &other)
      : parent(other.parent),
        left{other.left},
        right{other.right},
        color(other.color),
        key(other.key),
        value(other.value){};

  const key_type &getKey();
  const value_type &getValue();
  value_type &getValueNonConst();

  void swapValues(node_t *node);
  void setLeft(node_t *node);
  void setRight(node_t *node);

  node_t *grandparent();
  node_t *uncle();
  node_t *sibling();
};

/*               iterator                                     */

template <typename key_type, typename value_type, bool multi>
class RB_Tree<key_type, value_type, multi>::treeIterator {
 protected:
  node_t *_current;
  node_t *_it_root;

 public:
  using iterator = treeIterator;

  treeIterator() : _current{nullptr}, _it_root{nullptr} {};
  treeIterator(node_t *current, node_t *root)
      : _current{current}, _it_root{root} {};
  virtual ~treeIterator(){};

  reference operator*() const;
  iterator &operator++();
  iterator &operator--();

  bool operator==(const iterator &other) const;
  bool operator!=(const iterator &other) const;

  node_t *getPos();
};

/*               const iterator                               */

template <typename key_type, typename value_type, bool multi>
class RB_Tree<key_type, value_type, multi>::constTreeIterator
    : public treeIterator {
 public:
  using parent_t = RB_Tree<key_type, value_type, multi>::treeIterator;
  using const_iterator = constTreeIterator;

  constTreeIterator() : parent_t(){};
  constTreeIterator(node_t *node, node_t *root) : parent_t(node, root){};

  node_t *getPos() { return parent_t::getPos(); };

  const_iterator &operator++();
  const_iterator &operator--();

  bool operator==(const const_iterator &other) const;
  bool operator!=(const const_iterator &other) const;

 protected:
  const_reference operator*() const;
};

}  // namespace s21

#include "RB_Tree.tpp"

#endif  // S21_CONTAINERS_RB_TREE_H