/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>


template <typename T>
void print(T arr[], const int size){
    for(int i = 0; i < size; ++i)
        std::cout << arr[i] << '\n';
}


int main()
{
    std::string names[] = {"Ali", "Nawar", "Athena", "Goddes of Wisdom", "Pie"};
    int ages[] = {21, 20, 23, 1002, 3, 99, 41, };
    
    print(names, 5);
    std::puts("===============");
    print(ages, 7);
    

    return 0;
}
