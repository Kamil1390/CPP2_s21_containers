#ifndef SRC_QUEUE_QUEUE_H
#define SRC_QUEUE_QUEUE_H

#include "../List/list.h"

namespace s21 {
template <class T, class Container = s21::list<T>> class queue {
public:
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

  queue() : baseClass(){};
  queue(std::initializer_list<value_type> const &items) : baseClass(items){};
  queue(const queue &q) : baseClass(q.baseClass){};
  queue(queue &&q) noexcept : baseClass(std::move(q.baseClass)){};
  queue &operator=(queue &&q) noexcept {
    baseClass = std::move(q.baseClass);
    return *this;
  };
  queue &operator=(const queue &q) {
    baseClass = (q.baseClass);
    return *this;
  };
  ~queue(){};

  const_reference front() const { return baseClass.front(); };
  const_reference back() const { return baseClass.back(); };

  bool empty() const { return baseClass.empty(); };
  size_type size() const { return baseClass.size(); };

  void push(const_reference value) { baseClass.push_back(value); };
  void pop() { baseClass.pop_front(); };
  void swap(queue &other) { baseClass.swap(other.baseClass); };
  void print() { baseClass.print(); };

  template <class... Args> void insert_many_back(Args &&...args) {
    baseClass.insert_many_back(args...);
  };

private:
  Container baseClass;
};
} // namespace s21

#endif //  SRC_QUEUE_QUEUE_H