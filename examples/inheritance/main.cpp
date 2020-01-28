#include <iostream>
#include "arithmetic_sequence.hpp"
#include "geometric_sequence.hpp"

auto run(Sequence& s)
{
    for (int i = 0; i < 10; ++i)
    {
        std::cout << s.value() << ' ';
        s.next();
    }
	std::cout << '\n';
}

int main()
{
    auto a = ArithmeticSequence{1,2};
    auto g = GeometricSequence{1,2};
 
	run(a);
	run(g);
 }
