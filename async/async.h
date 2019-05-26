#ifndef ASYNC_ASYNC_H
#define ASYNC_ASYNC_H

#include <future>
#include <iostream>

namespace launch {
    enum parameters {
        async,
        deferred
    };
}

template<typename Func, typename... Params>
auto async(launch::parameters launch_parameter, Func func, Params... params) {
    std::promise<decltype(func(params...))> p{};
    switch (launch_parameter) {
        case launch::async: {
            auto future = p.get_future();
            std::thread([func, params..., p = std::move(p)]() mutable {
                auto x = func(params...);
                p.set_value(x);
            }).detach();
            return future;
        }
        case launch::deferred: {
            p.set_value(func(params...));
            return p.get_future();
        }
    }
}

#endif //ASYNC_ASYNC_H
