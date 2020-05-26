#include <cassert>
#include <iostream>

auto demo0()
{
	[](){}();
}

// define a function locally, with optional trailing return type

auto demo1()
{
	auto f = [](double x) -> double { return 2 * x + 1; };
	
	return f(3);
}

// capture with auto initializer

auto demo2()
{
	auto f = [m = 2, n = 1](double x) { return m * x + n; };
	
	return f(3);
}

// capture named values

auto demo3()
{
	auto m = 2, n = 1;

	auto f = [m,n](double x) { return m * x + n; };
	
	return f(3);
}

// capture all environment values by copy

auto demo4()
{
	auto m = 2, n = 1;

	auto f = [=](double x) { return m * x + n; };
	
	return f(3);
}

// mutating copied capture values

auto demo5()
{
	auto m = 0, n = 1;
	auto f = [=](double x) mutable { return ++m * x + n; };
	f(0);
	assert(m == 0);
	return f(3);
}

// capture by reference

auto demo6()
{
	auto m = 0, n = 1;
	auto f = [&](double x) { return ++m * x + n; };
	f(0);
	assert(m == 1);
	return f(3);
}

// return a lambda with templated parameter type

auto demo7()
{
	auto m = 2, n = 1;

	return [=](auto x) { return m * x + n; };
}

int main()
{
	std::cout << demo1() << '\n';
	std::cout << demo2() << '\n';
	std::cout << demo3() << '\n';
	std::cout << demo4() << '\n';
	std::cout << demo5() << '\n';
	std::cout << demo6() << '\n';
	std::cout << demo7()(3.0) << '\n';
}
