#include <cassert>
#include <array>
#include <iostream>

using Cat = int; // only integer cats!

class Stack
{
	static int const MAXSTACKSIZE = 10;

	int count;
	std::array<Cat, MAXSTACKSIZE> storage;
// public:
	void create () { count = 0; }
	void destroy() { while (not is_empty()) pop(); }

	bool is_empty() const { return count == 0; }
	bool is_full () const { return count == MAXSTACKSIZE; }

	void push(Cat x) { storage[count++] = x; }
	void pop () { storage[--count] = 0; }
	Cat& top () { return storage[count-1]; }
};

void demo3() 
{
	std::cout << "create" << std::endl;
	Stack s;
	s.create();
	std::cout << "created" << std::endl;
	
	s.push(1);
	s.push(2);
	s.push(3);
	assert(s.top() == 3);
	s.pop();
	assert(s.top() == 2);
	
	std::cout << "destroy" << std::endl;
	s.destroy();
	std::cout << "destroyed" << std::endl;
}

int main()
{
	demo3();
}