# Function template exercises (Q&A)

Q:
A set of overloaded functions
```cpp
int  min(int a, int b);
char min(char a, char b);
```
(same for `double`, `std::string`, ...) is needed.
Follow the DRY principle: Don't repeat yourself.

A:
Write a generalized function, a _template_ for a generic function

```cpp
template <typename T>
T min(T a, T b)
{
	return b < a ? b : a;
}
```

Q:
Why would
```cpp
	return a < b ? a : b;
```
be wrong?

A:
...


Q:
Suppose you define

```cpp
struct Rectangle { int x, y, width, height; };
```
Would the templated function `min()` work?

A:
Doesn't compile:
```
error ...: operator< not found ...
```

Q:
Which options do you have to resolve that?

A:
a) Provide an `operator<` for type `Rectangle`:

```cpp
bool operator<(Rectangle r1, Rectangle r2)
{
	return area(r1) < area(r2);
}
```

b) Specialize `min()` for `Rectangle`

```cpp
Rectangle min(Rectangle r1, Rectangle r2)
{
	return area(r2) < area(r1) ? r2 : r1;
}
```

c) Generalize the function template for any possible comparation (like in [cpprereference: std::min()](https://en.cppreference.com/w/cpp/algorithm/min )).

A comparator function has to be a predefined function or a lambda expression taking two parameters and returning a `bool` value (called a _binary predicate_ in math):

```cpp
template <typename T, typename BinaryPred>
T min(T a, T b, BinaryPred compare)
{
	return compare(b,a) ? b : a;
}

Rectangle r1, r2;
auto m1 = min(r1, r2, smaller_area);
auto m2 = min(r1, r2, [](auto r1, auto r2) { return r1.x < r2.x; });
```
Note: Functions (and lambdas) also are (complicated) types.

Q:
Which role plays the keyword `auto` instead of `Rectangle` in the
parameter list of the lambda expression?

A:
...

Q:
Do you understand the following code? What are the results?

```cpp
template <typename T, typename BinaryPred, typename UnaryFn>
T min(T a, T b, BinaryPred compare, UnaryFn proj)
{
	return compare(proj(b),proj(a)) ? b : a;
}

auto m3 = min(r1, r2, std::less<>{}, area);
auto m4 = min(r1, r2, std::less<>{}, [](auto r) { return r.x; });
```
Hints:
* `std::less<>{}` creates an `<utility>` object comparing two thingys by `operator<(a,b)`.
* In databases, considering (some) columns of a table is called a projection.

A:
...

Q:
Why can't we have both function templates in the same codebase:

```cpp
template <typename T, typename UnaryFn>
T min(T a, T b, UnaryFn proj)
{
	return proj(b) < proj(a) ? b : a;
}

template <typename T, typename BinaryPred>
T min(T a, T b, BinaryPred compare)
{
	return compare(b,a) ? b : a;
}
```
A:
...

Note: This could be resolved by C++20 template constraints (concepts).

