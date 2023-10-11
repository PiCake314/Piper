#include <iostream>
#include <vector>
#include <array>

#include "Piper.hpp"

struct Ident{
    template<typename T>
    constexpr T operator()(T&& t) const{
        return std::forward<T>(t);
    }
};


struct Fold : Piper<Fold>{
    template<std::ranges::range V, typename INIT, std::invocable<INIT, std::ranges::range_value_t<V>> OP = decltype(std::plus{})>
    constexpr INIT operator()(V&& v, INIT init, OP func = std::plus{}) const {
        for(auto&& elt : v)
            init = func(init, std::forward<decltype(elt)>(elt));

        return init;
    }
    
    template<typename INIT, typename OP = decltype(std::plus{})>
    constexpr auto operator()(INIT&& init, OP&& func = std::plus{}) const{
        return static_cast<const Piper<Fold>*>(this)->operator()(std::forward<INIT>(init), std::forward<OP>(func));
    }
};
Fold fold;


struct Map : Piper<Map>{
    template<std::ranges::range V, std::invocable<std::ranges::range_value_t<V>> OP>
    constexpr auto operator()(V&& v, OP func) const {
        std::clog << "Map\n";

        std::vector<std::invoke_result_t<OP, std::ranges::range_value_t<V>>> result;
        result.reserve(std::ranges::size(v));

        for(auto&& elt : v)
            result.push_back(func(std::forward<decltype(elt)>(elt)));

        return result;
    }
    
    template<typename OP = Ident>
    constexpr auto operator()(OP func = Ident{}) const{
        return static_cast<const Piper<Map>*>(this)->operator()(std::forward<OP>(func));
    }
};
Map map;

int main(){
    std::vector v = {1, 2, 3, 4, 5};

    // auto v2 = v | map([](auto x){ return x * x; });
    // auto value = v2 | fold(0);
    auto func = map([](auto x){ return x * x; }) | fold(0);
    // auto value = func(v);
    auto value = v | func(); // have to call it with () because of the way the operator| is defined

    std::clog << value << '\n';
}