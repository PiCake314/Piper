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
    template<std::ranges::range V, std::invocable<std::ranges::range_value_t<V>> OP = Ident>
    constexpr auto operator()(V&& v, OP func = Ident{}) const {
        // std::vector<std::invoke_result_t<OP, std::ranges::range_value_t<V>>> result;
        std::remove_cvref_t<V> result;
        // result.reserve(std::ranges::size(v));

        for(auto&& elt : v)
            result.push_back(func(std::forward<decltype(elt)>(elt)));

        return result;
    }
    
    template<typename OP = Ident>
    constexpr auto operator()(OP func = Ident{}) const {
        return static_cast<const Piper<Map>*>(this)->operator()(std::forward<OP>(func));
    }
};
Map map;


struct Adder : Piper<Adder>{
    constexpr int operator()(int x, int amount) const {
        return x + amount;
    }

    constexpr auto operator()(int amount) const {
        return static_cast<const Piper<Adder>*>(this)->operator()(amount);
    }
};
Adder adder;


int main(){
    using std::operator""s;

    std::vector v = {1, 2, 3, 4, 5};

    auto func = map([](int x){ return x * x; }) | fold(0);

    auto add3 = func() | adder(3);

    // std::clog << typeid(add3()).name() << std::endl;

    auto value = v | add3();

    
    std::cout << value << std::endl;


}