#include <iostream>
#include <ranges>
#include <numeric>
#include <algorithm>
#include <vector>

#include "Piper.hpp"

struct Fold : Piper<Fold>{
    template<std::ranges::range V, typename INIT, std::invocable<INIT, std::decay_t<std::ranges::range_value_t<V>>> OP = decltype(std::plus{})>
    INIT operator()(V &&v, INIT init, OP func = std::plus{}) const {
        for(auto&& elt : v)
            init = func(init, elt);

        return init;
    }
    
    template<typename INIT, typename OP = decltype(std::plus{})>
    auto operator()(INIT init, OP func = std::plus{}) const{
        return Piper<Fold>::operator()<INIT, OP>(init, func);
    }
};

int main(){
    using std::operator""s;

    std::vector v = {3, 14, 1, 5, 9, 2, 6, 5, 3, 5};

    Fold fold;

    // auto res_call = fold(v, 0, [](int acc, int elt) -> int { return acc + elt; }); // this works

    // auto res_pipe = v | fold(""s, [](std::string acc, int elt) -> std::string { return acc + std::to_string(elt); }); // this works

    // std::cout << res_call << '\n';
    // std::cout << res_pipe << '\n';

    auto res = v | std::ranges::views::filter([](int x){ return x % 2 == 0; })
                 | std::ranges::views::transform([](int x){ return x * x; })
                 | fold(1, std::multiplies{});
    
    auto res2 = fold(std::ranges::views::transform(std::ranges::views::filter(v, [](int x){ return x % 2 == 0; }), [](int x){ return x * x; }), 1, std::multiplies{}); // this works



    // C++23 equivalent
    // auto res3 = v | std::ranges::views::filter([](int x){ return x % 2 == 0; })
    //              | std::ranges::views::transform([](int x){ return x * x; })
    //              | std::ranges::fold_left(1, std::multiplies{});
    
    // auto res4 = std::ranges::fold_left(std::ranges::views::transform(std::ranges::views::filter(v, [](int x){ return x % 2 == 0; }), [](int x){ return x * x; }), 1, std::multiplies{}); // this works




    std::cout << res << '\n';
    std::cout << res2 << '\n';
    // std::cout << res3 << '\n';
    // std::cout << res4 << '\n';

    return 0;
}