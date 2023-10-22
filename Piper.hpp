#pragma once

#include <concepts>
#include <ranges>


template <typename Derived> class Piper;

template <typename T>
// concept PiperType = std::is_base_of_v<Piper<T>, T>;
concept PiperType = std::is_base_of_v<Piper<std::remove_cvref_t<T>>, std::remove_cvref_t<T>>;


template <typename T>
concept Packaged = requires(T t){
    t.derived; t.args;
};


template<PiperType D, typename... Types>
struct Package{
    const D* derived;
    std::tuple<Types...> args;


    constexpr auto operator()(auto v){
        return v | *this;
    }
};


template <typename Derived>
class Piper{
public:
    template<typename... Types>
    constexpr Package<Derived, Types...> operator()(Types&&... params) const{
        return {static_cast<const Derived*>(this), {params...}};
    }
};


template <size_t... Is>                                                  // doesn't have to be a range
constexpr auto piperHelpr(std::index_sequence<Is...>, Packaged auto&& p, /* std::ranges::range */ auto&& v){ // helps unpack the tuple by index instead of type to avoid ambiguity
    return p.derived->operator()(std::forward<decltype(v)>(v), std::forward<decltype(std::get<Is>(p.args))>(std::get<Is>(p.args))...);
}

template <typename P1, typename P2>
struct Composed : Piper<Composed<P1, P2>>{
    P1 p1;
    P2 p2;

    constexpr Composed(P1 f1, P2 f2) : p1(std::forward<P1>(f1)), p2(std::forward<P2>(f2)){}

    constexpr auto operator()(std::ranges::range auto v) const{ // regular syntax
        auto size1 = std::tuple_size<decltype(p1.args)>{};
        auto size2 = std::tuple_size<decltype(p2.args)>{};

        auto Is1 = std::make_index_sequence<size1>{};
        auto Is2 = std::make_index_sequence<size2>{};

        return piperHelpr(Is2, p2, piperHelpr(Is1, p1, v));
    }


    template <typename... Types>
    constexpr auto operator()(Types&&... params) const{ // returns a package to invoke |
        return static_cast<const Piper<Composed<P1, P2>>*>(this)->operator()(std::forward<Types>(params)...);
    }

};


// for composing two pipers
template <typename F1, typename F2>
requires ((PiperType<F1> || Packaged<F1>) && (PiperType<F2> || Packaged<F2>))
constexpr auto operator|(F1&& f1, F2&& f2){
    if constexpr(PiperType<F1> && PiperType<F2>){
        return Composed{std::forward<decltype(f1())>(f1()), std::forward<decltype(f2())>(f2())};
    }
    else if constexpr(PiperType<F1>){
        return Composed{std::forward<decltype(f1())>(f1()), std::forward<F2>(f2)};
    }
    else if constexpr(PiperType<F2>){
        return Composed{std::forward<F1>(f1), std::forward<decltype(f2())>(f2())};
    }
    else{
        return Composed{std::forward<F1>(f1), std::forward<F2>(f2)};
    }
}



template <typename V, Packaged P>
requires (!Packaged<V> && !PiperType<V>)
constexpr auto operator|(V&& v, P&& p){
    auto size = std::tuple_size<decltype(p.args)>{};
    return piperHelpr(std::make_index_sequence<size>(), std::forward<P>(p), std::forward<V>(v));
}

template <typename V>
requires (!Packaged<V> && !PiperType<V>)
constexpr auto operator|(V&& v, PiperType auto&& p2){
    return v | p2();
}


// // macro to make the above easier
// #define PIPER_OP(name) constexpr auto operator()(auto... args) const {\
//     return static_cast<const Piper<name>*>(this)->operator()(std::forward<decltype(args)>(args)...);\
// }\

