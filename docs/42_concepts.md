# Concepts and constraints

Since C++14 generalized parameters are possible:

```cpp
auto show = [](auto x) { std::cout << x << '\n'; }
```
To define the same as a function, you had to write a template:

```cpp
template <typename T> 
void show(T x) { std::cout << x << '\n'; }
```

C++20 now also allows unconstrained functions with auto parameters:

```cpp
void show(auto x) { std::cout << x << '\n'; } 
// Works at least for all types with defined operator<<;

auto add(auto x, auto y) { return x + y; } 
// requires defined operator+. 
```

What happens when the compiler tries to instantiate a template and some operations are not possible? Compiler error messages are not always readable, especially when some requirements are not met in a deeply nested template definition.

## Constraints

Parameter types should satisfy some requirements. If so, not valid instantiations can be removed from the overload set, reducing the load for the compiler to find a matching instance. This can reduce compile time and improve error messages. Previous techniques used std::enable_if<>, static_assert() and SFINAE to reach that goal.

### Template requirements

are predicates, evaluated at compile time. They constrain a template

```cpp
template <typename T> 
  requires std::is_integral_v<T> || std::is_floating_point_v<T> 
T add(T x, T y) { return x+y; }
```

Requirements can also follow after the parameter list. With a `concept` as a named requirement

```cpp
template <typename T> 
concept Number = std::is_integral_v<T> || std::is_floating_point_v<T>;
```

the example becomes

```cpp
template <typename T> 
  requires Number<T> 
T add(T x, T y) { return x+y; }
```

Besides template requires clauses there are „shorthand notation“ and „terse syntax“. 

### Shorthand notation

uses concept names instead of `typename`:

```cpp
template <Number T> 
T add(T x, T y) { return x+y; }
```

### Terse syntax
was heavily debated, lead to postponing Concept integration into the standard past C++17. It is now part of C++20:

```cpp
Number auto add(Number auto x, Number auto y) { return x+y; }
```

has slightly different meaning than the example before. It allows different types for parameters. Each parameter type is constrained independently. The return type can be any type, if it meets the requirements of the Number constraint. Furthermore, it's possible to constrain assignment to `auto` variables:

```cpp
	Number auto x = add(1, 2);
	Number auto y = add(1, 3.14);
	Number auto z = add(1, "3"); // error in calling add(): char* parameter is not a Number
	Number auto s = "Hello"; // error: char* is not a Number
```

## Defining concepts

Concepts are defined by logical combinations of requirements (see above) or a `requires` clause, containing 

* simple requirements like `x+y`, 
* type requirements like `typename T::value_type`, or 
* compound requirements, also constraining result type of operations

```cpp
template<typename T>
concept LessThanComparable = requires(T t) 
{ 
    { t<t } -> std::convertible_to<bool>; 
};
```

