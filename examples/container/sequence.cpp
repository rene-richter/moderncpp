#include <iostream>

int main()
{
	auto sequence = { 1, 4, 9, 16, 25 };
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
