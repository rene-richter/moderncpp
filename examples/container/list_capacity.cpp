#include <iostream>
#include <list>

int main()
try
{
	std::list<int> v;
	auto c = v.size() / 1'000'000;
	
	while (true)
	{
		v.push_back(1);
		if (c != v.size() / 1'000'000)
		{
			std::cout << c << '\n';
			c = v.size() / 1'000'000;
		}
	}
}
catch (std::exception& e)
{
	std::cerr << e.what() << '\n';
}
