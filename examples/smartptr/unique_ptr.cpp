#include <memory>
#include <iostream>

auto local()
{
	auto p = std::make_unique<int>(0);
	std::cout << *p << " lives until end of block\n";	
}

auto producer(int n)
{
	auto p = std::make_unique<int>(n);
	std::cout << "produced " << *p << '\n';
	return p;		
}

auto consumer(std::unique_ptr<int> p)
{
	if (p) std::cout << "consumed " << *p << '\n';
}

int main()
{
	// transfer of ownership:
	consumer(producer(1));
	
	std::unique_ptr<int> p;
	if (p) std::cout << "should be empty " << *p << '\n';
	
	p = producer(2);
	if (p) std::cout << "got " << *p << '\n';

	consumer(std::move(p));
	if (p) std::cout << "stayed " << *p << '\n';
}
