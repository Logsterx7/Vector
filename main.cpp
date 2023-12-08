#include "vector.hpp"

#include <format>
#include <iostream>

template <typename T>
void report(T& vector)
{
    std::cout << std::format("size    : {}\ncapacity: {}\nvalues  : ", vector.size(), vector.capacity());

    for (auto i = vector.begin(); i != vector.end(); i++)
    {
        std::cout << *i << ", ";
    }
    std::cout << std::endl;
}

// ------------------------------------------------------------------
//
// Final project, a vector with a bool specialization
//
// ------------------------------------------------------------------
int main()
{

    // Simple vector construction
    usu::vector<int> v1;
    usu::vector<int> v2(20);
    usu::vector v3{ 1, 2, 3, 5, 7, 11 };

    std::cout << "\n-- v1 --\n";
    report(v1);

    std::cout << "\n-- v2 --\n";
    report(v2);

    std::cout << "\n-- v3 --\n";
    report(v3);

    // Simple vector add/insert/remove
    v3.add(23);
    std::cout << "\n-- add --\n";
    report(v3);

    v3.insert(0, 13);
    std::cout << "\n-- insert at 0 --\n";
    report(v3);

    v3.insert(4, 17);
    std::cout << "\n-- insert at 4 --\n";
    report(v3);

    v3.insert(9, 19);
    std::cout << "\n-- insert at 9 --\n";
    report(v3);

    v3.remove(0);
    std::cout << "\n-- remove at 0 --\n";
    report(v3);

    v3.remove(3);
    std::cout << "\n-- remove at 3 --\n";
    report(v3);

    v3.remove(7);
    std::cout << "\n-- remove at 7 --\n";
    report(v3);

    // Insert until new capacity is required
    v3.insert(0, 29);
    v3.insert(0, 31);
    v3.insert(0, 37);
    std::cout << "\n-- maxed capacity --\n";
    report(v3);
    v3.insert(0, 41);
    std::cout << "\n-- updated capacity --\n";
    report(v3);

    return 0;
}
