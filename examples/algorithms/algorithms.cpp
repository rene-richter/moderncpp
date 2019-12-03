#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include <algorithm>

void demo()
{
	auto show = [](auto const& container)
	{
		std::cout << "[ ";
		std::for_each(begin(container), end(container), 
			[](auto e) { std::cout << e << " "; });	

		std::cout << "]\n";
	};

	std::string s = "Hello Algorithms";
	show(s);
	
	std::transform(begin(s), end(s), begin(s), 
		[](auto e) { return std::tolower(e); });
	
	show(s);
	
	std::replace(begin(s), end(s), 'l', 'r');
	show(s);
	
	auto pos = std::remove(begin(s), end(s), ' ');
	show(s);
	
	s.erase(pos, end(s));
	show(s);
	
	std::sort(begin(s), end(s));
	show(s);
	
	auto pos2 = std::unique(begin(s), end(s));
	show(s);
	
	s.erase(pos2, end(s));
	show(s);
	
	auto is_vocal = [](auto e) { 
		return e == 'a' || e == 'e' || e == 'i' || e == 'o' || e == 'u';
	};
	
	auto pos3 = std::partition(begin(s), end(s), is_vocal);
	show(s);
	
	std::fill(pos3, end(s), '_');
	show(s);	
	
	while (std::next_permutation(begin(s), pos3))
	{
		show(s);	
	}

	// auto seed = std::random_device{};
	auto seed = std::time(0);
	auto rng = std::default_random_engine(seed);
	
	std::shuffle(begin(s), end(s), rng);
	show(s);
}

int main()
{
	demo();
}
