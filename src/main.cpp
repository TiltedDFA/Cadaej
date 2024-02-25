#include <iostream>
#include "Types.hpp"
#include "Move.hpp"
int main(void)
{
    Move m(Square::A1, Square::A2);
    
    u64 val = 500;
    std::cout << "Hello world!\n" << val << '\n';
    return 0;
}