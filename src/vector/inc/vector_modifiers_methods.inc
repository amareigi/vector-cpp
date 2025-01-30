namespace s21 {
template <typename T, typename Alloc>
void vector<T, Alloc>::clear() {
  for (size_t i = 0; i < sz_; ++i) AllocTraits::destroy(alloc_, ptr_ + i);
  sz_ = 0;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(
    const_iterator pos, const_reference value) {
  size_type index = pos - cbegin();
  bool pos_is_not_iter_to_end = pos != cend();
  if (sz_ == cap_) {
    reserve(cap_ ? cap_ << 1 : 1);
  }
  if (sz_ > 0 && pos_is_not_iter_to_end) {
    value_type_ptr ptr_to_insert_place = ptr_ + index;
    value_type_ptr ptr_to_dst = ptr_ + sz_;
    value_type_ptr ptr_to_src = ptr_ + sz_ - 1;
    for (; ptr_to_dst != ptr_to_insert_place; --ptr_to_dst, --ptr_to_src) {
      *ptr_to_dst = std::move(*ptr_to_src);
    }
  }
  AllocTraits::construct(alloc_, ptr_ + index, value);
  ++sz_;
  return {ptr_ + index};
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(
    const_iterator pos) {
  if (sz_ > 0 && pos == cend()) throw "invalid iterator refers to end";
  size_type index = 0;
  if (sz_ != 0 && pos != cend()) {
    index = pos - cbegin();
    value_type_ptr ptr_to_last = ptr_ + sz_ - 1;
    value_type_ptr ptr_to_dst = ptr_ + index;
    value_type_ptr ptr_to_src = ptr_ + index + 1;
    for (; ptr_to_dst != ptr_to_last; ++ptr_to_dst, ++ptr_to_src) {
      *ptr_to_dst = std::move(*ptr_to_src);
    }
    AllocTraits::destroy(alloc_, ptr_to_last);
    --sz_;
  }
  return {ptr_ + index};
}

template <typename T, typename Alloc>
template <typename... U>
typename vector<T, Alloc>::reference vector<T, Alloc>::emplace_back(
    U &&...value) {
  if (sz_ == cap_) reserve(cap_ ? cap_ << 1 : 1);
  AllocTraits::construct(alloc_, ptr_ + sz_, std::forward<U>(value)...);
  return ptr_[sz_++];
}

template <typename T, typename Alloc>
template <typename U>
void vector<T, Alloc>::push_back(U &&value) {
  if (sz_ == cap_) reserve(cap_ ? cap_ << 1 : 1);
  AllocTraits::construct(alloc_, ptr_ + sz_, std::forward<U>(value));
  ++sz_;
}

template <typename T, typename Alloc>
void vector<T, Alloc>::push_back(const_reference value) {
  if (sz_ == cap_) reserve(cap_ ? cap_ << 1 : 1);
  AllocTraits::construct(alloc_, ptr_ + sz_, value);
  ++sz_;
}

template <typename T, typename Alloc>
void vector<T, Alloc>::pop_back() {
  if (sz_ > 0) {
    --sz_;
    AllocTraits::destroy(alloc_, ptr_ + sz_);
  }
}

template <typename T, typename Alloc>
void vector<T, Alloc>::swap(vector &other) {
  if (AllocTraits::propagate_on_container_swap::value) {
    using std::swap;
    swap(*this, other);
  } else if (alloc_ == other.alloc_) {
    std::swap(ptr_, other.ptr_);
    std::swap(sz_, other.sz_);
    std::swap(cap_, other.cap_);
  } else {
    throw "swap denied";
  }
}
// Insert_many
template <typename T, typename Alloc>
template <typename... Args>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert_many(
    const_iterator pos, Args &&...args) {
  size_type index = pos - begin();
  size_type args_count = sizeof...(Args);
  for (size_type i = sz_ + args_count - 1; i > index + args_count - 1; --i) {
    ptr_[i] = std::move(ptr_[i - args_count]);
  }
  sz_ += args_count;
  return begin() + index;
}

template <typename T, typename Alloc>
template <typename... Args>
void vector<T, Alloc>::insert_many_back(Args &&...args) {
  inset_many(this->end(), std::forward<Args>(args)...);
}

}  // namespace s21
