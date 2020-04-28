# Smart pointers in C++

... are smart, but not pointers. They are classes implementing a pointer-like interface and (safely) handling ownership of dynamically managed resources:

```cpp
std::unique_ptr<T> u = make_unique<T>(param); // not copyable, only movable
std::shared_ptr<T> s = make_shared<T>(param); // ref counting ptr
std::weak_ptr<T> w = s; // without ref counting to avoid/break self-sustaining cycles
if (auto sp = w.lock())  ... // use *sp 
```
When used as class members, you don't have to define special member functions ([Rule of Zero](../examples/smartptr/rule_f_zero.cpp)), unless you want different behavior.

## `std::unique_ptr<T>`

The factory helper function `make_unique<T>(init_values)` encapsulates operator `new` and returns `std::unique_ptr<T>` for local variables, parameters, and return types. To transfer ownership from a non-temporary variable, use `std::move()`. `std::move()` doesn’t move the ownership, it prepares only for the transfer. After the ownership is transferred, the former owner is empty.

 ```cpp
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
 ```

Even if `producer()` is called without transferring the result to a consumer, there is no memory leak.

`std::unique_ptr<T>` can be used as handles to store dynamically allocated objects in a `std::vector<std::unique_ptr<T>>` (example [zoo](../examples/smartptr/zoo.cpp)) or inside a class ([example](../examples/smartptr/rule_of_zero.cpp)), even for derived class objects.

Exercise: Since `std::stack<T>` by default is implemented with `std::vector<T>`, this would be a good point to implement the “Bremen musicians”  as a stack of safe pointers to animals of specialized types. 

## `std::shared_ptr<T>`

Reference-counting pointers

* can be produced by the factory function `std::make_shared<T>(param)` with the parameters needed to construct the object,
* share objects when copied or assigned from other shared pointers. `p.use_count()` gives the number of references.
* delete the object, when use count falls to 0. 

Warning 1: Don’t create no self-sustaining cycles: Object a contains a `shared_ptr` to b, and object  b contains a `shared_ptr` to a. Even if no other pointer points to them, the use count cannot fall to 0; this will result in a resource leak! (This is possible also in languages using garbage collectors...)

Warning 2: Using `shared_ptr<T>` as a function value parameter is considered bad practice when performance is key: it has to increment the use count when calling, and to increment it on exit. If the object outlives the called function, use an object reference as parameter.  

## `std::weak_ptr<T>`

is a good way to solve the dangling pointer problem. It is also designed to break cycles. It holds a pointer to a shared object, but not to increment the use count. By locking a `weak_ptr`, you get a `shared_ptr` that

* a) refers to an existing object or
* b) is empty when the referred object is gone.

```cpp
std::shared_ptr<T> s = make_shared<T>(param);
std::weak_ptr<T> w = s;
// ...
if (some_condition) s = null_ptr;
// ...
if (auto sp = w.lock())  ... // use *sp 
```

TODO: Find good example involving `weak_ptr<T>`: Team and Member? Parent/child? Observer/observable pattern?

YouTube video tip: Herb Sutter [Leak-Freedom in C++ ... By Default](https://www.youtube.com/watch?v=JfmTagWcqoE)  CppCon (2016).



