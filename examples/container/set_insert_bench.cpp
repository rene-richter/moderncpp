#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <set>

auto random_sequence(size_t size)
{
	auto seq = std::multiset<int>();

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(1,size);
	
	for (size_t i=0; i < size; ++i)
		seq.insert(distribution(generator));

	return seq;	
}

int main()
{
	size_t size = 10;
	
	while (size < 1'000'000'000)
	{
		auto start = std::chrono::system_clock::now();
        		
		auto seq = random_sequence(size);
		
		auto end = std::chrono::system_clock::now();
		auto diff = std::chrono::duration<double>(end-start);
        std::cout << "Time to create a sorted multiset of " 
                  << seq.size() << " ints : " << diff.count() << " s\n";
	
		size *= 10;
	}
}
