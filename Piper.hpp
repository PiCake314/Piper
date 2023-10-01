#pragma once

#include <concepts>
#include <ranges>
#include <utility>

template <typename Derived>
class Piper{
    template<typename... Types>
    struct Package{
        const Derived* derived;
        std::tuple<std::decay_t<Types>...> args;
    };

public:
    template<typename... Types>
    Package<Types...> operator()(Types&&... params) const{
        return {static_cast<const Derived*>(this), {params...}};
    }
};


template <size_t... Is>
auto piperHelpr( std::index_sequence<Is...>, auto&& V, auto&& p){
    return p.derived->operator()(std::forward<decltype(V)>(V), std::forward<decltype(std::get<Is>(p.args))>(std::get<Is>(p.args))...);
}


template <std::ranges::range V, template <typename...> class P, typename... Types>
auto operator | (V&& v, P<Types...> p){
    std::tuple_size<decltype(p.args)> size;

    return piperHelpr(std::make_index_sequence<size>(), std::forward<V>(v), std::forward<P<Types...>>(p));
    // return p.derived->operator()(std::forward<V>(v), std::forward<Types>(std::get<Types>(p.args))...);
}