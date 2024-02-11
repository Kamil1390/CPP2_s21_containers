#ifndef SRC_LIST_LIST_H
#define SRC_LIST_LIST_H

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {
template <class T> class list {
public:
  list();
  list(size_t n);
  list(std::initializer_list<T> const &items);
  list(const list &l);
  list(list &&l) noexcept;
  ~list();

private:
  class ListIterator;
  class ListConstIterator;

public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;
  using difference_type = std::ptrdiff_t;

  list &operator=(const list &l);
  list &operator=(list &&l) noexcept;

  const_reference front() const;
  const_reference back() const;

  iterator begin() const;
  iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  void push_back(const_reference value);
  void push_front(const_reference value);
  void pop_front();
  void pop_back();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();
  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <class... Args> void insert_many_back(Args &&...args);
  template <class... Args> void insert_many_front(Args &&...args);

private:
  class Node {
  public:
    value_type data_;
    Node *ptr_next_;
    Node *ptr_prev_;
    Node(value_type data = value_type(), Node *ptr_next = nullptr,
         Node *ptr_prev = nullptr);
  };

  class ListIterator {
  public:
    Node *ptr_;
    ListIterator();
    ListIterator(Node *ptr);
    ListIterator(const iterator &other);

    bool operator==(const iterator &other) const;
    bool operator!=(const iterator &other) const;
    reference operator*();
    iterator &operator++();
    iterator operator++(int value);
    iterator operator+(int value);
    iterator &operator--();
    iterator operator--(int value);
    iterator operator-(int value);
    iterator &operator=(const iterator other);
  };
  class ListConstIterator : public ListIterator {
  public:
    ListConstIterator();
    ListConstIterator(Node *ptr);
    ListConstIterator(const const_iterator &other);
    ListConstIterator(const iterator &other);

    bool operator==(const iterator &other) const;
    bool operator!=(const iterator &other) const;
    reference operator*();
  };

  Node *head_;
  Node *tail_;
  Node *fict_;
  int size_;

  void init_head_tail(value_type data);
  void init_list();
  void rewrite(int key);
  void copy_object(const list &l);
  void move_object(list &l);
  bool find_iterator(ListIterator it);
};

} // namespace s21

#include "list.tpp"
#endif //  SRC_LIST_LIST_H
