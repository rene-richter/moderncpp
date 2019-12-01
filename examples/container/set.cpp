#include <iostream>
#include <set>

int main()
{
	auto sequence = std::set{ 16, 4, 1, 25, 9 };
	auto first = begin(sequence);
	auto last  = end(sequence);
	
	for (auto iter = first; iter != last; ++iter)
	{
		auto element = *iter;
		
		std::cout << element << ' ';
	}
	std::cout << '\n';

	for (auto element : sequence)
	{
		std::cout << element << ' ';		
	}
	std::cout << '\n';
}
