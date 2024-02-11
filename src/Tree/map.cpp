#include "map.h"

namespace s21 {

template <class Key, class T>
typename map<Key, T>::value_type map<Key, T>::ConstIteratorMap::operator*() {
  return std::pair<Key, T>(this->get_node()->key_, this->get_node()->value_);
}

template <class Key, class T> map<Key, T> &map<Key, T>::operator=(map &&other) {
  if (this != other) {
    this->root_ = this->nil_.get();
    swap(other);
    other.clear();
  }
  return *this;
}

template <class Key, class T>
map<Key, T> &map<Key, T>::operator=(const map &other) {
  if (this != other) {
    this->clear();
    this->root_ = copyTree(other.root_);
  }
  return *this;
}

template <class Key, class T>
map<Key, T>::map(std::initializer_list<value_type> const &items) {
  this->root_ = this->nil_.get();
  for (value_type item : items)
    insert(item.first, item.second);
}

template <class Key, class T> T &map<Key, T>::at(const Key &key) {
  node_type *node = find(key).node_;
  if (node == this->nil_.get())
    throw std::out_of_range("map::at");
  return node->value_;
}

template <class Key, class T> T &map<Key, T>::operator[](const Key &key) {
  node_type *node = find(key).node_;
  return node->value_;
}

template <class Key, class T>
typename map<Key, T>::iterator map<Key, T>::begin() const {
  return IteratorMap(this->minValue(this->root_));
}

template <class Key, class T>
typename map<Key, T>::iterator map<Key, T>::end() const {
  if (this->root_ == this->nil_.get())
    return begin();
  iterator iter(this->maxValue(this->root_));
  ++iter;
  return IteratorMap(iter);
}

template <class Key, class T>
std::pair<typename map<Key, T>::iterator, bool>
map<Key, T>::insert(const value_type &value) {
  return insert(value.first, value.second);
}

template <class Key, class T>
std::pair<typename map<Key, T>::iterator, bool>
map<Key, T>::insert(const Key &key, const T &obj) {
  node_type *current_node = this->root_;
  node_type *parent = this->nil_.get();
  while (current_node != this->nil_.get()) {
    parent = current_node;
    if (this->compare_(parent->key_, key))
      current_node = current_node->right_;
    else if (this->compare_(key, parent->key_))
      current_node = current_node->left_;
    else
      return std::pair<iterator, bool>(this->find(parent->key_), false);
  }
  node_type *new_node = new node_type(key, obj);
  new_node->parent_ = parent;
  if (parent == this->nil_.get())
    this->root_ = new_node;
  else if (this->compare_(parent->key_, key))
    parent->right_ = new_node;
  else
    parent->left_ = new_node;
  this->balanceAfterInsert(new_node);
  return std::pair<iterator, bool>(find(new_node->key_), true);
}

template <class Key, class T>
std::pair<typename map<Key, T>::iterator, bool>
map<Key, T>::insert_or_assign(const Key &key, const T &obj) {
  node_type *current_node = this->root_;
  node_type *parent = this->nil_.get();
  while (current_node != this->nil_.get()) {
    parent = current_node;
    if (this->compare_(parent->key_, key))
      current_node = current_node->right_;
    else if (this->compare_(key, parent->key_))
      current_node = current_node->left_;
    else {
      current_node->value_ = obj;
      return std::pair<iterator, bool>(find(current_node->key_), false);
    }
  }
  node_type *new_node = new node_type(key, obj);
  new_node->parent_ = parent;
  if (parent == this->nil_.get())
    this->root_ = new_node;
  else if (this->compare_(parent->key_, key))
    parent->right_ = new_node;
  else
    parent->left_ = new_node;
  this->balanceAfterInsert(new_node);
  return std::pair<iterator, bool>(find(new_node->key_), true);
}

template <class Key, class T>
void map<Key, T>::copyNode(typename set<Key, T>::Node *&in,
                           typename set<Key, T>::Node *&out) {
  in->color_ = out->color_;
  in->parent_ = out->parent_;
  (in->parent_->left_ == out) ? in->parent_->left_ = in
                              : in->parent_->right_ = in;
  if (out->left_ != this->nil_.get()) {
    in->left_ = out->left_;
    in->left_->parent_ = in;
  }
  if (out->right_ != this->nil_.get()) {
    in->right_ = out->right_;
    in->right_->parent_ = in;
  }
}

template <class Key, class T>
typename map<Key, T>::iterator map<Key, T>::find(const Key &key) {
  node_type *current_node = this->root_;
  while (current_node != this->nil_.get() && current_node->key_ != key) {
    current_node =
        (key < current_node->key_) ? current_node->left_ : current_node->right_;
  }
  return IteratorMap(current_node);
}

template <class Key, class T> void map<Key, T>::erase(iterator pos) {
  typename set<Key, T>::iterator it;
  it.node_ = pos.node_;
  it.past_node_ = pos.past_node_;
  set<Key, T>::erase(it);
}

template <class Key, class T> void map<Key, T>::merge(map &other) {
  if (this->root_ == this->nil_.get())
    set<Key, T>::swap(other);
  else {
    iterator iter = other.begin();
    iterator next_iter = other.begin();
    while (iter != other.end()) {
      ++next_iter;
      std::pair<iterator, bool> result_insert =
          insert(iter.get_node()->key_, iter.get_node()->value_);
      if (result_insert.second)
        other.erase(iter);
      iter = next_iter;
    }
  }
}
} // namespace s21