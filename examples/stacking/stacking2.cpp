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
	friend void create (Stack& s) { s.count = 0; }
	friend void destroy(Stack& s) { while (not is_empty(s)) pop(s); }

	friend bool is_empty(Stack const& s) { return s.count == 0; }
	friend bool is_full (Stack const& s) { return s.count == MAXSTACKSIZE; }

	friend void push(Stack& s, Cat x) { s.storage[s.count++] = x; }
	friend void pop (Stack& s) { s.storage[--s.count] = 0; }
	friend Cat& top (Stack& s) { return s.storage[s.count-1]; }
};

void demo2() 
{
	std::cout << "create" << std::endl;
	Stack s;
	create(s);
	std::cout << "created" << std::endl;
	
	push(s, 1);
	push(s, 2);
	push(s, 3);
	assert(top(s) == 3);
	pop(s);
	assert(top(s) == 2);

	std::cout << "destroy" << std::endl;
	destroy(s);
	std::cout << "destroyed" << std::endl;
}

int main()
{
	demo2();
}