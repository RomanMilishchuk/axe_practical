#include <iostream>
#include "atomic_double.hpp"

namespace std {
    atomic<double>::atomic(double a) : container{a}, lock{} {}

    bool atomic<double>::is_lock_free() { return false; }

    double atomic<double>::operator++() {
        lock_guard<mutex> lg{lock};
        double a{container};
        container++;
        return a;
    }

    double atomic<double>::operator--() {
        lock_guard<mutex> lg{lock};
        double a{container};
        container--;
        return a;
    }

    double atomic<double>::operator++(int) {
        lock_guard<mutex> lg{lock};
        return ++container;
    }

    double atomic<double>::operator--(int) {
        lock_guard<mutex> lg{lock};
        return --container;
    }

    ostream &operator<<(ostream &out, const atomic<double> &c) {
        out << c.container;
        return out;
    }

    istream &operator>>(istream &in, atomic<double> &c) {
        in >> c.container;
        return in;
    }

}