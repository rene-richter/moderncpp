#include <iostream>
#include "arithmetic_sequence.hpp"
#include "geometric_sequence.hpp"

int main()
{
    auto odd = ArithmeticSequence{1,2};
    
    for (int i = 0; i < 10; ++i)
    {
        std::cout << odd.value() << ' ';
        odd.next();
    }
	std::cout << '\n';
	
    auto powers_of_2 = GeometricSequence{1,2};
    
    for (int i = 0; i < 10; ++i)
    {
        std::cout << powers_of_2.value() << ' ';
        powers_of_2.next();
    }
	std::cout << '\n';
}
