# Stacking cats and other animals

inspired by Bjarne Stroustrup's [Sixteen ways to stack a cat](http://www.stroustrup.com/stack_cat.pdf ) (1990),
leading to a Brothers Grimm's tale, made in Modern C++.

## Stack

A stack is a device to store multiple things on top of each other,
like a stack of books, a stack of kitchen plates, a stack of shipping containers, ...
You can 
* push something on the stack,
* pop something from it,
* and have access to the top thing on the stack.

## A stack of cats

If you have a lot of cats, sometimes you have to stack them.
The trick is how to do that without making them angry...
(It's more about the stack than the cats.)

### 1st attempt

```cpp
using Cat = int; // only integer cats!
const int MAXSTACKSIZE = 10;

struct Stack
{
	int count;
	std::array<Cat, MAXSTACKSIZE> storage;
};

// operations

bool is_empty(const Stack& s) { return s.count == 0; }
bool is_full (const Stack& s) { return s.count == MAXSTACKSIZE; }

void push(Stack& s, Cat x) { s.storage[s.count++] = x; }
void pop (Stack& s) { s.storage[--s.count] = 0; }
Cat& top (Stack& s) { return s.storage[s.count-1]; }

void create (Stack& s) { s.count = 0; }
void destroy(Stack& s) { while (not is_empty(s)) pop(s); }

// 

void demo1()
{
	Stack s;
	create(s);
	
	push(s, 1);
	push(s, 2);
	push(s, 3);
	assert(top(s) == 3);
	pop(s);
	assert(top(s) == 2);
	
	destroy(s);
}
```

Here is a (incomplete) list of issues:
* pop(s) resets a place on storage to 0. Why? Suppose 0 stands for an empty place
(would not be necessary, but simplifies debugging ...)
* Never forget to call create(s): otherwise count is not initialized => garbage.
Next cat would be pushed to somewhere in space, i.e memory,
causing undefined behaviour like killing your cat, killing your program or
making your cat pregnant even if you don't have any cats anymore!
* Pop all cats from the stack before removing it: otherwise these cats will become angry. So never forget to call destroy(s). If you don't pop off all cats, their lifetime ends, when the storage is destroyed at the end of the stack lifetime.
(For int values nothing bad happens here.)
* The implementation of destroy(s) only illustrates that the programmer is responsible for cleaning up all ressources he allocates -- there is no garbage collector at all (or seen the other way around, the best of all garbage collectors:
Don't produce any garbage in the first place).
* Setting s.count = 0 in demo() directly would have the same effect for the moment,
but what if the implementation of stack changes?
* Assigning s.count a wrong value at any moment can result in horrible effects.
It's impossible to reason about the correctness of stack without knowing the whole program.

## Stage 2: Restricting access to friends

```cpp
class Stack
{
	static const int MAXSTACKSIZE = 10;

	int count;
	std::array<Cat, MAXSTACKSIZE> storage;
public:
	friend void create (Stack& s) { s.count = 0; }
	friend void destroy(Stack& s) { while (not is_empty(s)) pop(s); }

	friend bool is_empty(const Stack& s) { return s.count == 0; }
	friend bool is_full (const Stack& s) { return s.count == MAXSTACKSIZE; }

	friend void push(Stack& s, Cat x) { s.storage[s.count++] = x; }
	friend void pop (Stack& s) { s.storage[--s.count] = 0; }
	friend Cat& top (Stack& s) { return s.storage[s.count-1]; }
};

void demo2() 
{
	// same as before
}
```
* One issue solved: no access to data members from outside (except friends).
* Classwide constant MAXSTACKSIZE is now an implementation detail.

## Stage 3: Member functions

```cpp
class Stack
{
	static const int MAXSTACKSIZE = 10;

	int count;
	std::array<Cat, MAXSTACKSIZE> storage;
public:
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
	Stack s;
	s.create();
	
	s.push(1);
	s.push(2);
	s.push(3);
	assert(s.top() == 3);
	s.pop();
	assert(s.top() == 2);
	
	s.destroy();
}
```
Note:
* member functions (_methods_) have access to member data.
* const methods do not change any member data.

## Stage 4: Automating construction and destruction 

special functions:
* constructor Stack()
* destructor ~Stack() 

```cpp
class Stack
{
	static const int MAXSTACKSIZE = 10;

	int count;
	std::array<Cat, MAXSTACKSIZE> storage;
public:
	Stack() { count = 0; }
	~Stack() { while (not is_empty()) pop(); }

	bool is_empty() const { return count == 0; }
	bool is_full () const { return count == MAXSTACKSIZE; }

	void push(Cat x) { storage[count++] = x; }
	void pop () { storage[--count] = 0; }
	Cat& top () { return storage[count-1]; }
};

void demo4() 
{
	Stack s;
	s.push(1);
	s.push(2);
	s.push(3);
	assert(s.top() == 3);
	s.pop();
	assert(s.top() == 2);
}
```

* Stack behaviour is now controlled by its methods. 
* A responsible programmer would make sure the stack is 
  * not full when pushing, and
  * not empty when popping.

## Stage 5: Multiples stack of different data and capacity 

Make stack a template.

```cpp
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
	void pop () { storage[--count] = 0; }
	T&   top () { return storage[count-1]; }
};

void demo5() 
{
	Stack<Cat> s;
	s.push(1);
	s.push(2);
	assert(s.top() == 2);

	using Dog = std::string;

	Stack<Dog, 5> dogs;
	dogs.push("bello");
	assert(dogs.top() == "bello");
}
```
* You can't mix them: impossible to push a cat on a stack of dogs.

## Stage 6: Use standard library implementation

std::stack<T>

rename is_empty(), no method full()

# Stage 7
"The Bremen musicians" are various types of animals: donkey, rooster, cat and dog.
Sometimes they get visitors. Sometimes they form a stack.

A C++17 solution with _compile time polymorphism_ using a _union type_:
* Animal can hold only one object at a time.
* But the objects can have totally unrelated types.

```cpp
class Cat{};
class Dog{};
class Donkey{};
class Rooster{};
using Animal = std::variant<Donkey, Dog, Cat, Rooster>;

struct FriendlyVisitor
{
	void operator()(Cat x) { std::cout << "mew ";  }
	void operator()(Dog x) { std::cout << "woof ";  }
	void operator()(Donkey x) { std::cout << "hee-haw ";  }
	void operator()(Rooster x) { std::cout << "cock-a-doodle-doo ";  }
};

struct EvilVisitor
{
	void operator()(Cat x) { std::cout << "scratch!\n";  }
	void operator()(Dog x) { std::cout << "bite!\n";  }
	void operator()(Donkey x) { std::cout << "bash!\n";  }
	void operator()(Rooster x) { std::cout << "hack!\n";  }
};

void demo7() 
{
	std::stack<Animal> s;
	
	s.push(Donkey{});
	s.push(Dog{});
	s.push(Cat{});
	s.push(Rooster{});
	
	while (!s.empty())
	{
		Animal animal = s.top();
		s.pop();
		std::visit(FriendlyVisitor{}, animal);
		std::visit(EvilVisitor{}, animal);
	}
}
```

# Stage 8
would solve the same task using inheritance, runtime polymorphism, and smart pointers
(TODO).