#ifndef ATOMIC_DOUBLE_ATOMIC_DOUBLE_HPP
#define ATOMIC_DOUBLE_ATOMIC_DOUBLE_HPP

#include <atomic>
#include <mutex>

namespace std {
    template<>
    class atomic<double> {
        double container;
        mutex lock;
    public:
        atomic() = default;

        explicit atomic(double a);

        ~atomic() = default;

        bool is_lock_free();

        atomic(const atomic &) = delete;

        atomic &operator=(const atomic &) = delete;


        double operator++();

        double operator--();

        double operator++(int);

        double operator--(int);

        template<typename RhsT>
        double operator+=(RhsT rhs) {
            lock_guard<mutex> lg{lock};
            container += rhs;
            return container;
        }

        template<typename RhsT>
        double operator-=(RhsT rhs) {
            lock_guard<mutex> lg{lock};
            container -= rhs;
            return container;
        }

        friend ostream &operator<<(ostream &out, const atomic<double> &c);

        friend istream &operator>>(istream &in, atomic<double> &c);

    };
}
#endif //ATOMIC_DOUBLE_ATOMIC_DOUBLE_HPP
