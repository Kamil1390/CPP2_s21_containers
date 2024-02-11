#include "multiset.h"

namespace s21 {
    template<class Key>
    multiset<Key> &multiset<Key>::operator=(multiset &&other) {
        if (this != other) {
            this->root_ = this->nil_.get();
            swap(other);
            other.clear();
        }
        return *this;
    }

    template<class Key>
    multiset<Key> &multiset<Key>::operator=(const multiset &other) {
        if (this != other) {
            this->clear();
            this->root_ = copyTree(other.root_);
        }
        return *this;
    }

    template<class Key>
    typename multiset<Key>::size_type multiset<Key>::count(const Key &key) const {
        size_type count = 0;
        iterator iter = this->begin();
        while (iter != this->end()) {
            if (*iter == key) ++count;
            ++iter;
        }
        return count;
    }

    template<class Key>
    typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key &key) const {
        iterator iter = this->begin();
        while (iter != this->end()) {
            if (*iter >= key) return iter;
            ++iter;
        }
        return iter;
    }

    template<class Key>
    typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key &key) const {
        iterator iter = this->begin();
        while (iter != this->end()) {
            if (*iter > key) return iter;
            ++iter;
        }
        --iter;
        return iter;
    }

    template<class Key>
    std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
    multiset<Key>::equal_range(const Key &key) const {
        return std::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
    }
} // s21