#ifndef ATOMIC_STRING_ATOMIC_STRING_HPP
#define ATOMIC_STRING_ATOMIC_STRING_HPP

#include <atomic>
#include <algorithm>
#include <mutex>

namespace std {
    template<>
    class atomic<string> {
        string container;
        mutex lock;
    public:
        atomic() = default;

        explicit atomic(string a);

        ~atomic() = default;

        bool is_lock_free();

        atomic(const atomic &) = delete;

        atomic &operator=(const atomic &) = delete;

        size_t size();

        string operator+=(const string &rhs);

        string operator+(const string &rhs);

        void clear();

        string insert(size_t index, const string &to_insert);

        void erase(size_t begin, size_t count);

        friend ostream &operator<<(ostream &out, atomic<string> &c);

        friend istream &operator>>(istream &in, atomic<string> &c);

    };
}
#endif //ATOMIC_STRING_ATOMIC_STRING_HPP
