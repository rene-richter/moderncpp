# Exercises

Design, create, and test C++ programs for these tasks.

1. Read a given number of integers from input stream,
   store them to a `std::vector<int>`,
   sort them using `std::sort()` in ascending order,
   print them to output.
   Show min and max values, compute their sum and average values.
	* Refactor `input()`,` sort()`, and `print()` as independent functions returning/taking `vector<int>`.
    * Let `input()` read an unknown number of values until end of input stream.
	* Store input data in a text file instead of typing them in repeatedly;
	  redirect the file to your program's input stream by command line.
    * Investigate which changes would be necessary to process floating point numbers of type `double`.
1. Read a (unknown) number of historical (dead) persons (name, born, died) into your program,
   store them as vector of persons. Use a redirected text file as input.
   Print all persons' data to output. Sort them
   * by name,
   * year of birth, and
   * age at time of dying and print them again after each sorting.
1. Implement the non-recursive algorithm for the greatest common divisor of integers in C++:
```
gcd(a,b): (assuming non-negative a,b)
while b is not 0:
	remainder = a modulo b
	a = b
	b = remainder
```
   (Use `a%b` as modulo operation.) 
   Implement also the recursive algorithm (Euclid of Alexandria 3rd century BCE)
```
gcd(a,b):
	b is 0 ==> a
	a < b ==> gcd(b,a)
	otherwise gcd(a-b,b)
```
   Write a test driver using `doctest.h` or
```cpp
#include <cassert>
assert(gcd(28,7) == 4);
assert(gcd(28,0) == 28);
assert(gcd( 0,7) == 7);
assert(gcd( 4,9) == 1);
```
4. Find all Pythagorean triples
   (positive integers a,b,c where`a*a + b*b` equals `c*c`)
   within range `0 < a,b,c < 500`.
   Print them in ascending order, no duplicates!
