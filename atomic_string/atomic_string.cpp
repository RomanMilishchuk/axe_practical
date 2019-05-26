#include <utility>

//
// Created by hermann on 26.05.19.
//

#include "atomic_string.hpp"
#include <iostream>

namespace std {
    string atomic<string>::operator+=(const string &rhs) {
        lock_guard<mutex> lg{lock};
        container += rhs;
        return container;
    }

    string atomic<string>::operator+(const string &rhs) {
        lock_guard<mutex> lg{lock};
        return container + rhs;
    }

    void atomic<string>::clear() {
        lock_guard<std::mutex> lg{lock};
        container.clear();
    }

    string atomic<string>::insert(size_t index, const string &to_insert) {
        lock_guard<mutex> lg{lock};
        return container.insert(index, to_insert);
    }

    void atomic<string>::erase(size_t begin, size_t count) {
        lock_guard<mutex> lg{lock};
        container.erase(begin, count);
    }

    bool atomic<string>::is_lock_free() { return false; }

    atomic<string>::atomic(string a) : container{std::move(a)}, lock{} {}

    ostream &operator<<(ostream &out, atomic<string> &c) {
        out << c.container;
        return out;
    }

    istream &operator>>(istream &in, atomic<string> &c) {
        return in >> c.container;
    }

    size_t atomic<string>::size() {
        lock_guard<mutex> lg{lock};
        return container.size();
    }


}
