#include <iostream>

#include "Piper.hpp"

struct Fold : Piper<Fold>{
    template<container V, typename INIT, std::invocable<INIT, typename V::value_type> OP>
    INIT operator()(const V &v, INIT init, OP func) const {
        for(const auto &elt : v)
            init = func(init, elt);

        return init;
    }
    
    template<typename INIT, typename OP>
    auto operator()(INIT init, OP func) const{
        return Piper<Fold>::operator()<INIT, OP>(init, func);
    }
};


int main(){
    using std::operator""s;

    std::vector v = {3, 14, 1, 5, 9, 2, 6, 5, 3, 5};

    Fold fold;

    auto res_call = fold(v, 0, [](int acc, int elt) -> int { return acc + elt; }); // this works

    auto res_pipe = v | fold(""s, [](std::string acc, int elt) -> std::string { return acc + std::to_string(elt); }); // this works

    std::cout << res_call << '\n';
    std::cout << res_pipe << '\n';

    return 0;
}