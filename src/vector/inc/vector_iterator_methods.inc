namespace s21 {

template <typename T, typename Alloc>
template <bool IsConst>
class vector<T, Alloc>::base_iterator {
 public:
  friend class vector;
  using traits = std::iterator_traits<T>;
  using pointer_type = std::conditional_t<IsConst, const T *, T *>;
  using reference_type = std::conditional_t<IsConst, const T &, T &>;
  using difference_type = typename std::ptrdiff_t;
  using value_type = T;

  base_iterator(const base_iterator &) = default;
  base_iterator(base_iterator<false> &other) : iptr_(other.iptr_) {}
  base_iterator &operator=(const base_iterator &) = default;

  reference_type operator*() const { return *iptr_; }
  pointer_type operator->() const { return iptr_; }
  bool operator!=(const base_iterator &other) const {
    return iptr_ != other.iptr_;
  }
  bool operator==(const base_iterator &other) const {
    return iptr_ == other.iptr_;
  }

  base_iterator operator+(size_type n) const { return {iptr_ + n}; }
  base_iterator operator-(size_type n) const { return {iptr_ - n}; }
  size_type operator-(const base_iterator &other) const {
    return iptr_ - other.iptr_;
  }

  base_iterator &operator++() {
    ++iptr_;
    return *this;
  }
  base_iterator operator++(int) {
    base_iterator copy = *this;
    ++iptr_;
    return copy;
  }
  base_iterator &operator--() {
    --iptr_;
    return *this;
  }
  base_iterator operator--(int) {
    base_iterator copy = *this;
    --iptr_;
    return copy;
  }

 private:
  pointer_type iptr_;
  base_iterator(T *ptr) : iptr_(ptr) {}
};

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::begin() {
  return {ptr_};
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::end() {
  return {ptr_ + sz_};
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::begin() const {
  return {ptr_};
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::end() const {
  return {ptr_ + sz_};
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::cbegin() const {
  return const_iterator{ptr_};
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::cend() const {
  return {ptr_ + sz_};
}

}  // namespace s21
