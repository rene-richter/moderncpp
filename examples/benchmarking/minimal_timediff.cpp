#include <chrono>
#include <iostream>

int main()
{
	using Clock = std::chrono::high_resolution_clock;
	using namespace std::chrono_literals;
	auto zero = 0ns;
	auto min_diff = 1000000ns;
	
	// something to measure ...
	for (int i = 0; i < 1'000'000'000; ++i)
	{
		auto start = Clock::now();
		if (0 == i % 100'000'000) std::cout << i << '\n';
		auto end = Clock::now();

		auto diff = end - start;
		if (zero < diff && diff < min_diff) min_diff = diff;
	}

	std::cout << "clock resolution = " << min_diff.count() << " nanoseconds\n"; 	
}
