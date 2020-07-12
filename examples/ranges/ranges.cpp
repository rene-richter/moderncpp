#include <iostream>
#include <ranges>

auto is_prime(int n)
{
	if (n < 2) return false;
	if (n == 2) return true;
	for (int t = 3; t < n; t += 2)
		if (n % t == 0) return false;
		
	return true;
};

int main()
{
	auto square = [](int x) { return x*x; };
	
	using namespace std::ranges::views;
	auto sequence = iota(0) | filter(is_prime) | drop(10) | take(3) | reverse| transform(square);
	// no computation done up to here (lazy)

	// squares of prime number No. 11, 12, 13 in reverse order
	for (auto e : sequence) std::cout << e << ' ';
}
