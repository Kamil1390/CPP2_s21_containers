#ifndef SRC_STACK_STACK_H_
#define SRC_STACK_STACK_H_

#include "../List/list.h"

namespace s21 {
template <class T, class Container = s21::list<T>> class stack {
public:
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

  stack() : baseClass(){};
  stack(std::initializer_list<T> const &items) : baseClass(items){};
  stack(const stack &s) : baseClass(s.baseClass){};
  stack(stack &&s) noexcept : baseClass(std::move(s.baseClass)){};
  stack &operator=(stack &&s) noexcept {
    baseClass = std::move(s.baseClass);
    return *this;
  };
  stack &operator=(const stack &s) {
    baseClass = (s.baseClass);
    return *this;
  };
  ~stack(){};

  const_reference top() const { return baseClass.front(); };

  bool empty() const { return baseClass.empty(); };
  size_type size() const { return baseClass.size(); };

  void push(const_reference value) { baseClass.push_front(value); };
  void pop() { baseClass.pop_front(); };
  void swap(stack &other) { baseClass.swap(other.baseClass); };
  template <class... Args> void insert_many_front(Args &&...args) {
    for (auto i : {args...}) {
      push(i);
    }
  };

private:
  Container baseClass;
};
} // namespace s21

#endif //  SRC_STACK_STACK_H_
