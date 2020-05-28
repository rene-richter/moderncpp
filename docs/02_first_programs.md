# 02 First useful (?) programs and fundamental ideas
## Input-Process-Output pattern
Example 1:
```cpp
#include <iostream>

int main()
{
    int value;
    std::cin >> value;
    value *= 3;
    std::cout << value << '\n';
}
```
Useful programs have to `#include` some stuff from library "headers", e.g. how to input / output data streams to `cin`= console input / `cout`= console output.

Example 2: Even if you don't know C++ yet, you can try to understand its source code.
```cpp
#include <iostream>
#include <map>
#include <string>

int main()
{
    std::map<std::string, int> table;
    std::string word;
    while (std::cin >> word)
    {
        table[word]++;
    }
    for (auto const [word, count] : table)
    {
        std::cout << word << '\t' << count << '\n';
    }
}
```
Exercise:
* How to compile the code on your platform?
* How to start the executable?
* How to input data (a text file) to it?
* How to end keyboard input to a running program on your platform?
* What does this program do / send to output?
* What are braces `{ }` for?
* Why are some text lines indented?
* Do you know about iteration of code sequences?

## Variable
has to be declared / defined before use, typically has
* a name (a scope, a lifetime, a location in memory, i.e. an address)
* a value (from a set of possible values), which can change at runtime
    -- otherwise it's called a `const` variable,
* a type (which operations are allowed, how much memory does it need).

Literal values and temporary objects like return values do not need a name:

```cpp
int main() { return 6*7; }
// I have no idea, how your operating system will react to that error code...
```

## Name

A name consists of letters `A-Z`, `a-z` and digits `0-9` (not at the beginning).
Underscores `_` are allowed, `_leading __underscores` are typically reserved for implementation details (beware of possible name clashes).
Some names are reserved (keywords) like `auto`, `const`, `for`, and `while`.
C++ is case-sensitive: `Robot` and `robot` are different names,
The `camelCasing`, `PascalCasing`, `snake_casing`, and `YELLING` styles have different applications.

Advice for beginners:
* Choose names that make your intent clear (naming is hard).
* Avoid names with small cognitive distance, e.g. the characters `I`, `l`, and `1` look very much the same in most editor fonts.

## Type
A type defines
* a set of possible values,
* which operations are allowed for a value,
* how much space is needed to store it,
* how the bitwise representation of the value is interpreted.

For a start we need
* boolean values for logic,
* integer numbers and floating-point numbers (in double precision) for math,
* characters and strings of characters for text processing.

Some *containers* like
* `std::vector<T>` (a dynamic array of objects of some type `T`) and
* `std::map<Key,Value>` (a sorted table of key-value pairs, a.k.a. dictionary in other languages)

help organize lots of data.

C++ is a strongly typed language. The type of a variable is known at compile time. (We don't look into runtime polymorphism at this point.)

## Initial value
(Local) variables of fundamental types should be initialized, i.e. assigned a value at definition.

```cpp
bool     b { true || false }; // but not both at the same time
int        i { 0b00101010 };        // binary 0b0010'1010 == decimal 42
double d { 2.99792458e8 };    // speed of light in meters per second
                                                        // __e8 == __ multiplied by 100'000'000
                                                        // ' can be used as digit separator (since C++14)
char     c { '*' };                     // character must be surrounded by '
```

Otherwise they contain unknown garbage values.
Modern C++ compilers are able to detect the type of variables automatically from the assigned value:
```cpp
auto x { 42 };            // int
auto r { "Hello" }; // refers to an array of 6 char constants,
                                        // is not a std::string!
```
Other types are defined in namespace `std` of the C++ standard library :
```cpp
#include <map>
#include <string>
std::map<std::string,int> table; // empty table of string-integer pairs
std::string s1;                                    // empty string of characters
std::string s2 { "Hello" };            // string of 5 characters
```
A suffix to a constant literal can hint to some type:
```cpp
using std::literals;
auto s3 { "Hello"s };                    // std::string
auto t1 { 10s };                             // 10 seconds
auto t2 { 1min + 28s + 73ms }; // std::chrono::duration
auto z    { 3.0 + 2.0i };                // std::complex number
```
## Operator
* known from math: assign a value with `x=2`, add two values `1+2`,
* familiar from C-like languages like `i*=3` (multiply i by 3 and store the result in `i`), corresponding to assembler instructions like `MUL AX,3`
* reused in C++ with different meaning: get/send data from/to console with `>>` and `<<` shifting operators
* sometimes impossible to grasp for beginners

See statement `table[word]++` in Example 2:
    * `table[word]` looks for the word in the (ASCIIbetically sorted) key column of the table and
    * inserts a line with the word and an initial integer value 0, if the word is not found,
    * then `++` increments the associated number by 1.
