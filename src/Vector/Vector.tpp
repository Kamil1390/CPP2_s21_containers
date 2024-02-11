#include "vector.h"

namespace s21 {

template <class T> vector<T>::vector() { zero_vector(); }

template <class T> vector<T>::vector(size_t n) { memory_allocation(n); }

template <class T> vector<T>::vector(std::initializer_list<T> const &items) {
  memory_allocation(items.size());
  std::copy(items.begin(), items.end(), vector_);
}

template <class T> vector<T>::vector(const vector &v) {
  memory_allocation(v.size_);
  std::copy(v.vector_, v.vector_ + v.size_, vector_);
}

template <class T>
vector<T>::vector(vector &&v) noexcept
    : vector_(v.vector_), size_(v.size_), capacity_(v.capacity_) {
  v.zero_vector();
}

template <class T> vector<T>::~vector() {
  delete[] vector_;
  zero_vector();
}

template <class T> vector<T> &vector<T>::operator=(vector &&v) noexcept {
  if (this != &v) {
    delete[] vector_;
    size_ = v.size_;
    capacity_ = v.capacity_;
    vector_ = v.vector_;
    v.zero_vector();
  }
  return *this;
}

template <class T> vector<T> &vector<T>::operator=(const vector &v) {
  if (this != &v) {
    delete[] vector_;
    vector_ = new T[v.capacity_];
    std::copy(v.vector_, v.vector_ + v.size_, vector_);
    size_ = v.size_;
    capacity_ = v.capacity_;
  }
  return *this;
}

template <class T> typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("range check pos >= size_");
  }
  return vector_[pos];
}

template <class T>
typename vector<T>::const_reference vector<T>::at(size_type pos) const {
  if (pos >= size_) {
    throw std::out_of_range("range check pos >= size_");
  }
  return vector_[pos];
}

template <class T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return vector_[pos];
}

template <class T>
typename vector<T>::const_reference vector<T>::operator[](size_type pos) const {
  return vector_[pos];
}

template <class T>
typename vector<T>::const_reference vector<T>::front() const {
  return vector_[0];
}

template <class T> typename vector<T>::const_reference vector<T>::back() const {
  return vector_[size_ - 1];
}

template <class T> typename vector<T>::iterator vector<T>::data() {
  return vector_;
}

template <class T> typename vector<T>::iterator vector<T>::begin() const {
  return vector_;
}

template <class T> typename vector<T>::iterator vector<T>::end() const {
  return vector_ + size_;
}

template <class T> bool vector<T>::empty() const { return size_ == 0; }
template <class T> size_t vector<T>::size() const { return size_; }
template <class T> size_t vector<T>::max_size() const {
  return std::min<size_type>(std::allocator<T>().max_size(),
                             std::numeric_limits<difference_type>::max());
}
template <class T> void vector<T>::reserve(size_type size) {
  if (size > capacity_) {
    change_capacity(size);
  }
}
template <class T> size_t vector<T>::capacity() const { return capacity_; }

template <class T> void vector<T>::shrink_to_fit() {
  if (capacity_ > size_) {
    change_capacity(size_);
  }
}

template <class T> void vector<T>::clear() {
  size_ = 0;
  delete[] vector_;
  vector_ = nullptr;
}

template <class T>
typename vector<T>::iterator vector<T>::insert(const_iterator pos,
                                               const_reference value) {
  if (pos < begin() || pos > end()) {
    throw std::out_of_range("range check pos >= size_");
  }
  size_t position = pos - begin();
  push_back(value);
  for (size_t i = size_ - 1; i > position; i--) {
    std::swap(vector_[i], vector_[i - 1]);
  }
  return vector_ + position;
}

template <class T> void vector<T>::erase(iterator pos) {
  if (pos < begin() || pos > end()) {
    throw std::out_of_range("range check pos >= size_");
  }
  size_t position = pos - begin();
  for (size_t i = position; i < size_ - 1; i++) {
    std::swap(vector_[i], vector_[i + 1]);
  }
  size_ -= 1;
}

template <class T> void vector<T>::push_back(const_reference value) {
  if (size_ + 1 > capacity_) {
    reserve(size_ * 2);
  }
  vector_[size_] = value;
  size_ += 1;
}

template <class T> void vector<T>::pop_back() {
  size_ = size_ > 0 ? size_ - 1 : 0;
}

template <class T> void vector<T>::swap(vector &other) {
  if (this != &other) {
    std::swap(vector_, other.vector_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }
}

template <class T>
template <class... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  size_t position = pos - begin();
  for (auto i : {args...}) {
    insert(begin() + position, i);
    position++;
  }
  return begin() + position;
}

template <class T>
template <class... Args>
void vector<T>::insert_many_back(Args &&...args) {
  for (auto i : {args...}) {
    push_back(i);
  }
}

template <class T> void vector<T>::zero_vector() {
  vector_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <class T> void vector<T>::memory_allocation(size_t n) {
  size_ = n;
  capacity_ = size_;
  vector_ = new T[size_]{};
}

template <class T> void vector<T>::change_capacity(size_t n) {
  T *tmp_vector = new T[n];
  std::copy(vector_, end(), tmp_vector);
  delete[] vector_;
  vector_ = tmp_vector;
  capacity_ = n;
}

} // namespace s21