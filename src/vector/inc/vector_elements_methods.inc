namespace s21 {
template <typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::at(size_type pos) {
  if (pos >= cap_) throw "out_of_range";
  return ptr_[pos];
}
template <typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::operator[](
    size_type pos) {
  return ptr_[pos];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::operator[](
    size_type pos) const {
  return ptr_[pos];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::front() {
  return ptr_[0];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::back() {
  return ptr_[sz_ - 1];
}

template <typename T, typename Alloc>
T *vector<T, Alloc>::data() {
  return ptr_;
}
}  // namespace s21
