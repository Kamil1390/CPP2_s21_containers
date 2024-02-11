#include "set.h"

namespace s21 {
template <typename Key, typename Value, typename Compare>
std::unique_ptr<typename set<Key, Value, Compare>::Node>
    set<Key, Value, Compare>::nil_ = std::make_unique<Node>();

template <class Key, class Value, class Compare>
typename set<Key, Value, Compare>::Node *
set<Key, Value, Compare>::minValue(Node *node) {
  if (node == nil_.get())
    return node;
  while (node->left_ != nil_.get()) {
    node = node->left_;
  }
  return node;
}

template <class Key, class Value, class Compare>
typename set<Key, Value, Compare>::Node *
set<Key, Value, Compare>::maxValue(Node *node) {
  if (node == nil_.get())
    return node;
  while (node->right_ != nil_.get()) {
    node = node->right_;
  }
  return node;
}

template <class Key, class Value, class Compare>
bool set<Key, Value, Compare>::ConstIterator::operator!=(
    const ConstIterator &other) {
  return node_ != other.node_;
}

template <class Key, class Value, class Compare>
bool set<Key, Value, Compare>::ConstIterator::operator==(
    const ConstIterator &other) {
  return node_ == other.node_;
}

template <class Key, class Value, class Compare>
typename set<Key, Value, Compare>::ConstIterator &
set<Key, Value, Compare>::ConstIterator::operator++() {
  if (node_ == nil_.get() &&
      ConstIterator(past_node_).nextValue() != nil_.get()) {
    node_ = past_node_;
    past_node_ = node_->parent_;
  } else {
    past_node_ = node_;
    node_ = nextValue();
  }
  return *this;
}

template <class Key, class Value, class Compare>
typename set<Key, Value, Compare>::ConstIterator
set<Key, Value, Compare>::ConstIterator::operator++(int) {
  ConstIterator iter = *this;
  ++(*this);
  return iter;
}

template <class Key, class Value, class Compare>
typename set<Key, Value, Compare>::ConstIterator &
set<Key, Value, Compare>::ConstIterator::operator--() {
  if (node_ == nil_.get() &&
      ConstIterator(past_node_).prevValue() != nil_.get()) {
    node_ = past_node_;
    past_node_ = node_->parent_;
  } else {
    past_node_ = node_;
    node_ = prevValue();
  }
  return *this;
}

template <class Key, class Value, class Compare>
typename set<Key, Value, Compare>::ConstIterator
set<Key, Value, Compare>::ConstIterator::operator--(int) {
  ConstIterator iter = *this;
  --(*this);
  return iter;
}

template <class Key, class Value, class Compare>
typename set<Key, Value, Compare>::const_reference
set<Key, Value, Compare>::ConstIterator::operator*() {
  return get_node()->value_;
}

template <class Key, class Value, class Compare>
typename set<Key, Value, Compare>::Node *
set<Key, Value, Compare>::ConstIterator::nextValue() {
  Node *node = get_node();
  if (node->right_ != nil_.get())
    return minValue(node->right_);
  Node *temp = node->parent_;
  while (temp != nil_.get() && node == temp->right_) {
    node = temp;
    temp = temp->parent_;
  }
  return temp;
}

template <class Key, class Value, class Compare>
typename set<Key, Value, Compare>::Node *
set<Key, Value, Compare>::ConstIterator::prevValue() {
  Node *node = this->get_node();
  if (node->left_ != nil_.get())
    return maxValue(node->left_);
  Node *temp = node->parent_;
  while (temp != nil_.get() && node == temp->left_) {
    node = temp;
    temp = temp->parent_;
  }
  return temp;
}

template <class Key, class Value, class Compare>
typename set<Key, Value, Compare>::Node *
set<Key, Value, Compare>::ConstIterator::get_node() const {
  return node_;
}

template <class Key, class Value, class Compare>
set<Key, Value, Compare>::set() {
  root_ = nil_.get();
}

template <class Key, class Value, class Compare>
set<Key, Value, Compare>::set(std::initializer_list<value_type> const &items) {
  root_ = nil_.get();
  for (value_type item : items)
    insert(item);
}

template <class Key, class Value, class Compare>
set<Key, Value, Compare>::set(const set &other) {
  root_ = copyTree(other.root_);
}

template <class Key, class Value, class Compare>
set<Key, Value, Compare> &
set<Key, Value, Compare>::operator=(const set &other) {
  if (this != other) {
    root_ = copyTree(other.root_);
  }
  return *this;
}

template <class Key, class Value, class Compare>
set<Key, Value, Compare>::set(set &&other) {
  root_ = nil_.get();
  swap(other);
}

template <class Key, class Value, class Compare>
set<Key, Value, Compare> &set<Key, Value, Compare>::operator=(set &&other) {
  if (this != other) {
    clear();
    swap(other);
  }
  return *this;
}

template <class Key, class Value, class Compare>
set<Key, Value, Compare>::~set() {
  clear();
  root_ = nullptr;
}

template <class Key, class Value, class Compare>
typename set<Key, Value, Compare>::Node *
set<Key, Value, Compare>::copyTree(Node *node, Node *parent) {
  if (node == nil_.get()) {
    return nil_.get();
  }
  Node *new_parent = new Node(node->key_, node->value_, node->color_, parent);
  new_parent->left_ = copyTree(node->left_, new_parent);
  new_parent->right_ = copyTree(node->right_, new_parent);
  return new_parent;
}

template <class Key, class Value, class Compare>
typename set<Key, Value, Compare>::iterator
set<Key, Value, Compare>::begin() const {
  return Iterator(minValue(root_));
}

template <class Key, class Value, class Compare>
typename set<Key, Value, Compare>::iterator
set<Key, Value, Compare>::end() const {
  if (root_ == nil_.get())
    return begin();
  Iterator iter(maxValue(root_));
  ++iter;
  return Iterator(iter);
}

template <class Key, class Value, class Compare>
bool set<Key, Value, Compare>::empty() const {
  return size() == 0;
}

template <class Key, class Value, class Compare>
typename set<Key, Value, Compare>::size_type
set<Key, Value, Compare>::size() const {
  size_type count = 0;
  iterator iter = begin();
  iterator iter_end = end();
  while (iter != iter_end) {
    ++count;
    ++iter;
  }
  return count;
}

template <class Key, class Value, class Compare>
typename set<Key, Value, Compare>::size_type
set<Key, Value, Compare>::max_size() const {
  return std::min<size_type>(std::allocator<Node>().max_size(),
                             std::numeric_limits<difference_type>::max());
}

template <class Key, class Value, class Compare>
void set<Key, Value, Compare>::clear() {
  if (root_ != nil_.get()) {
    makeClearTree(root_);
    root_ = nil_.get();
  }
}

template <class Key, class Value, class Compare>
void set<Key, Value, Compare>::makeClearTree(Node *node) {
  if (node != nil_.get()) {
    makeClearTree(node->left_);
    makeClearTree(node->right_);
    delete node;
  }
}

template <class Key, class Value, class Compare>
std::pair<typename set<Key, Value, Compare>::Iterator, bool>
set<Key, Value, Compare>::insert(const value_type &value) {
  Node *current_node = root_;
  Node *parent = nil_.get();
  while (current_node != nil_.get()) {
    parent = current_node;
    if (compare_(parent->key_, value))
      current_node = current_node->right_;
    else if (compare_(value, parent->key_))
      current_node = current_node->left_;
    else
      return std::pair<Iterator, bool>(find(parent->key_), false);
  }
  Node *new_node = new Node(value);
  new_node->parent_ = parent;
  if (parent == nil_.get())
    root_ = new_node;
  else if (compare_(parent->key_, value))
    parent->right_ = new_node;
  else
    parent->left_ = new_node;
  balanceAfterInsert(new_node);
  return std::pair<Iterator, bool>(find(new_node->key_), true);
}

template <class Key, class Value, class Compare>
void set<Key, Value, Compare>::balanceAfterInsert(Node *node) {
  Node *uncle;
  while (node != root_ && node->parent_->color_ == RED) {
    if (node->parent_ == node->parent_->parent_->left_) {
      uncle = node->parent_->parent_->right_;
      if (uncle->color_ == RED) {
        node->parent_->color_ = BLACK;
        uncle->color_ = BLACK;
        node->parent_->parent_->color_ = RED;
        node = node->parent_->parent_;
      } else {
        if (node == node->parent_->right_) {
          node = node->parent_;
          leftRotate(node);
        }
        node->parent_->color_ = BLACK;
        node->parent_->parent_->color_ = RED;
        rightRotate(node->parent_->parent_);
      }
    } else {
      uncle = node->parent_->parent_->left_;
      if (uncle->color_ == RED) {
        node->parent_->color_ = BLACK;
        uncle->color_ = BLACK;
        node->parent_->parent_->color_ = RED;
        node = node->parent_->parent_;
      } else {
        if (node == node->parent_->left_) {
          node = node->parent_;
          rightRotate(node);
        }
        node->parent_->color_ = BLACK;
        node->parent_->parent_->color_ = RED;
        leftRotate(node->parent_->parent_);
      }
    }
  }
  root_->color_ = BLACK;
}

template <class Key, class Value, class Compare>
void set<Key, Value, Compare>::erase(iterator pos) {
  Node *data = pos.get_node();
  if (data != nil_.get()) {
    Node *node;
    if (data->right_ == nil_.get() || data->left_ == nil_.get()) {
      node = data;
    } else {
      ++pos;
      node = pos.get_node();
    }
    Node *child = (node->left_ != nil_.get()) ? node->left_ : node->right_;
    child->parent_ = node->parent_;
    if (node->parent_ == nil_.get()) {
      root_ = child;
    } else {
      if (node == node->parent_->left_)
        node->parent_->left_ = child;
      else
        node->parent_->right_ = child;
    }
    if (node != data) {
      data->value_ = node->value_;
      data->key_ = node->key_;
    }
    if (node->color_ == BLACK)
      balanceAfterErase(child);
    delete node;
  }
  nil_->parent_ = nullptr;
}

template <class Key, class Value, class Compare>
void set<Key, Value, Compare>::balanceAfterErase(Node *node) {
  while (node != root_ && node->color_ == BLACK) {
    node == node->parent_->left_ ? balanceAfterEraseLeft(node)
                                 : balanceAfterEraseRight(node);
  }
  node->color_ = BLACK;
}

template <class Key, class Value, class Compare>
void set<Key, Value, Compare>::balanceAfterEraseLeft(Node *&node) {
  Node *brother = node->parent_->right_;
  if (brother->color_ == RED) {
    brother->color_ = BLACK;
    node->parent_->color_ = RED;
    leftRotate(node->parent_);
    brother = node->parent_->right_;
  }
  if (brother->left_->color_ == BLACK && brother->right_->color_ == BLACK) {
    brother->color_ = RED;
    node = node->parent_;
  } else {
    if (brother->right_->color_ == BLACK) {
      brother->left_->color_ = BLACK;
      brother->color_ = RED;
      rightRotate(brother);
      brother = node->parent_->right_;
    }
    brother->color_ = node->parent_->color_;
    node->parent_->color_ = BLACK;
    brother->right_->color_ = BLACK;
    leftRotate(node->parent_);
    node = root_;
  }
}

template <class Key, class Value, class Compare>
void set<Key, Value, Compare>::balanceAfterEraseRight(Node *&node) {
  Node *brother = node->parent_->left_;
  if (brother->color_ == RED) {
    brother->color_ = BLACK;
    node->parent_->color_ = RED;
    rightRotate(node->parent_);
    brother = node->parent_->left_;
  }
  if (brother->left_->color_ == BLACK && brother->right_->color_ == BLACK) {
    brother->color_ = RED;
    node = node->parent_;
  } else {
    if (brother->left_->color_ == BLACK) {
      brother->right_->color_ = BLACK;
      brother->color_ = RED;
      leftRotate(brother);
      brother = node->parent_->left_;
    }
    brother->color_ = node->parent_->color_;
    node->parent_->color_ = BLACK;
    brother->left_->color_ = BLACK;
    rightRotate(node->parent_);
    node = root_;
  }
}

template <class Key, class Value, class Compare>
void set<Key, Value, Compare>::rightRotate(Node *node) {
  Node *buffer = node->left_;
  node->left_ = buffer->right_;
  if (buffer->right_ != nil_.get())
    buffer->right_->parent_ = node;
  buffer->parent_ = node->parent_;
  if (node->parent_ == nil_.get()) {
    root_ = buffer;
  } else {
    if (node == node->parent_->right_) {
      node->parent_->right_ = buffer;
    } else {
      node->parent_->left_ = buffer;
    }
  }
  buffer->right_ = node;
  node->parent_ = buffer;
}

template <class Key, class Value, class Compare>
void set<Key, Value, Compare>::leftRotate(Node *node) {
  Node *buffer = node->right_;
  node->right_ = buffer->left_;
  if (buffer->left_ != nil_.get())
    buffer->left_->parent_ = node;
  buffer->parent_ = node->parent_;
  if (node->parent_ == nil_.get()) {
    root_ = buffer;
  } else {
    if (node == node->parent_->left_) {
      node->parent_->left_ = buffer;
    } else {
      node->parent_->right_ = buffer;
    }
  }
  buffer->left_ = node;
  node->parent_ = buffer;
}

template <class Key, class Value, class Compare>
void set<Key, Value, Compare>::swap(set &other) {
  std::swap(root_, other.root_);
}

template <class Key, class Value, class Compare>
void set<Key, Value, Compare>::merge(set &other) {
  if (root_ == nil_.get())
    swap(other);
  else {
    Iterator iter = other.begin();
    Iterator next_iter = other.begin();
    while (iter != other.end()) {
      ++next_iter;
      std::pair<Iterator, bool> result_insert = insert(iter.get_node()->value_);
      if (result_insert.second)
        other.erase(iter);
      iter = next_iter;
    }
  }
}

template <class Key, class Value, class Compare>
typename set<Key, Value, Compare>::iterator
set<Key, Value, Compare>::find(const Key &key) const {
  Node *current_node = root_;
  while (current_node != nil_.get() && current_node->key_ != key) {
    current_node =
        (key < current_node->key_) ? current_node->left_ : current_node->right_;
  }
  return Iterator(current_node);
}

template <class Key, class Value, class Compare>
bool set<Key, Value, Compare>::contains(const Key &key) const {
  return find(key).get_node() != nil_.get();
}

template <class Key, class Value, class Compare>
template <class... Args>
std::vector<std::pair<typename set<Key, Value, Compare>::iterator, bool>>
set<Key, Value, Compare>::insert_many(Args &&...args) {
  std::vector<std::pair<iterator, bool>> result;
  value_type arr[] = {args...};
  for (value_type element : arr)
    result.push_back(insert(element));
  return result;
}

template <class Key, class Value, class Compare>
typename set<Key, Value, Compare>::Node *
set<Key, Value, Compare>::get_root() const {
  return root_;
}

template <class Key, class Value, class Compare>
void set<Key, Value, Compare>::printImageTree(Node *node, int depth,
                                              char branch) {
  if (node == nil_.get())
    return;
  printImageTree(node->right_, depth + 1, '/');
  std::cout << std::string(4 * depth, ' ') << branch << node->key_ << ":"
            << branch << node->value_ << std::string(":") << node->color_
            << std::endl;
  printImageTree(node->left_, depth + 1, '\\');
}

template <class Key, class Value, class Compare>
void set<Key, Value, Compare>::printSortTree(Node *node) {
  if (node == nil_.get())
    return;
  printSortTree(node->left_);
  std::cout << node->value_ << ' ';
  printSortTree(node->right_);
}
} // namespace s21