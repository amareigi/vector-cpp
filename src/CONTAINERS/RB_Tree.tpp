#ifndef S21_CONTAINERS_RB_TREE_TPP
#define S21_CONTAINERS_RB_TREE_TPP

#include "RB_Tree.h"

namespace s21 {

/*               CONSTRUCTORS AND DESTRUCTOR                  */

template <typename key_type, typename value_type, bool multi>
RB_Tree<key_type, value_type, multi>::RB_Tree() : _root{nullptr}, _size{} {};

template <typename key_type, typename value_type, bool multi>
RB_Tree<key_type, value_type, multi>::RB_Tree(
    const RB_Tree<key_type, value_type, multi> &other) {
  copy(other);
};

template <typename key_type, typename value_type, bool multi>
RB_Tree<key_type, value_type, multi>::RB_Tree(
    RB_Tree<key_type, value_type, multi> &&other)
    : _root(other._root), _size(other._size) {
  other._root = nullptr;
  other._root = 0;
};

template <typename key_type, typename value_type, bool multi>
RB_Tree<key_type, value_type, multi>::~RB_Tree() {
  clearTree();
};

/*               NODE METHODS                                 */

template <typename key_type, typename value_type, bool multi>
const typename RB_Tree<key_type, value_type, multi>::key_type &
RB_Tree<key_type, value_type, multi>::node::getKey() {
  return key;
};

template <typename key_type, typename value_type, bool multi>
const typename RB_Tree<key_type, value_type, multi>::value_type &
RB_Tree<key_type, value_type, multi>::node::getValue() {
  return value;
};

template <typename key_type, typename value_type, bool multi>
typename RB_Tree<key_type, value_type, multi>::value_type &
RB_Tree<key_type, value_type, multi>::node::getValueNonConst() {
  return value;
};

template <typename key_type, typename value_type, bool multi>
void RB_Tree<key_type, value_type, multi>::node::setLeft(node_t *node) {
  this->left = node;
  if (node) node->parent = this;
}

template <typename key_type, typename value_type, bool multi>
void RB_Tree<key_type, value_type, multi>::node::setRight(node_t *node) {
  this->right = node;
  if (node) node->parent = this;
}

template <typename key_type, typename value_type, bool multi>
void RB_Tree<key_type, value_type, multi>::node::swapValues(node_t *node) {
  node_color tmpColor = color;
  color = node->color;
  node->color = tmpColor;

  node_t *tmpNode = left;
  setLeft(node->left);
  node->setLeft(tmpNode);

  tmpNode = right;
  setRight(node->right);
  node->setRight(tmpNode);

  if (parent) {
    if (parent->left == this)
      parent->left->left = node;
    else
      parent->right = node;
  }

  if (node->parent) {
    if (node->parent->left == node)
      node->parent->left = this;
    else
      node->parent->right = this;
  }

  tmpNode = parent;
  parent = node->parent;
  node->parent = tmpNode;
};

template <typename key_type, typename value_type, bool multi>
typename RB_Tree<key_type, value_type, multi>::node_t *
RB_Tree<key_type, value_type, multi>::node::grandparent() {
  return (this->parent) ? (this->parent->parent) : nullptr;
};

template <typename key_type, typename value_type, bool multi>
typename RB_Tree<key_type, value_type, multi>::node_t *
RB_Tree<key_type, value_type, multi>::node::uncle() {
  node_t *gp = this->grandparent();
  if (!gp) return nullptr;
  return (this->parent == gp->left) ? gp->right : gp->left;
};

template <typename key_type, typename value_type, bool multi>
typename RB_Tree<key_type, value_type, multi>::node_t *
RB_Tree<key_type, value_type, multi>::node::sibling() {
  return (this == this->parent->left) ? this->parent->right
                                      : this->parent->left;
};

/*               RB_TREE METHODS                              */

template <typename key_type, typename value_type, bool multi>
void RB_Tree<key_type, value_type, multi>::clearTree() {
  if (_root != nullptr) {
    clearSubTree(_root);
    _root = nullptr;
  }
  _size = 0;
};

template <typename key_type, typename value_type, bool multi>
void RB_Tree<key_type, value_type, multi>::clearSubTree(node_t *node) {
  if (node->left != nullptr) clearSubTree(node->left);
  if (node->right != nullptr) clearSubTree(node->right);
  delete node;
};

template <typename key_type, typename value_type, bool multi>
void RB_Tree<key_type, value_type, multi>::move(RB_Tree &&other) {
  _root = other._root;
  _size = other._size;
  other._root = nullptr;
  other._size = 0;
};

template <typename key_type, typename value_type, bool multi>
void RB_Tree<key_type, value_type, multi>::copy(const RB_Tree &other) {
  _root = nullptr;
  clearTree();
  if (other._root) {
    _root = new node_t(*other._root);
    if (!_root) throw std::runtime_error("Bad allocation");
    copyChild(other._root, _root);
  }
  _size = other._size;
};

template <typename key_type, typename value_type, bool multi>
void RB_Tree<key_type, value_type, multi>::copyChild(node_t *from, node_t *to) {
  if (from->left) {
    node_t *lNode = new node_t(*from->left);
    if (!lNode) throw std::runtime_error("Bad allocation");
    to->setLeft(lNode);
    copyChild(from->left, lNode);
  }
  if (from->right) {
    node_t *rNode = new node_t(*from->right);
    if (!rNode) throw std::runtime_error("Bad allocation");
    to->setRight(rNode);
    copyChild(from->right, rNode);
  }
};

template <typename key_type, typename value_type, bool multi>
void RB_Tree<key_type, value_type, multi>::rotate(node_t *node, direction dir) {
  node_t *pivot = (dir == LEFT) ? node->right : node->left;

  pivot->parent = node->parent;
  if (node->parent) {
    if (node->parent->left == node)
      node->parent->left = pivot;
    else
      node->parent->right = pivot;
  }
  if (dir == LEFT) {
    node->right = pivot->left;
    if (pivot->left) pivot->left->parent = node;
    pivot->left = node;
  } else {
    node->left = pivot->right;
    if (pivot->right) pivot->right->parent = node;
    pivot->right = node;
  }
  node->parent = pivot;
};

template <typename key_type, typename value_type, bool multi>
int RB_Tree<key_type, value_type, multi>::compareKeys(const key_type &key_1,
                                                      const key_type &key_2) {
  if (key_1 < key_2) {
    return -1;
  } else if (key_1 == key_2) {
    return 0;
  } else {
    return 1;
  }
};

template <typename key_type, typename value_type, bool multi>
typename RB_Tree<key_type, value_type, multi>::node *
RB_Tree<key_type, value_type, multi>::findNode(const key_type &key) {
  node_t *current = _root;

  while (current != nullptr) {
    int compare = compareKeys(key, current->getKey());
    if (!compare) return current;
    current = (compare < 0) ? current->left : current->right;
  };
  return nullptr;
};

template <typename key_type, typename value_type, bool multi>
bool RB_Tree<key_type, value_type, multi>::contains(const key_type &key) {
  return findNode(key) ? true : false;
};

template <typename key_type, typename value_type, bool multi>
void RB_Tree<key_type, value_type, multi>::swap(RB_Tree &other) {
  node_t *tmp = other._root;
  size_type sizeTemp = other._size;

  other._root = _root;
  _root = tmp;

  other._size = _size;
  _size = sizeTemp;
};

template <typename key_type, typename value_type, bool multi>
void RB_Tree<key_type, value_type, multi>::merge(RB_Tree &other) {
  for (constTreeIterator iter = other.cbegin(); iter != other.cend(); ++iter) {
    key_type key = iter.getPos()->getKey();
    value_type value = iter.getPos()->getValue();

    node_t *node = new node_t(nullptr, nullptr, nullptr, RED, key, value);

    if (!node) throw std::runtime_error("Bad allocation");

    bool isSuccess = insertNode(node);

    if (!isSuccess) delete node;
  }
};

template <typename key_type, typename value_type, bool multi>
typename RB_Tree<key_type, value_type, multi>::node_t *
RB_Tree<key_type, value_type, multi>::minNode(node_t *node) {
  node_t *current = node;
  while (current->left) {
    current = current->left;
  }
  return current;
};

template <typename key_type, typename value_type, bool multi>
typename RB_Tree<key_type, value_type, multi>::node_t *
RB_Tree<key_type, value_type, multi>::maxNode(node_t *node) {
  node_t *current = node;
  while (current->right) {
    current = current->right;
  }
  return current;
};

template <typename key_type, typename value_type, bool multi>
std::pair<typename RB_Tree<key_type, value_type, multi>::treeIterator, bool>
RB_Tree<key_type, value_type, multi>::insertData(key_type key,
                                                 value_type value) {
  node_t *node = nullptr;
  bool isCorrectInsert = false;

  if (!multi) node = findNode(key);

  if (!node) {
    node = new node_t(nullptr, nullptr, nullptr, RED, key, value);
    if (!node) throw std::runtime_error("Bad allocation");
    isCorrectInsert = insertNode(node);
  }
  return {treeIterator(node, _root), isCorrectInsert};
};

template <typename key_type, typename value_type, bool multi>
bool RB_Tree<key_type, value_type, multi>::insertNode(node_t *node) {
  if (_root == nullptr) {
    node->color = BLACK;
    _root = node;
  } else {
    int compare{};
    node_t *nextNode = nullptr;
    node_t *parentNode = _root;

    do {
      compare = compareKeys(node->getKey(), parentNode->getKey());
      if (compare == 0 && !multi) return false;

      if (compare < 0) {
        nextNode = parentNode->left;
      } else {
        nextNode = parentNode->right;
      }
      if (nextNode != nullptr) {
        parentNode = nextNode;
      }
    } while (nextNode != nullptr);

    if (compare < 0) {
      parentNode->left = node;
    } else {
      parentNode->right = node;
    }
    node->parent = parentNode;
    insertCase1(node);
  };
  _size += 1;
  return true;
};

template <typename key_type, typename value_type, bool multi>
void RB_Tree<key_type, value_type, multi>::insertCase1(node_t *node) {
  if (node->parent == nullptr || node->parent->color == BLACK)
    return;
  else
    insertCase2(node);
};

template <typename key_type, typename value_type, bool multi>
void RB_Tree<key_type, value_type, multi>::insertCase2(node_t *node) {
  node_t *uncleN = node->uncle();

  if ((uncleN != nullptr) && (uncleN->color == RED)) {
    node_t *gpa = node->grandparent();
    node->parent->color = BLACK;
    uncleN->color = BLACK;
    gpa->color = gpa->parent ? RED : BLACK;
    insertCase1(gpa);
  } else {
    insertCase3(node);
  }
};

template <typename key_type, typename value_type, bool multi>
void RB_Tree<key_type, value_type, multi>::insertCase3(node_t *node) {
  node_t *gpa = node->grandparent();

  if ((node == node->parent->right) && (node->parent == gpa->left)) {
    rotate(node->parent, LEFT);
    node = node->left;

  } else if ((node == node->parent->left) && (node->parent == gpa->right)) {
    rotate(node->parent, RIGHT);
    node = node->right;
  }
  insertCase4(node);
};

template <typename key_type, typename value_type, bool multi>
void RB_Tree<key_type, value_type, multi>::insertCase4(node_t *node) {
  node_t *gpa = node->grandparent();

  node->parent->color = BLACK;
  gpa->color = RED;
  if ((node == node->parent->left) && (node->parent == gpa->left)) {
    rotate(gpa, RIGHT);
  } else {
    rotate(gpa, LEFT);
  }
  if (node->parent->parent == nullptr) {
    _root = node->parent;
  }
};

template <typename key_type, typename value_type, bool multi>
void RB_Tree<key_type, value_type, multi>::erase(treeIterator pos) {
  node_t *node = pos.getPos();
  if (node) {
    if (!node->parent && !node->right && !node->left) {
      delete node;
      _size = 0;
      _root = nullptr;
    } else {
      deleteNode(node);
    }
    if (_root) {
      node_t *temp = _root;
      while (temp->parent) temp = temp->parent;
      _root = temp;
    }
  } else {
    throw std::runtime_error("Invalid pointer");
  }
};

template <typename key_type, typename value_type, bool multi>
void RB_Tree<key_type, value_type, multi>::deleteNode(node_t *node) {
  node_t *delNode = node;
  if (node->left)
    delNode = maxNode(node->left);
  else if (node->right)
    delNode = minNode(node->right);

  if (delNode != node) {
    delNode->swapValues(node);

    if (delNode->parent == nullptr) {
      _root = delNode;
      _root->color = BLACK;
    }
    delNode = node;
  }
  node_t *child = (delNode->left) ? delNode->left : delNode->right;
  if (delNode->color == BLACK) {
    if (child == nullptr) {
      deleteCase1(delNode);
    } else {
      child->parent = delNode->parent;

      if (delNode->parent->left == delNode) {
        delNode->parent->left = child;
      } else {
        delNode->parent->right = child;
      }

      if (child->color == RED) {
        child->color = BLACK;
      } else {
        deleteCase1(child);
      }
    }
  }
  if (delNode->parent) {
    if (delNode->parent->left == delNode)
      delNode->parent->left = nullptr;
    else if (delNode->parent->right == delNode)
      delNode->parent->right = nullptr;
    delNode->parent = nullptr;
  }
  if (delNode == _root) _root = nullptr;
  _size -= 1;

  if (delNode) delete delNode;
};

template <typename key_type, typename value_type, bool multi>
void RB_Tree<key_type, value_type, multi>::deleteCase1(node_t *node) {
  if (node->parent) {
    node_t *bro = node->sibling();

    if (bro && bro->color == RED) {
      node->parent->color = RED;
      bro->color = BLACK;
      if (node == node->parent->left)
        rotate(node->parent, LEFT);
      else
        rotate(node->parent, RIGHT);
    }
    deleteCase2(node);
  }
};

template <typename key_type, typename value_type, bool multi>
void RB_Tree<key_type, value_type, multi>::deleteCase2(node_t *node) {
  node_t *bro = node->sibling();

  if (bro && (node->parent->color == BLACK) && (bro->color == BLACK) &&
      (bro->left == nullptr || bro->left->color == BLACK) &&
      (bro->right == nullptr || bro->right->color == BLACK)) {
    bro->color = RED;
    deleteCase1(node->parent);
  } else
    deleteCase3(node);
};

template <typename key_type, typename value_type, bool multi>
void RB_Tree<key_type, value_type, multi>::deleteCase3(node_t *node) {
  node_t *bro = node->sibling();

  if (bro && (node->parent->color == RED) && (bro->color == BLACK) &&
      (bro->left == nullptr || bro->left->color == BLACK) &&
      (bro->right == nullptr || bro->right->color == BLACK)) {
    bro->color = RED;
    node->parent->color = BLACK;
  } else
    deleteCase4(node);
};

template <typename key_type, typename value_type, bool multi>
void RB_Tree<key_type, value_type, multi>::deleteCase4(node_t *node) {
  node_t *bro = node->sibling();

  if (bro && bro->color == BLACK) {
    if ((node == node->parent->left) &&
        (bro->right == nullptr || bro->right->color == BLACK) &&
        (bro->left != nullptr && bro->left->color == RED)) {
      bro->color = RED;
      bro->left->color = BLACK;
      rotate(bro, RIGHT);

    } else if ((node == node->parent->right) &&
               (bro->left == nullptr || bro->left->color == BLACK) &&
               (bro->right != nullptr && bro->right->color == RED)) {
      bro->color = RED;
      bro->right->color = BLACK;
      rotate(bro, LEFT);
    }
  }
  deleteCase5(node);
};

template <typename key_type, typename value_type, bool multi>
void RB_Tree<key_type, value_type, multi>::deleteCase5(node_t *node) {
  node_t *bro = node->sibling();

  if (bro) bro->color = node->parent->color;
  node->parent->color = BLACK;

  if (node == node->parent->left) {
    if (bro && bro->right) bro->right->color = BLACK;
    rotate(node->parent, LEFT);
  } else {
    if (bro && bro->left) bro->left->color = BLACK;
    rotate(node->parent, RIGHT);
  }
};

template <typename key_type, typename value_type, bool multi>
bool RB_Tree<key_type, value_type, multi>::empty() {
  return _root ? false : true;
};

template <typename key_type, typename value_type, bool multi>
typename RB_Tree<key_type, value_type, multi>::size_type
RB_Tree<key_type, value_type, multi>::size() {
  return _size;
};

template <typename key_type, typename value_type, bool multi>
typename RB_Tree<key_type, value_type, multi>::size_type
RB_Tree<key_type, value_type, multi>::max_size() {
  return __LONG_MAX__ / sizeof(node_t);
};

template <typename key_type, typename value_type, bool multi>
typename RB_Tree<key_type, value_type, multi>::treeIterator
RB_Tree<key_type, value_type, multi>::begin() {
  return treeIterator(minNode(_root), _root);
};

template <typename key_type, typename value_type, bool multi>
typename RB_Tree<key_type, value_type, multi>::treeIterator
RB_Tree<key_type, value_type, multi>::end() {
  return treeIterator(nullptr, _root);
};

template <typename key_type, typename value_type, bool multi>
typename RB_Tree<key_type, value_type, multi>::constTreeIterator
RB_Tree<key_type, value_type, multi>::cbegin() {
  return constTreeIterator(minNode(_root), _root);
};

template <typename key_type, typename value_type, bool multi>
typename RB_Tree<key_type, value_type, multi>::constTreeIterator
RB_Tree<key_type, value_type, multi>::cend() {
  return constTreeIterator(nullptr, _root);
};

/*               treeIterator METHODS                        */

template <typename key_type, typename value_type, bool multi>
typename RB_Tree<key_type, value_type, multi>::reference
RB_Tree<key_type, value_type, multi>::treeIterator::operator*() const {
  if (_current) {
    return const_cast<key_type &>(_current->getValue());
  } else {
    static value_type default_value{};
    return default_value;
  }
};

template <typename key_type, typename value_type, bool multi>
typename RB_Tree<key_type, value_type, multi>::treeIterator &
RB_Tree<key_type, value_type, multi>::treeIterator::operator++() {
  if (_current) {
    if (_current->right) {
      _current = minNode(_current->right);
    } else {
      node_t *parent = nullptr;
      while ((parent = _current->parent) && _current == parent->right) {
        _current = parent;
      }
      _current = parent;
    }
  }
  return *this;
};

template <typename key_type, typename value_type, bool multi>
typename RB_Tree<key_type, value_type, multi>::treeIterator &
RB_Tree<key_type, value_type, multi>::treeIterator::operator--() {
  if (_current) {
    if (_current->left) {
      _current = maxNode(_current->left);

    } else {
      node_t *parent = nullptr;
      while ((parent = _current->parent) && _current == parent->left) {
        _current = parent;
      }
      _current = parent;
    }
  } else {
    _current = maxNode(_it_root);
  }
  return *this;
};

template <typename key_type, typename value_type, bool multi>
bool RB_Tree<key_type, value_type, multi>::treeIterator::operator==(
    const treeIterator &other) const {
  return other._current == _current;
};

template <typename key_type, typename value_type, bool multi>
bool RB_Tree<key_type, value_type, multi>::treeIterator::operator!=(
    const treeIterator &other) const {
  return !(other._current == _current);
};

/*               constTreeIterator METHODS                    */

template <typename key_type, typename value_type, bool multi>
typename RB_Tree<key_type, value_type, multi>::const_reference
RB_Tree<key_type, value_type, multi>::constTreeIterator::operator*() const {
  if (this->_current) {
    return this->_current->getKey();
  } else {
    static value_type default_value{};
    return default_value;
  }
};

template <typename key_type, typename value_type, bool multi>
typename RB_Tree<key_type, value_type, multi>::constTreeIterator &
RB_Tree<key_type, value_type, multi>::constTreeIterator::operator++() {
  parent_t::operator++();
  return *this;
};

template <typename key_type, typename value_type, bool multi>
typename RB_Tree<key_type, value_type, multi>::constTreeIterator &
RB_Tree<key_type, value_type, multi>::constTreeIterator::operator--() {
  parent_t::operator--();
  return *this;
};

template <typename key_type, typename value_type, bool multi>
bool RB_Tree<key_type, value_type, multi>::constTreeIterator::operator==(
    const constTreeIterator &other) const {
  return other._current == this->_current;
};

template <typename key_type, typename value_type, bool multi>
bool RB_Tree<key_type, value_type, multi>::constTreeIterator::operator!=(
    const constTreeIterator &other) const {
  return !(other._current == this->_current);
};

template <typename key_type, typename value_type, bool multi>
typename RB_Tree<key_type, value_type, multi>::node *
RB_Tree<key_type, value_type, multi>::treeIterator::getPos() {
  return _current;
};

}  // namespace s21

#endif  // S21_CONTAINERS_RB_TREE_TPP