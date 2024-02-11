#ifndef TREE_SET_H
#define TREE_SET_H
#include <initializer_list>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

namespace s21 {
template <class Key, class Value> class map;
template <class Key, class Value = Key, class Compare = std::less<Key>>
class set {
  enum Color { BLACK, RED };

public:
  struct Node;
  struct ConstIterator;
  struct Iterator;
  using key_type = Key;
  using value_type = Value;
  using referance = value_type &;
  using const_reference = const value_type &;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

  struct Node {
  public:
    Node() = default;
    explicit Node(Value value)
        : key_(value), value_(value), color_(RED), left_(nil_.get()),
          right_(nil_.get()), parent_(nil_.get()){};
    Node(Key key, Value value)
        : key_(key), value_(value), color_(RED), left_(nil_.get()),
          right_(nil_.get()), parent_(nil_.get()){};
    Node(Key key, Value value, Color color, Node *parent)
        : key_(key), value_(value), color_(color), left_(nil_.get()),
          right_(nil_.get()), parent_(parent){};

  protected:
    Key key_;
    Value value_;
    Color color_ = BLACK;
    Node *left_ = nullptr;
    Node *right_ = nullptr;
    Node *parent_ = nullptr;

    friend class set<Key, Value, Compare>;
    friend class map<Key, Value>;
  };

  struct ConstIterator {
  public:
    ConstIterator() = default;
    explicit ConstIterator(Node *node)
        : node_(node), past_node_(node->parent_){};
    bool operator!=(const const_iterator &other);
    bool operator==(const const_iterator &other);
    ConstIterator &operator++();
    ConstIterator operator++(int);
    ConstIterator &operator--();
    ConstIterator operator--(int);
    const Value &operator*();
    Node *get_node() const;

  private:
    Node *nextValue();
    Node *prevValue();

  protected:
    Node *node_ = nil_.get();
    Node *past_node_ = nil_.get();

    friend class map<Key, Value>;
  };

  struct Iterator : ConstIterator {
  public:
    Iterator() : ConstIterator(){};
    explicit Iterator(Node *node) : ConstIterator(node){};
  };

  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &other);
  set &operator=(const set &other);
  set(set &&other);
  set &operator=(set &&other);
  ~set();

  iterator begin() const;
  iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  std::pair<iterator, bool> insert(const_reference value);
  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);

  iterator find(const Key &key) const;
  bool contains(const Key &key) const;

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

  void printImageTree(Node *node, int depth = 0, char branch = ' ');
  void printSortTree(Node *node);
  Node *get_root() const;

private:
  Node *copyTree(Node *node, Node *new_parent = nil_.get());
  void balanceAfterErase(Node *node);
  void balanceAfterEraseLeft(Node *&node);
  void balanceAfterEraseRight(Node *&node);
  void rightRotate(Node *node);
  void leftRotate(Node *node);
  void makeClearTree(Node *node);

protected:
  static std::unique_ptr<Node> nil_;
  Node *root_;
  Compare compare_ = Compare();
  void balanceAfterInsert(Node *node);
  static Node *minValue(Node *node);
  static Node *maxValue(Node *node);
};
} // namespace s21

#include "set.cpp"
#endif // TREE_SET_H
