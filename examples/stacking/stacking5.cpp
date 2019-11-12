#include <cassert>
#include <array>
#include <string>

template <typename T, int MAXSTACKSIZE = 10>
class Stack
{
	int count;
	std::array<T, MAXSTACKSIZE> storage;
public:
	Stack() { count = 0; }
	~Stack() { while (not is_empty()) pop(); }

	bool is_empty() const { return count == 0; }
	bool is_full () const { return count == MAXSTACKSIZE; }

	void push(T x) { storage[count++] = x; }
	void pop () { storage[--count] = T{}; }
	T&   top () { return storage[count-1]; }
};

void demo5() 
{
	using Cat = int; // only integer cats!
	Stack<Cat> s;
	s.push(1);
	s.push(2);
	assert(s.top() == 2);

	using Dog = std::string;

	Stack<Dog, 5> dogs;
	dogs.push("bello");
	assert(dogs.top() == "bello");
}

int main()
{
	demo5();
}