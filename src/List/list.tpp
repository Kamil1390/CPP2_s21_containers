#include "list.h"

namespace s21 {

template <class value_type>
list<value_type>::list() : head_(nullptr), tail_(nullptr), fict_(nullptr) {
  init_list();
}

template <class value_type>
list<value_type>::list(size_type n)
    : head_(nullptr), tail_(nullptr), fict_(nullptr) {
  init_list();
  for (size_type i = 0; i < n; i++) {
    push_front(value_type());
  }
}

template <class value_type>
list<value_type>::list(std::initializer_list<value_type> const &items)
    : head_(nullptr), tail_(nullptr), fict_(nullptr) {
  for (auto data : items) {
    push_back(data);
  }
}

template <class value_type> list<value_type>::list(const list &l) {
  init_list();
  copy_object(l);
}

template <class value_type> list<value_type>::list(list &&l) noexcept {
  init_list();
  move_object(l);
}

template <class value_type> list<value_type>::~list() {
  clear();
  delete fict_;
}

template <class value_type>
list<value_type> &list<value_type>::operator=(const list &l) {
  if (this != &l) {
    copy_object(l);
  }
  return *this;
}

template <class value_type>
list<value_type> &list<value_type>::operator=(list &&l) noexcept {
  if (this != &l) {
    move_object(l);
  }
  return *this;
}

template <class value_type> void list<value_type>::copy_object(const list &l) {
  clear();
  Node *current = l.tail_;
  int count = l.size_;
  while (count > 0) {
    push_front(current->data_);
    current = current->ptr_prev_;
    count--;
  }
}

template <class value_type> void list<value_type>::move_object(list &l) {
  clear();
  while (l.size_ > 0) {
    push_front(l.tail_->data_);
    l.pop_back();
  }
  l.head_ = l.tail_ = nullptr;
}

template <class value_type>
list<value_type>::Node::Node(value_type data, Node *ptr_next, Node *ptr_prev)
    : data_(data), ptr_next_(ptr_next), ptr_prev_(ptr_prev) {}

template <class value_type>
list<value_type>::ListIterator::ListIterator() : ptr_(nullptr) {}

template <class value_type>
list<value_type>::ListIterator::ListIterator(Node *ptr) : ptr_(ptr) {}

template <class value_type>
list<value_type>::ListIterator::ListIterator(const iterator &other)
    : ptr_(other.ptr_) {}

template <class value_type>
bool list<value_type>::ListIterator::operator==(const iterator &other) const {
  return ptr_ == other.ptr_ ? true : false;
}

template <class value_type>
bool list<value_type>::ListIterator::operator!=(const iterator &other) const {
  return ptr_ != other.ptr_ ? true : false;
}

template <class value_type>
typename list<value_type>::reference
list<value_type>::ListIterator::operator*() {
  return ptr_->data_;
}

template <class value_type>
typename list<value_type>::iterator &
list<value_type>::ListIterator::operator++() {
  if (ptr_ != nullptr) {
    ptr_ = ptr_->ptr_next_;
  }
  return *this;
}

template <class value_type>
typename list<value_type>::iterator
list<value_type>::ListIterator::operator++(int value) {
  (void)value;
  iterator temp(*this);
  if (ptr_ != nullptr) {
    ptr_ = ptr_->ptr_next_;
  }
  return temp;
}

template <class value_type>
typename list<value_type>::iterator
list<value_type>::ListIterator::operator+(int value) {
  for (int i = 0; i < value; ++i) {
    ptr_ = ptr_->ptr_next_;
  }
  return *this;
}

template <class value_type>
typename list<value_type>::iterator &
list<value_type>::ListIterator::operator--() {
  if (ptr_ != nullptr) {
    ptr_ = ptr_->ptr_prev_;
  }
  return *this;
}

template <class value_type>
typename list<value_type>::iterator
list<value_type>::ListIterator::operator--(int value) {
  iterator temp(*this);
  if (ptr_ != nullptr) {
    ptr_ = ptr_->ptr_prev_;
  }
  return temp;
}

template <class value_type>
typename list<value_type>::iterator
list<value_type>::ListIterator::operator-(int value) {
  for (int i = 0; i < value; ++i) {
    ptr_ = ptr_->ptr_prev_;
  }
  return *this;
}

template <class value_type>
typename list<value_type>::iterator &
list<value_type>::ListIterator::operator=(const iterator other) {
  ptr_ = other.ptr_;
  return *this;
}

template <class value_type>
list<value_type>::ListConstIterator::ListConstIterator() : ListIterator() {}

template <class value_type>
list<value_type>::ListConstIterator::ListConstIterator(Node *ptr)
    : ListIterator(ptr) {}

template <class value_type>
list<value_type>::ListConstIterator::ListConstIterator(
    const const_iterator &other)
    : ListIterator(other) {}

template <class value_type>
list<value_type>::ListConstIterator::ListConstIterator(const iterator &other)
    : ListIterator(other) {}

template <class value_type>
bool list<value_type>::ListConstIterator::operator==(
    const iterator &other) const {
  return ListIterator::ptr_ == other.ptr_ ? true : false;
}

template <class value_type>
bool list<value_type>::ListConstIterator::operator!=(
    const iterator &other) const {
  return ListIterator::ptr_ != other.ptr_ ? true : false;
}

template <class value_type>
typename list<value_type>::reference
list<value_type>::ListConstIterator::operator*() {
  return ListIterator::ptr_->data_;
}

template <class value_type>
typename list<value_type>::const_reference list<value_type>::front() const {
  auto iter = begin();
  return *iter;
}

template <class value_type>
typename list<value_type>::const_reference list<value_type>::back() const {
  auto iter = end();
  return *(--iter);
}

template <class value_type>
void list<value_type>::push_back(const_reference value) {
  int key = 0;
  if (head_ == nullptr) {
    init_head_tail(value);
  } else {
    key = 2;
    Node *current = tail_;
    tail_->ptr_next_ = new Node(value, fict_, current);
    tail_ = tail_->ptr_next_;
  }
  rewrite(key);
}

template <class value_type>
void list<value_type>::push_front(const_reference value) {
  int key = 0;
  if (head_ == nullptr) {
    init_head_tail(value);
  } else {
    key = 1;
    Node *current = head_;
    current->ptr_prev_ = new Node(value, current);
    head_ = current->ptr_prev_;
  }
  rewrite(key);
}

template <class value_type> bool list<value_type>::empty() const {
  return fict_->ptr_next_ == fict_;
}

template <class value_type> void list<value_type>::pop_front() {
  if (size_ > 0) {
    Node *temp = fict_->ptr_next_;
    fict_->ptr_next_ = fict_->ptr_next_->ptr_next_;
    fict_->ptr_next_->ptr_prev_ = fict_;
    delete temp;
    --size_;
    fict_->data_ = size_;
  }
}

template <class value_type> void list<value_type>::pop_back() {
  if (size_ > 0) {
    Node *temp = tail_;
    tail_ = tail_->ptr_prev_;
    tail_->ptr_next_ = fict_;
    fict_->ptr_prev_ = tail_;
    delete temp;
    --size_;
    fict_->data_ = size_;
  }
}

template <class value_type>
typename list<value_type>::iterator
list<value_type>::insert(iterator pos, const_reference value) {
  Node *currentNode = pos.ptr_;
  Node *prevNode = currentNode->ptr_prev_;
  Node *newNode = new Node(value);
  newNode->ptr_next_ = currentNode;
  newNode->ptr_prev_ = currentNode->ptr_prev_;
  currentNode->ptr_prev_ = newNode;
  prevNode->ptr_next_ = newNode;
  ++size_;
  tail_ = fict_->ptr_prev_;
  head_ = fict_->ptr_next_;
  fict_->data_ = size_;
  return iterator(newNode);
}

template <class value_type> void list<value_type>::erase(iterator pos) {
  if (pos == begin()) {
    pop_front();
  } else {
    if (pos != end()) {
      Node *currentNode = pos.ptr_;
      Node *prevNode = currentNode->ptr_prev_;
      Node *nextNode = currentNode->ptr_next_;
      prevNode->ptr_next_ = nextNode;
      nextNode->ptr_prev_ = prevNode;
      delete currentNode;
      --size_;
      fict_->data_ = size_;
    }
  }
}

template <class value_type> void list<value_type>::swap(list &other) {
  if (this != &other) {
    list<value_type> copy(other);
    other = std::move(*this);
    move_object(copy);
  }
}

template <class value_type> void list<value_type>::merge(list &other) {
  if (this != &other) {
    auto iter = begin();
    auto iter2 = other.begin();
    while (other.size_ > 0) {
      if (*iter2 < *iter || iter == end()) {
        insert(iter, *iter2);
        other.erase(iter2);
        iter2 = other.begin();
      } else {
        ++iter;
      }
    }
  }
}

template <class value_type>
void list<value_type>::splice(const_iterator pos, list &other) {
  if (this != &other && !other.empty() && find_iterator(pos)) {
    auto it = other.begin();
    for (auto i = other.begin(); i != other.end();) {
      it = i;
      insert(pos, *i);
      ++i;
      other.erase(it);
    }
  }
}

template <class value_type> void list<value_type>::reverse() {
  if (size_ > 1) {
    Node *tmp = fict_->ptr_next_;
    std::swap(fict_->ptr_next_, fict_->ptr_prev_);
    while (tmp != fict_) {
      std::swap(tmp->ptr_next_, tmp->ptr_prev_);
      tmp = tmp->ptr_prev_;
    }
  }
}

template <class value_type> void list<value_type>::unique() {
  if (size_ > 1) {
    auto itr = begin();
    for (auto i = begin(); i != end(); ++i) {
      itr = i;
      while (*i == *(++itr)) {
        erase(itr);
        itr = i;
      }
    }
  }
}

template <class value_type> void list<value_type>::sort() {
  if (size_ > 1) {
    Node *currentNode = head_;
    Node *nextNode = currentNode->ptr_next_;
    for (int i = 0; i < size_; ++i) {
      for (; currentNode != tail_; currentNode = currentNode->ptr_next_) {
        if (currentNode->data_ > nextNode->data_) {
          std::swap(currentNode->data_, nextNode->data_);
        }
        nextNode = nextNode->ptr_next_;
      }
      currentNode = head_;
      nextNode = currentNode->ptr_next_;
    }
  }
}

template <class value_type> void list<value_type>::clear() {
  while (size_ > 0) {
    pop_front();
  }
  head_ = tail_ = nullptr;
}

template <class value_type>
template <class... Args>
typename list<value_type>::iterator
list<value_type>::insert_many(const_iterator pos, Args &&...args) {
  iterator it = pos;
  for (auto data : {args...}) {
    insert(pos, data);
  }
  return (--it);
}

template <class value_type>
template <class... Args>
void list<value_type>::insert_many_back(Args &&...args) {
  for (auto data : {args...}) {
    push_back(data);
  }
}

template <class value_type>
template <class... Args>
void list<value_type>::insert_many_front(Args &&...args) {
  for (auto data : {args...}) {
    push_front(data);
  }
}

template <class value_type>
typename list<value_type>::iterator list<value_type>::begin() const {
  return ListIterator(fict_->ptr_next_);
}

template <class value_type>
typename list<value_type>::iterator list<value_type>::end() const {
  return ListIterator(fict_);
}

template <class value_type>
typename list<value_type>::size_type list<value_type>::size() const {
  return size_;
}

template <class value_type>
typename list<value_type>::size_type list<value_type>::max_size() const {
  return std::min<size_type>(std::allocator<value_type>().max_size(),
                             std::numeric_limits<difference_type>::max());
}

template <class value_type> void list<value_type>::init_list() {
  fict_ = new Node();
  fict_->ptr_next_ = fict_;
  fict_->ptr_prev_ = fict_;
  size_ = 0;
}

template <class value_type>
void list<value_type>::init_head_tail(value_type data) {
  if (fict_ == nullptr) {
    init_list();
  }
  head_ = new Node(data, fict_, fict_);
  tail_ = head_;
}

template <class value_type> bool list<value_type>::find_iterator(iterator it) {
  bool rez = false;
  if (it.ptr_ == fict_) {
    rez = true;
  } else {
    for (auto i = begin(); i != end(); ++i) {
      if (i.ptr_ == it.ptr_) {
        rez = true;
      }
    }
    if (rez == false) {
    }
  }
  return rez;
}

template <class value_type> void list<value_type>::rewrite(int key) {
  if (size_ < 0) {
    size_ = 0;
  }
  if (key == 0) {
    fict_->ptr_next_ = head_;
    fict_->ptr_prev_ = tail_;
  }
  if (key == 1) {
    head_->ptr_prev_ = fict_;
    fict_->ptr_next_ = head_;
  }
  if (key == 2) {
    tail_->ptr_next_ = fict_;
    fict_->ptr_prev_ = tail_;
  }
  ++size_;
  fict_->data_ = size_;
}

} // namespace s21
