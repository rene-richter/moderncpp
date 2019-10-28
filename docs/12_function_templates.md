# Function templates
_Generic programming_ (or _compile time polymorphism_) allows to abstract from concrete data types.
The types of parameters are themselves _type parameters_ to a _template_:
```cpp
template <typename T>
auto square(T x) { return x*x; }

auto i = square(1);
auto d = square(3.14);
auto d2 = square<double>(2); // explicit call for double instead of int
```
The matching function is generated by the compiler at the function call.
(Therefore the templated function has to have a function body also in header files.)

## Specialisations
A concrete function definition
```cpp
auto square(char x) { return std::string(2, x); }

auto s = square('d');´
```
overrules the template for special type parameters.

Exercise:
* When does a function template match a function call?
* Find situations when the compiler can't find a type match.
* Experiment with a function `min(a,b)` returning the minimum of two given values.
  What if `a` and `b` have different types?