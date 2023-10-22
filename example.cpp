#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

#include "Piper.hpp"


struct Fold : Piper<Fold>{
    template<std::ranges::range V, typename INIT = int, std::invocable<INIT, std::ranges::range_value_t<V>> OP = decltype(std::plus{})>
    constexpr INIT operator()(V&& v, INIT init = 0, OP func = std::plus{}) const {
        for(auto&& elt : v)
            init = func(init, std::forward<decltype(elt)>(elt));

        return init;
    }

    template<typename INIT = int, typename OP = decltype(std::plus{})>
    constexpr auto operator()(INIT init = 0, OP func = std::plus{}) const {
        return static_cast<const Piper*>(this)->operator()(init, func);
    }
};
Fold fold;


struct Map : Piper<Map>{
    template<std::ranges::range V, std::invocable<std::ranges::range_value_t<V>> OP>
    constexpr auto operator()(V&& v, OP func) const {
        // std::vector<std::invoke_result_t<OP, std::ranges::range_value_t<V>>> result;
        std::remove_cvref_t<V> result;
        // result.reserve(std::ranges::size(v));

        for(auto&& elt : v)
            result.push_back(func(std::forward<decltype(elt)>(elt)));

        return result;
    }
    
    constexpr auto operator()(auto func) const {
        return static_cast<const Piper*>(this)->operator()(func);
    }
};
Map map;


struct Filter : Piper<Filter>{
    
    template <std::ranges::range V, std::invocable<std::ranges::range_value_t<V>> OP>
    constexpr auto operator()(V v, OP func) const {
        std::remove_cvref_t<V> v2;

        for(auto&& n : v)
            if(func(n))
                v2.push_back(n);
            

        return v2;
    }

    constexpr auto operator()(auto func) const {
        return static_cast<const Piper*>(this)->operator()(func);
    }
};
Filter filter;



struct Slice : Piper<Slice>{

    std::string_view operator()(std::string_view sv, int start, int end) const {
        return sv.substr(start, end - start);
    }


    auto operator()(int start, int end){
        return static_cast<const Piper*>(this)->operator()(start, end);
    }
};
Slice slicer;


struct FirstName : Piper<FirstName> {

    std::string operator()(std::string sv) const {
        return sv.substr(0, sv.find(' '));
    }

    auto operator()(){
        return static_cast<const Piper*>(this)->operator()();
    }
};
FirstName firstName;


struct Encrypt : Piper<Encrypt> {

    std::string operator()(std::string sv, int shift) const {
        std::clog << "Shifting by: " << int(shift) << '\n';
        for(auto& c : sv)
            // c = (c + shift) % 26;
            // c = (c + shift) % 26 + 'a';
            if(isalpha(c)) c = ((c - 'a' + ((shift % 26) + 26)) % 26) + 'a';

        return sv;
    }

    auto operator()(int shift){
        std::clog << "Shifting2 by: " << shift << '\n';
        return static_cast<const Piper*>(this)->operator()(shift);
    }

};
Encrypt encrypt;

int main(){
    std::vector v = {1, 2, 3, 4, 5};
    // std::string name = "Jason Turner";

    std::cout << (v | fold(0)) << '\n';

    // auto to_small = map([](auto c){ return std::tolower(c); });

    // std::cout << encrypt(to_small(name), 3) << '\n';
    // std::cout << (name | to_small | encrypt(3)) << '\n';

    // std::cout << encrypt(encrypt(to_small(name), 3), -3) << '\n';
    // std::cout << (name | to_small | encrypt(3) | encrypt(-17)) << '\n';
    // std::cout << (name | to_small | encrypt(1) | encrypt(-15)) << '\n';
}