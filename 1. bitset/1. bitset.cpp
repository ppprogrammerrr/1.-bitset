#include <iostream>
#include "bitset.h"

void print(bitset& b) {
    for (int i = 0; i < b.size(); i++) {
        std::cout << b[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{

    bitset b(10);
    print(b);
    b.set(5, 1);
    print(b);
    std::cout << b.size() / 8 << std::endl;
    b.set(20, 1);
    print(b);
    std::cout << b.size() / 8;
}

