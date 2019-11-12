#include <cassert>
#include <array>
#include <iostream>

using Cat = int; // only integer cats!
int const MAXSTACKSIZE = 10;

struct Stack
{
	int count;
	std::array<Cat, MAXSTACKSIZE> storage;
};

// operations

bool is_empty(Stack const& s) { return s.count == 0; }
bool is_full (Stack const& s) { return s.count == MAXSTACKSIZE; }

void push(Stack& s, Cat x) { s.storage[s.count++] = x; }
void pop (Stack& s) { s.storage[--s.count] = 0; }
Cat& top (Stack& s) { return s.storage[s.count-1]; }

void create (Stack& s) { s.count = 0; }
void destroy(Stack& s) { while (not is_empty(s)) pop(s); }

// 

void demo1()
{
	std::cout << "create" << std::endl;
	Stack s;
	create(s);
	std::cout << "created " << s.count << std::endl;
	
	push(s, 1);
	push(s, 2);
	push(s, 3);
	assert(top(s) == 3);
	pop(s);
	assert(top(s) == 2);

	std::cout << "destroy" << std::endl;
	destroy(s);
	std::cout << "destroyed " << s.count << std::endl;
}

int main()
{
	demo1();
}