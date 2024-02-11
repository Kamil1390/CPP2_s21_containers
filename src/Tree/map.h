#ifndef TREE_MAP_H
#define TREE_MAP_H
#include "set.h"

namespace s21 {
template <class Key, class T> class map : public set<Key, T> {
public:
  struct ConstIteratorMap;
  struct IteratorMap;
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = IteratorMap;
  using const_iterator = ConstIteratorMap;
  using size_type = std::size_t;
  using node_type = typename set<Key, T>::Node;

  struct ConstIteratorMap : set<Key, T>::ConstIterator {
    ConstIteratorMap() : set<Key, T>::ConstIterator(){};
    explicit ConstIteratorMap(node_type *node)
        : set<Key, T>::ConstIterator(node){};
    value_type operator*();
  };

  struct IteratorMap : ConstIteratorMap {
    IteratorMap() : ConstIteratorMap(){};
    explicit IteratorMap(node_type *node) : ConstIteratorMap(node){};
  };

  map() : set<key_type, mapped_type>(){};
  map(std::initializer_list<value_type> const &items);
  map(const map &m) : set<key_type, mapped_type>(m){};
  map &operator=(const map &other);
  map(map &&m) : set<key_type, mapped_type>(std::move(m)){};
  map &operator=(map &&other);
  ~map() = default;

  T &at(const Key &key);
  T &operator[](const Key &key);

  iterator begin() const;
  iterator end() const;

  std::pair<iterator, bool> insert(const_reference value);
  std::pair<iterator, bool> insert(const Key &key, const T &obj);
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj);

  void erase(iterator pos);
  void merge(map &other);

private:
  iterator find(const Key &key);
  void copyNode(node_type *&in, node_type *&out);
};

} // namespace s21

#include "map.cpp"
#endif // TREE_MAP_H
