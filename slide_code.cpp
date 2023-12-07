#include <string_view>
#include <iostream>
#include <tuple>



template <typename Derived> class Piper;

struct Slice;

template <typename T, typename...Args>
struct Package{
    T* obj;
    std::tuple<Args...> args;
};


template <typename Derived>
class Piper{

public:
    template <typename... Args>
    Package<Derived, Args...> make_package(Args... args) const{
        return {static_cast<const Derived*>(this), {args...}};
    }
};

    // Package make_package(int s, int e) const{
    //     return {static_cast<const Derived*>(this), {s, e}};
    // }

void slicer(int, int);
void slicer(std::string, int, int);


int main(){

    "Jason Turner" | slicer(0, 5);

    slicer("Jason Turner", 0, 5);

}


// struct Package{
//     Slice* obj;
//     std::tuple<int, int> args;
// };


struct Slice : Piper<Slice>{

    auto operator()(std::string_view sv, int start, int end) const {
        return sv.substr(start, end - start);
    }

    auto operator()(int start, int end){
        return static_cast<const Piper<Slice>*>(this)->operator()(start, end);
    }
};


auto operator|(std::string_view sv, auto args){
    return p.obj->operator()(sv, std::get<0>(args.args), std::get<1>(args.args));
}


auto operator|(std::string_view sv, std::tuple<int, int> args){

}

template <template <typename...> typename P, typename... Types>
auto operator|(auto lhs, P<>){
    // return p.obj->operator()(sv, std::get<0>(p.args), std::get<1>(p.args));
}

template <typename T>
concept Packaged = requires(T t){
    t.derived; t.args;
};


template <size_t... Is>
auto piperHelpr(std::index_sequence<Is...>, Packaged auto p, auto v){
    return p.derived->operator()(v, std::get<Is>(p.args)...);
}



auto operator|(auto v, Packaged auto p){
    auto size = std::tuple_size<decltype(p.args)>{};
    return piperHelpr(std::make_index_sequence<size>{}, p, v);
}

bool isEven(int i){
    return i % 2 == 0;
}

int doubleIt(int i){
    return i * 2;
}

void main(){
    std::vector v = {1,2,3,4,5};
    v | filter(isEven) | map(doubleIt) | fold(0, std::plus{});
    fold(map(doubleIt), 0, std::plus{});
    auto mapFold = map(doubleIt) | fold(0, std::plus{});
    auto filterMapFold = filter(isEven) | mapFold;
    v | filterMapFold;
}


template <typename F1, typename F2>
class Composer : Piper<Composer> {
    F1 f1;
    F2 f2;

    Composer(F1_f1, F2 _f2)
    : f1{_f1}, f2{_f2} {}

    auto operator()(auto t) const {
        return f2(f1(t));
    }

    template <typename... Types>
    auto operator()(Types... params) const { // returns a package to invoke |
        return static_cast<const Piper<Composed<P1, P2>>*>(this)->make_package(params...);
    }
};

template <Packaged P1, Packaged P2>
struct Composed : Piper<Composed<P1, P2>>{
    P1 p1;
    P2 p2;

    template <Packaged P1_, Packaged P2_>
    constexpr Composed(P1_&& f1, P2_&& f2) : p1(std::forward<P1>(f1)), p2(std::forward<P2>(f2)){}

    template <typename T>
    inline constexpr auto operator()(T&& v) const { // regular syntax
        auto size1 = std::tuple_size<decltype(p1.args)>{};
        auto size2 = std::tuple_size<decltype(p2.args)>{};

        auto Is1 = std::make_index_sequence<size1>{};
        auto Is2 = std::make_index_sequence<size2>{};

        return piperHelpr(Is2, p2, piperHelpr(Is1, p1, std::forward<T>(v)));
    }

    template <typename... Types>
    [[nodiscard]] inline constexpr auto operator()(Types&&... params) const { // returns a package to invoke |
        return static_cast<const Piper<Composed<P1, P2>>*>(this)->make_package(std::forward<Types>(params)...);
    }

};