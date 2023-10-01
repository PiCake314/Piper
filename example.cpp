#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>

#include "Piper.hpp"

struct Fold : Piper<Fold>{
    template<std::ranges::range V, typename INIT, std::invocable<INIT, std::ranges::range_value_t<V>> OP = decltype(std::plus{})>
    INIT operator()(V&& v, INIT init, OP func = std::plus{}) const {
        for(auto&& elt : v)
            init = func(init, std::forward<decltype(elt)>(elt));

        return init;
    }
    
    template<typename INIT, typename OP = decltype(std::plus{})>
    auto operator()(INIT&& init, OP&& func = std::plus{}) const{
        return static_cast<const Piper<Fold>*>(this)->operator()(std::forward<INIT>(init), std::forward<OP>(func));
    }
};
Fold fold;


struct Slice : Piper<Slice>{

    std::string_view operator()(std::string_view sv, size_t start, size_t end) const{
        std::clog << "Start: " << start << '\n';
        std::clog << "End: " << end << '\n';
        return sv.substr(start, end - start);
    }

    constexpr auto operator()(size_t start, size_t end) const{
        return static_cast<const Piper<Slice>*>(this)->operator()(start, end);
    }
};
Slice slice;


int main(){
    using std::operator""s;
    std::vector v = {1, 2, 3, 4, 5};
    auto s = "Hello World"s;


    // auto value = fold(v, 0);
    // auto value = v | fold(0);
    // auto value = slice(s, 1, 4);
    auto value = s | slice(1, 4);

    std::cout << value << std::endl;

    // std::cout << unhash << std::endl;

}