#include <chrono>
#include <iostream>

int main()
{
	using Clock = std::chrono::high_resolution_clock;
	auto start = Clock::now();
	
	// something to measure ...
	for (int i = 0; i < 2'000'000'000; ++i)
	{
		if (0 == i % 100'000'000) std::cout << i << '\n';
	}
	
	auto end = Clock::now();
	auto diff = std::chrono::duration<double>{end - start};	
	std::cout << "duration = " << diff.count() << " seconds\n"; 	
}
