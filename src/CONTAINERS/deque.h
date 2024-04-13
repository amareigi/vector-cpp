#ifndef S21_CONTAINERS_DEQUE_H
#define S21_CONTAINERS_DEQUE_H

namespace s21 {

template <typename T>
class deque {
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

 protected:
  struct Node {
    T data;
    Node* next;
    Node() : next(nullptr){};
    ~Node(){};
  };

  Node* _node;
  size_type _size;

 public:
  deque();
  deque(const deque& s);
  deque(deque&& s);
  ~deque() noexcept;
  deque& operator=(deque&& s);
  deque& operator=(const deque& s);

  bool empty();
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(deque& other);
  void pushBack(const_reference value);

  void print();
};

template <typename value_type>
deque<value_type>::deque() : _node(nullptr), _size(0){};

template <typename value_type>
deque<value_type>::deque(const deque& s) : _node(nullptr), _size(0) {
  Node* temp = s._node;
  while (temp) {
    this->pushBack(temp->data);
    temp = temp->next;
  }
};

template <typename value_type>
deque<value_type>::deque(deque&& s) : _node(s._node), _size(s._size) {
  s._node = nullptr;
  s._size = 0;
};

template <typename value_type>
deque<value_type>::~deque() noexcept {
  while (_node) {
    Node* temp = _node->next;
    delete _node;
    _node = temp;
  };
};

template <typename value_type>
typename deque<value_type>::deque& deque<value_type>::operator=(deque&& s) {
  if (s._node != _node) {
    _node = s._node;
    _node->next = s._node->next;
    _size = s._size;
    s._size = 0;
    s._node = nullptr;
  }
  return *this;
};

template <typename value_type>
typename deque<value_type>::deque& deque<value_type>::operator=(
    const deque& s) {
  if (s._node != _node) {
    while (!this->empty()) this->pop();
    Node* temp = s._node;
    while (temp) {
      this->pushBack(temp->data);
      temp = temp->next;
    }
    _size = s._size;
  }
  return *this;
};

template <typename value_type>
void deque<value_type>::push(const_reference value) {
  Node* temp = _node;
  _node = new Node;
  if (!_node) throw std::runtime_error("Bad allocation");
  _node->data = value;
  _node->next = temp;
  _size++;
};

template <typename value_type>
void deque<value_type>::pushBack(const_reference value) {
  Node* temp = _node;
  if (!temp) {
    _node = new Node;
    if (!_node) throw std::runtime_error("Bad allocation");
    _node->next = nullptr;
    _node->data = value;
  } else {
    while (temp->next) temp = temp->next;
    temp->next = new Node;
    if (!temp->next) throw std::runtime_error("Bad allocation");
    temp->next->data = value;
    temp->next->next = nullptr;
  }
  _size++;
};

template <typename value_type>
void deque<value_type>::pop() {
  if (_size > 0) {
    Node* temp = _node;
    if (_node->next) {
      _node = _node->next;
    }
    _size--;
    delete temp;
  }
};

template <typename value_type>
bool deque<value_type>::empty() {
  return (_size ? false : true);
};

template <typename value_type>
typename deque<value_type>::size_type deque<value_type>::size() {
  return _size;
};

template <typename value_type>
void deque<value_type>::swap(deque& other) {
  std::swap(*this, other);
};

template <typename value_type>
void deque<value_type>::print() {
  if (_node) {
    Node* temp = _node;
    while (temp) {
      std::cout << temp->data << " | ";
      temp = temp->next;
    }
    std::cout << std::endl;
  };
}

}  // namespace s21

#endif  // S21_CONTAINERS_DEQUE_H