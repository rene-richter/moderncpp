# Ranges

A range `r`is a sequence of data, that has `begin(r)` and `end(r)`. Algorithms have simpler interfaces in C++20:

```cpp
std::sort(begin(r), end(r)); // < C++20
std::ranges::sort(r);        // C++20
```

The `<ranges>` library introduces „views“, i.e. small combinable blocks, that manipulate data items one by one as needed (lazy evaluation), see [example](../examples/ranges/ranges.cpp):

```cpp
using namespace std::ranges::views;
auto sequence = iota(0) | filter(is_prime) | drop(10) | take(3) | reverse| transform(square);
// no computation done up to here (lazy)

// squares of prime number No. 11, 12, 13 in reverse order
for (auto e : sequence) std::cout << e << ' ';
```



