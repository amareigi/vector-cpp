namespace s21 {

// default
template <typename T, typename Alloc>
vector<T, Alloc>::vector(const Alloc &alloc)
    : alloc_(alloc), sz_(0), cap_(0), ptr_(nullptr) {}

// params
template <typename T, typename Alloc>
vector<T, Alloc>::vector(size_type n, const_reference value, const Alloc &alloc)
    : vector(alloc) {
  reserve(n);
  for (size_type i = 0; i < n; ++i) {
    AllocTraits::construct(alloc_, ptr_ + i, value);
    ++sz_;
  }
}

// init_list
template <typename T, typename Alloc>
vector<T, Alloc>::vector(std::initializer_list<T> const &items,
                         const Alloc &alloc)
    : vector(alloc) {
  reserve(items.size());
  int j = 0;
  for (auto it = items.begin(); it != items.end(); ++it, ++j) {
    AllocTraits::construct(alloc_, ptr_ + j, *it);
    ++sz_;
  }
}

// copy
template <typename T, typename Alloc>
vector<T, Alloc>::vector(const vector &v)
    : vector(AllocTraits::select_on_container_copy_construction(v.alloc_)) {
  reserve(v.sz_);
  for (size_type i = 0; i < v.sz_; ++i) {
    AllocTraits::construct(alloc_, ptr_ + i, v[i]);
    ++sz_;
  }
}

// move
template <typename T, typename Alloc>
vector<T, Alloc>::vector(vector &&v, const Alloc &alloc) : vector(alloc) {
  if (alloc_ == v.alloc_) {
    sz_ = v.sz_;
    cap_ = v.cap_;
    ptr_ = v.ptr_;
  } else {
    reserve(v.cap_);
    for (size_type i = 0; i < v.sz_; ++i) {
      AllocTraits::construct(alloc_, ptr_ + i,
                             std::move_if_noexcept(v.ptr_[i]));
      ++sz_;
    }
    v.~vector();
  }
  v.sz_ = 0;
  v.cap_ = 0;
  v.ptr_ = nullptr;
}

// copy assignment
template <typename T, typename Alloc>
vector<T, Alloc> &vector<T, Alloc>::operator=(const vector &v) {
  if (&v != this) {
    for (size_t i = 0; i < sz_; ++i) AllocTraits::destroy(alloc_, ptr_ + i);
    sz_ = 0;
    if (AllocTraits::propagate_on_container_copy_assignment::value) {
      alloc_ = v.alloc_;
    }
    reserve(v.sz_);
    for (size_type i = 0; i < v.sz_; ++i) {
      AllocTraits::construct(alloc_, ptr_ + i, v[i]);
      ++sz_;
    }
  }
  return *this;
}

// move assignment
template <typename T, typename Alloc>
vector<T, Alloc> &vector<T, Alloc>::operator=(vector &&v) {
  if (&v != this) {
    this->~vector();
    if (AllocTraits::propagate_on_container_move_assignment::value) {
      alloc_ = v.alloc_;
      sz_ = v.sz_;
      cap_ = v.cap_;
      ptr_ = v.ptr_;
    } else if (alloc_ == v.alloc_) {
      sz_ = v.sz_;
      cap_ = v.cap_;
      ptr_ = v.ptr_;
    } else {
      reserve(v.cap_);
      for (size_type i = 0; i < v.sz_; ++i) {
        AllocTraits::construct(alloc_, ptr_ + i,
                               std::move_if_noexcept(v.ptr_[i]));
        ++sz_;
      }
      v.~vector();
    }
    v.sz_ = 0;
    v.cap_ = 0;
    v.ptr_ = nullptr;
  }
  return *this;
}

template <typename T, typename Alloc>
vector<T, Alloc>::~vector() {
  for (size_t i = 0; i < sz_; ++i) AllocTraits::destroy(alloc_, ptr_ + i);
  if (ptr_ != nullptr) AllocTraits::deallocate(alloc_, ptr_, cap_);
  sz_ = 0;
  cap_ = 0;
  ptr_ = nullptr;
}
}  // namespace s21
