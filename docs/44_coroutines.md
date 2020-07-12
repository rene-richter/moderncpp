# Coroutines

Coroutines contain a keyword `co_yield`, `co_return`or `co_await`.

Functions compute a value and return it. 
A coroutine can deliver (yield) a value, suspend its work, and resume (continue its work) at the same position, when reactivated:

```cpp
#include <experimental/generator> // MS VC++ /await /std=c++latest
#include <iostream>
#include <numeric>
#include <tuple>

using Triple = std::tuple<int, int, int>;
using namespace std::experimental;

generator<Triple> pythagorean_triples(int limit)
{
    for (auto z = 1; z < limit; ++z)
        for (auto y = 1; y < z; ++y)
            for (auto x = 1; x < y; ++x)
                if (x * x + y * y == z * z)
                {
                    std::cout << '\t' << x << ' ' << y << ' ' << z << '\n';
                    co_yield {x, y, z};
                }
}

generator<Triple> irreducible_pythagorean_triples(int limit)
{
    for (auto [x, y, z] : pythagorean_triples(limit))
        if (std::gcd(x, z) == 1 && std::gcd(y, z) == 1)
            co_yield {x, y, z};
}

int main()
{
    std::cout << "\tpythagorean triple\nirreducible\n";

    for (auto [x, y, z] : irreducible_pythagorean_triples(30))
        std::cout << x << ' ' << y << ' ' << z << '\n';
}
```

The output illustrates, how these two coroutines interact:

```txt
	pythagorean triple
irreducible
	3 4 5
3 4 5
	6 8 10
	5 12 13
5 12 13
	9 12 15
	8 15 17
8 15 17
	12 16 20
	15 20 25
	7 24 25
7 24 25
	10 24 26
	20 21 29
20 21 29
```

Like `std::views::iota(1)`, coroutines can act as generators. 
Unfortunately, generators are not standardized yet. 
At the moment (July 2020), generators are experimental in Visual C++. 
They will combine well with [`<ranges>`](41_ranges.md), when implemented. 
Lewis Baker's library [cppcoro](https://github.com/lewissbaker/cppcoro) also provides this facility.

