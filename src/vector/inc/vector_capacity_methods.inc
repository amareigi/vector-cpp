namespace s21 {
// empty
template <typename T, typename Alloc>
bool vector<T, Alloc>::empty() {
  return !sz_;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::size() {
  return sz_;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::max_size() {
  return (std::numeric_limits<size_t>::max() / sizeof(value_type)) / 2;
}

template <typename T, typename Alloc>
void vector<T, Alloc>::reserve(size_type size) {
  if (size > cap_) {
    value_type *new_ptr = AllocTraits::allocate(alloc_, size);
    size_type i = 0;
    try {
      for (; i < sz_; ++i) {
        AllocTraits::construct(alloc_, new_ptr + i,
                               std::move_if_noexcept(ptr_[i]));
      }
    } catch (...) {
      for (size_type j = 0; j < i; ++j) {
        AllocTraits::destroy(alloc_, new_ptr + j);
      }
      AllocTraits::deallocate(alloc_, new_ptr, size);
      throw;
    }
    for (size_t i = 0; i < sz_; ++i) AllocTraits::destroy(alloc_, ptr_ + i);
    if (ptr_ != nullptr) AllocTraits::deallocate(alloc_, ptr_, cap_);
    ptr_ = new_ptr;
    cap_ = size;
  }
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::capacity() {
  return cap_;
}

template <typename T, typename Alloc>
void vector<T, Alloc>::shrink_to_fit() {
  if (sz_ < cap_) {
    value_type *new_ptr = AllocTraits::allocate(alloc_, sz_);
    size_type i = 0;
    try {
      for (; i < sz_; ++i) {
        AllocTraits::construct(alloc_, new_ptr + i,
                               std::move_if_noexcept(ptr_[i]));
      }
    } catch (...) {
      for (size_type j = 0; j < i; ++j) {
        AllocTraits::destroy(alloc_, new_ptr + j);
      }
      AllocTraits::deallocate(alloc_, new_ptr, sz_);
      throw;
    }
    for (size_t i = 0; i < sz_; ++i) AllocTraits::destroy(alloc_, ptr_ + i);
    if (ptr_ != nullptr) AllocTraits::deallocate(alloc_, ptr_, cap_);
    ptr_ = new_ptr;
    cap_ = sz_;
  }
}

}  // namespace s21
