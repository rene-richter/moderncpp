# Lambda expressions

Lambda expressions (short: lambdas) are anonymous functions, more exactly: 
[function objects](35_overloading_operators.md#Function-objects) or 
[closures](https://en.wikipedia.org/wiki/Closure_(computer_programming)). 
[Lambda calculus](https://en.wikipedia.org/wiki/Lambda_calculus), a formal system developed in the 1930s, is the theoretical foundation of functional programming. 

## Defining lambdas

```cpp
auto square = [](auto x){ return x*x; };
```

defines a variable of an anonymous, unique, but unknown compiler-generated type. Therefore `auto`in front of `square` is necessary. 

## Calling lambdas

A named lambda behaves like / is a function:

```cpp
std::cout << square(5);   // 25
std::cout << square(1.2); // 1.44
```
Lambda calls with `auto` parameters are implemented as templates.

## Immediately invoked lambda expressions (IILE)

can initialize values requiring complex computations: 

```cpp
const auto squares =
	[](int n)
	{
		std::vector<int> v;
		for (int i = 0; i <= n; ++i) v.push_back(square(i)); 
		return v;
	}(10);
```

Naming the lambda is not necessary. Call it immediately. Just add a function call with parameters following the lambda expression. 

Fun question: What does `[]{}();` mean? Hint: Parentheses between `[]` and function body `{}` are optional and can be omitted for lambdas without parameters. 

## Lambdas as callbacks in standard algorithms

Lambda definitions are allowed inside functions, locally. Some standard algorithms expect helper functions:

```cpp
auto lambda_as_callback(std::vector<int> v)
{
	auto between = [](int x) { return 10 < x && x < 40; }
	return std::count_if(begin(v), end(v), between);
}

auto define_callback_in_place(std::vector<int> v)
{
	return std::count_if(begin(v), end(v), 
		[](int x) { return 10 < x && x < 40; }
	);
}
```

Defining the lambda in place improves locality of code. There is no need to define a function or function object elsewhere, no need to lookup where its definition is located in the codebase. Compilers can inline and optimize the generated code.

## Closure: capture state easily

The *capture list* `[]` at the start of the lambda expression initializes values stored inside the function object:  

```cpp
[min = 10, max = 40](int x) { return min < x && x < max; }
```

A lambda can capture values of variables existing in the scope

```cpp
auto min = 10, max = 40;
```

explicitly by name

```cpp
[min, max](int x) { return min < x && x < max; }
```

or all (used) names by copy

```cpp
[=](int x) { return min < x && x < max; }
```

or by reference

```cpp
[&](int x) { return min < x && x < max; }
```

Beware: Don’t risk dangling references! References should outlive the lambda expression. Captured values are immutable except when the lambda is marked as `mutable`:

```cpp
std::for_each(begin(v), end(v),
	[count = 0](auto x) mutable
	{
		std::cout << count++ << ' ' << x << '\n';		 
	}
);
```

## Higher order functions

Take function (objects) as parameters and/or return function objects as result. Functional programming utilizes a lot of *higher order functions* like `map()`, `filter()` and `reduce()`. Google patented [MapReduce](https://en.wikipedia.org/wiki/MapReduce) as a parallel, distributed programming model.

To some extent C++ standard library algorithm templates are “second order” functions. They utilize functions as callbacks (but do not return function objects):

```cpp
#include <numeric>

auto max_string_length(std::vector<std::string> const& v)
{
	return std::transform_reduce(begin(v), end(v)), 0,
		[](auto x, auto y) { return std::max(x,y); },
		[](auto s){ return s.size(); }
	);
}
```

Don’t stop here.

Lambdas (or other function objects) are perfectly valid parameters

```cpp
auto call_twice = [](auto f, auto x) { return f(f(x)); };

std::cout << call_twice(square, 3); // 81 
```

and return values

```cpp
auto compose = [](auto f, auto g)
	{
		return [](auto x) { return g(f(x)); };
	};

auto answer = compose(
	square,
	[](auto x) { return x + 17; }		
)(5); // 5*5 + 17 == 42
```

In lambda calculus there is no limit...