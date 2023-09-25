#pragma once

#include <concepts>

// template <typename T>
// concept container = requires(T t){
//     t.begin();
//     t.end();
//     typename T::value_type;
// };


template <typename Derived>
class Piper{
public:

    template<typename INIT, typename Func>
    struct Package{
        INIT init;
        Func func;
        Derived* derived;
    };

    // template<container V, typename value_type, typename Func>
    // value_type operator()(V, value_type, Func) const; // defined by the derived class

    template<typename INIT, typename Func>
    Package<INIT, Func> operator()(INIT init, Func func) const{
        return Package<INIT, Func>{init, func, const_cast<Derived*>(static_cast<const Derived*>(this))};
    }
};

// template <container V, typename INIT, std::invocable<INIT, typename V::value_type> Func, template <class, typename> class P, typename Derived>
// auto operator | (V v, typename Piper<Derived>:: template Package<INIT, Func> p){
//     return p.derived->operator()(v, p.init, p.func);
// }

template <std::ranges::range V, template <typename, typename> class P, typename INIT, std::invocable<INIT, std::decay_t<std::ranges::range_value_t<V>>> Func>
auto operator | (V v, P<INIT, Func> p){
    return p.derived->operator()(v, p.init, p.func);
}