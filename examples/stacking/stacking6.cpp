#include <cassert>
#include <string>
#include <stack>

void demo6() 
{
	using Cat = int; // only integer cats!
	std::stack<Cat> s;
	s.push(1);
	s.push(2);
	assert(s.top() == 2);

	using Dog = std::string;
	std::stack<Dog> dogs;
	dogs.push("bello");
	assert(dogs.top() == "bello");
}

int main()
{
	demo6();
}