#include <iostream>

int main()
{
	int sequence[] = { 1, 4, 9, 16, 25 };
	auto first = std::begin(sequence);  // &sequence[0]
	auto last  = std::end(sequence);    // &sequence[0] + 5
	
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
