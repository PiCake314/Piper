#pragma once

#include <concepts>
#include <ranges>


template <typename Derived>
requires std::is_object_v<Derived> && std::same_as<Derived, std::remove_cvref_t<Derived>>
class Piper;

template <typename T>
concept PiperType = std::is_base_of_v<Piper<std::remove_cvref_t<T>>, std::remove_cvref_t<T>>;


template <typename T>
concept Packaged = requires(T t){
    t.derived; t.args;
};


template <PiperType D, typename... Types>
struct Package{
    const D* derived;
    std::tuple<Types...> args;

    template <typename V>
    inline constexpr auto operator()(V&& v) const {
        // return v | *this;
        return operator|(std::forward<V>(v), *this);
    }

    inline constexpr Package& operator()(){
        return *this;
    }
};


template <typename Derived>
requires std::is_object_v<Derived> && std::same_as<Derived, std::remove_cvref_t<Derived>>
class Piper{
public:
    template <typename... Types>
    [[nodiscard]] inline constexpr Package<Derived, Types...> operator()(Types... params) const {
        // I had std::forward here but it was causing problems (UB? or possibly just lifetime issues)
        return {static_cast<const Derived*>(this), {params...}};
    }
};


template <size_t... Is, typename V>                                                  // doesn't have to be a range
inline constexpr auto piperHelpr(std::index_sequence<Is...>, Packaged auto&& p, /* std::ranges::range */ V&& v){ // helps unpack the tuple by index instead of type to avoid ambiguity
    return p.derived->operator()(std::forward<V>(v), std::forward<decltype(std::get<Is>(p.args))>(std::get<Is>(p.args))...);
}


template <Packaged P1, Packaged P2>
struct Composed : Piper<Composed<P1, P2>>{
    P1 p1;
    P2 p2;

    template <Packaged P1_, Packaged P2_>
    constexpr Composed(P1_&& f1, P2_&& f2) : p1(std::forward<P1>(f1)), p2(std::forward<P2>(f2)){}

    template <typename... Types>
    inline constexpr auto operator()(Types&&... v) const { // regular syntax
        return p2(p1(std::forward<Types>(v)...));
    }

    [[nodiscard]] inline constexpr auto operator()() const { // returns a package to invoke |
        return static_cast<const Piper<Composed<P1, P2>>*>(this)->operator()();
    }

};

// for composing two pipers
template <typename F1, typename F2>
requires ((PiperType<F1> || Packaged<F1>) && (PiperType<F2> || Packaged<F2>))
inline constexpr auto operator|(F1&& f1, F2&& f2){
    if constexpr(PiperType<F1> && PiperType<F2>){
        using P1 = decltype(f1());
        using P2 = decltype(f2());
        return Composed<P1, P2>{std::forward<P1>(f1()), std::forward<P2>(f2())};
    }
    else if constexpr(PiperType<F1>){
        using P1 = decltype(f1());
        return Composed<P1, F2>{std::forward<P1>(f1()), std::forward<F2>(f2)};
    }
    else if constexpr(PiperType<F2>){
        using P2 = decltype(f2());
        return Composed<F1, P2>{std::forward<F1>(f1), std::forward<P2>(f2())};
    }
    else{
        return Composed<F1, F2>{std::forward<F1>(f1), std::forward<F2>(f2)};
    }
}

template <typename V, Packaged P>
requires (!Packaged<V> && !PiperType<V>)
inline constexpr auto operator|(V&& v, P&& p){
    auto size = std::tuple_size<decltype(p.args)>{};
    return piperHelpr(std::make_index_sequence<size>{}, std::forward<P>(p), std::forward<V>(v));
}

template <typename V>
requires (!Packaged<V> && !PiperType<V>)
inline constexpr auto operator|(V&& v, PiperType auto&& p2){
    // return v | p2();
    // return std::forward<V>(v) | p2();
    return operator|(std::forward<V>(v), p2());
}
