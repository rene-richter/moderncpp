#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <list>

auto random_sequence(size_t size)
{
	auto seq = std::list<int>(size);

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(1,size);

	std::generate(begin(seq), end(seq), 
		[&]() { return distribution(generator); }
	);
	return seq;	
}

int main()
{
	size_t size = 10;
	
	while (size < 1'000'000'000)
	{
		auto seq = random_sequence(size);
		auto start = std::chrono::system_clock::now();
        
		seq.sort();
		// std::sort(begin(seq), end(seq));
		
		auto end = std::chrono::system_clock::now();
		auto diff = std::chrono::duration<double>(end-start);
		std::cout << "Time to sort a list of " 
				  << seq.size() << " ints : " << diff.count() << " s\n";
	
		size *= 10;
	}
}
