#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <string>
#include <numeric>
#include <string_view>
#include <ranges>

#include "Piper.hpp"


struct Fold : Piper<Fold>{

    using Piper<Fold>::operator();

    template<std::ranges::range V, typename INIT = int, std::invocable<INIT, std::ranges::range_value_t<V>> OP = decltype(std::plus{})>
    constexpr INIT operator()(V&& v, INIT init = 0, OP func = std::plus{}) const {
        for(auto&& elt : v)
            init = func(init, std::forward<decltype(elt)>(elt));

        return init;
    }

    // template<typename INIT = int, typename OP = decltype(std::plus{})>
    // constexpr auto operator()(INIT init = 0, OP func = std::plus{}) const {
    //     return static_cast<const Piper*>(this)->make_package(init, func);
    // }
};
Fold fold;


struct Map : Piper<Map>{

    using Piper<Map>::operator();

    template<std::ranges::range V, std::invocable<std::ranges::range_value_t<V>> OP>
    constexpr auto operator()(V&& v, OP func) const {
        // std::vector<std::invoke_result_t<OP, std::ranges::range_value_t<V>>> result;
        std::remove_cvref_t<V> result;
        // result.reserve(std::ranges::size(v));
        std::back_insert_iterator<std::remove_cvref_t<V>> it(result);

        for(auto&& elt : v)
            // simialr to *it++
            it = func(std::forward<decltype(elt)>(elt));

        // for(auto&& elt : v)
        //     result.push_back(func(std::forward<decltype(elt)>(elt)));

        return result;
    }
};
Map map;


struct Filter : Piper<Filter>{

    using Piper<Filter>::operator();
    
    template <std::ranges::range V, std::invocable<std::ranges::range_value_t<V>> OP>
    constexpr auto operator()(V v, OP func) const {
        // std::remove_cvref_t<V> v2;
        V v2;
        auto insert = std::back_inserter(v2);

        for(auto&& n : v)
            if(func(n))
                insert = n; // similar to *insert++ = n;

        return v2;
    }
};
Filter filter;



// struct Slice : Piper<Slice>{

//     constexpr std::string operator()(std::string sv, int start, int end) const {
//         return sv.substr(start, end - start);
//     }


//     auto operator()(int start, int end) const {
//         return static_cast<const Piper*>(this)->make_package(start, end);
//     }
// };
// Slice slicer;


// struct Adder : Piper<Adder>{
//     constexpr int operator()(int a, int b) const {
//         return a + b;
//     }

//     constexpr auto operator()(int x) const {
//         return static_cast<const Piper*>(this)->make_package(x);
//     }
// };
// Adder adder;


// struct VoidS : Piper<VoidS> {

//     auto operator()(std::string_view sv) const {
//         std::cout << sv;
//     }

//     auto operator()()const {
//         return static_cast<const Piper<VoidS>*> (this)->make_package();
//     }
// };
// VoidS voider;

// struct Multiplier : Piper<Multiplier>{
//     constexpr int operator()(int a, int b) const {
//         return a * b;
//     }

//     constexpr auto operator()(int x) const {
//         return static_cast<const Piper*>(this)->make_package(x);
//     }
// };
// Multiplier multiplier;



using namespace std::string_literals;

int main(){

    // example 1
    // std::string name = "Ali Almutawa";

    // auto first3 = slicer(0, 3);
    // auto capitalize = map([](auto&& s){ return std::toupper(s); });

    // auto capFirst3 = capitalize | first3;
    // std::cout << (name | capFirst3()) << '\n';

    // voider("Hello!");
    // "Hello!" | voider();

    // example 2
    // std::vector vec = {1, 2, 3, 4, 5};
    // auto even = filter([](auto n){ return n % 2 == 0; });
    // auto doubleIt = map([](auto n){ return n * 2; });
    // auto doubleEvensSum = even | doubleIt | fold;

    // std::cout << (vec | doubleEvensSum) << '\n';



    // return std::accumulate(std::begin(vec), std::end(vec), 10, [](auto a, auto b){ return a + b * 2; });
    // return fold(vec, 10, [](auto a, auto b){ return a + b * 2; });


    // example 3
    // int x = 10;
    // int y = 20;
    // auto adderX = adder(x);

    // int z = adder(x, y);
    // int z2 = adderX(y);
    // int z3 = y | adder(x);
    // int z4 = y | adderX();
    // int z5 = y | adderX;

    // std::cout << z << ' ' << z2 << ' ' << z3 << ' ' << z4 << ' ' << z5 << '\n';

    // auto multY = multiplier(y);

    // int res = z | adderX | multY;
    // std::cout << res << '\n';

    std::vector vec = {1, 2, 3, 4, 5};
    auto sum = vec | map([](auto x){ return x * 3; }) | filter([](auto x){ return x & 1; }) | fold(2);
    std::cout << sum << '\n';


}