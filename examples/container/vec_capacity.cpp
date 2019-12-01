#include <iostream>
#include <vector>

int main()
try
{
	std::vector<int> v;
	auto s = v.size();
	auto c = v.capacity();
	
	while (true)
	{
		v.push_back(1);
		if (c != v.capacity())
		{
			std::cout << s << ' ' << c << ' ' << &v.front() << '\n';
			s = v.size();
			c = v.capacity();
		}
	}
}
catch (std::exception& e)
{
	std::cerr << e.what() << '\n';
}
