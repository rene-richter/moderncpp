# Functions
##  Declare before use
A _function header_
```cpp
int square(int x);
```
has to be _declared_ before a _function call_
```cpp
auto x = square(2);
```
Note that _definitions_ are also _declarations_:
A function is _defined_ by a function header followed by a _function body_:
```cpp
int square(int x) { return x*x; }
```
Define  a function exactly once in a program (ODR = one definition rule).
_Header files_ shall not contain function bodies, since they will be included into many compilation units and violate the ODR rule, except when these functions are marked as `inline`:
```cpp
inline int square(int x) { return x*x; }
```
Then the function body is required to be seen in the header.
(Remark: The `inline` mark was originally intended as a hint to the compiler not to call the function, but to insert the function body statements inside the caller. It can save some machine code for the function call frame, especially for small functions with few statements. Today the optimizer makes a fairly good job. If in doubt, measure the effect, e.g. in https://godbolt.org or with a profiler.)

## Default parameter values
Default values given in declaration are used, when the function is called with fewer arguments:
```cpp
int volume(int x, int y=1, int z=1);

auto two = volume(2);
auto six = volume(2,3);
auto twelve = volume(2,3,4);
```
Default values are not to repeat in the function definition (except when it is also the first declaration)
```cpp
int volume(int x, int y, int z)
{
    return x*y*z;
}
```
Exercise (experiment with source code):
- What if multiple declarations contradict?
- In which order are default values used?

## Overloaded parameter list
Functions with different parameter lists  can share the same name (_overloaded_ function):
```cpp
int square(int x) { return x*x; }
double square(double x) { return x*x; }

auto i = square(2);
auto d = square(3.14);
```
Exercise:
- Which functions are considered as candidates in the overload set?
- When does parameter list match?
- What happens if not?
- What if more than one candidate matches?

Rules are given in https://en.cppreference.com/w/cpp/language/overload_resolution
(caveat: may be too much for beginners; it's suspected to require Scott Meyers' [haircut](http://scottmeyers.blogspot.com/2014/09/cppcon-hair-poll.html?m=1) to grasp them all).

## Return type
* A function header starts with a _return type_ (see above).
  It has to match the type of the returned value.
* `void` functions (called _procedures_ or _subroutines_ in other languages) do not return a value, but can contain a `return` statement (without a return value).
* `auto` return type deduction can be utilized since C++14: The compiler knows the type of the return value and therefore the return type of the function. This feature is especially useful for type names too complicated, or only known to the compiler.
