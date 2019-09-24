# Programs = data structures + algorithms
## Connect related data

```cpp
struct Person
{
	std::string name;
	int born;
	int died;
};

Person p{"Galilei", 1564, 1642};
```

Access to data members

```cpp
void print(Person p)
{
	std::cout << p.name << '\t' << p.born << '-' << p.died << '\n'; 
}

Person read_data_for_person()
{
	Person p;
	char dummy;
	std::cin >> p.name >> p.born >> dummy >> p.died;
	return p;
}
```

## Data containers

* for many data of the same type
* containers are generic: `vector<T>` where `T` can be any (copyable, default-constructible, ...) type

```cpp
std::vector<Person> persons;
```
Empty containers
```cpp
persons.empty() // persons.size() == 0
```
can grow (acquire more data)

```cpp
persons.push_back(p);
persons.push_back({"Newton", 1642, 1726});
```
and shrink

```cpp
persons.pop_back();
```
Initializer lists fill containers at construction time:

```cpp
std::vector<Person> persons
	{
		{"Galilei", 1564, 1642},
		{"Newton" , 1642, 1726},
		{"Hawking", 1942, 2018},
	};
```
Iterate over all elements
```cpp
for (auto person : persons)
{ 
	print(person);
}
```
or unpack data with *structured bindings* (different names are possible):

```cpp
for (auto [lastname, year_of_birth, year_of_death_not_used] : persons)
{ 
	std::cout << lastname << '\t' << year_of_birth << '\n';
}
```

## Algorithms
work on a range of data
```cpp
#include <algorithm>

std::sort(begin(persons), end(persons), by_name);
std::sort(begin(persons), end(persons), by_year_of_birth);
```

The sorting criterion can be a predefined function returning `bool` or a lambda expression (adhoc function):

```cpp
auto by_name = [](Person x, Person y) { return x.name < y.name; };
auto by_year_of_birth = [](Person x, Person y) { return x.born < y.born; };
```

## Memory management

`vector<T> v` is similar to `std::string s`
* memory is (re)allocated, when needed
* released, when variables `s` and `v` end their life
* resource management is deterministic, no garbage collection needed
* RAII principle ("*r*essource *a*cquisition *i*s *i*nitialization"), should be named AC/DC ("*a*cquire in *c*onstructor / *d*estructor *c*leans up")

```
s ----> [sequence of chars in chunk of dynamic memory...]

v ----> [data of type T in chunk of dynamic memory...]
```

## (Unnecessary) copies and (constant) references

### Copies
```cpp
auto another_person = person;
```
copies all data from `person` to `another_person`. They exist as independent objects. Changing `person.name` or `person.died` will not affect `another_person`.

This loop does not change names in container `persons`, since it works on copies of each container value:
```cpp
for (auto person : persons)
{
	person.name = "N.N."; // changes a copy
}
```
### References
Refer to existing objects using a reference `&` (an "alias" name):
```cpp
for (auto& person : persons)
{
	person.name = "N.N."; // changes values in container
}
```
No copy takes place, so references are cheaper. 
If you don't want to modify values, mark them as `const`:
```cpp
for (auto const& person : persons)
{
	person.name = "N.N."; // error
}
```
### Moving stories about expiring values
```cpp
Person read_data_for_person();
```
returns a value, possibly containing lots of dynamic allocated data (a very long name).
```
temp ----------> [data...]
```
The return value object ends its life after giving its data to another object. The handover can be done by a (possibly expensive) *copy*
```
temp ----------> [data...]
                  |||||||
                  vvvvvvv
copy ----------> [data...]
```

or a (possibly cheaper) *move* operation, if the copy or move is not *elided* completely:
```cpp
Person p1 = read_data_for_person(); // possible copy elision
```

After moving its data the *moved-from* object is "in a valid but empty state". It can be destroyed safely.
```
temp -> X    --> [data...]
           /
          /
p1  -----
```
### Variations on function parameters
*Input parameters*
```cpp
void print(Person p);
```
take temporary *expiring values* by move into `p` (if possible)
```cpp
print(read_data_for_person()); // move
```
otherwise copy their data into `p`:

```cpp
Person p2{"Newton" , 1642, 1726};
print(p2); // copy
```

*Output parameters*
```cpp
void print(Person& p);
```
take a reference to *lvalue* (object that can appear on the left side of an assignment operation)
* are allowed to change the data of the referred object,
* are another way to transport information from inside the function out,
* require a copy for temporary *rvalues*. The compiler may warn about that copy.

```cpp
void print(Person const& p);
```
takes a constant reference to an lvalue. For temporary rvalues the lifetime is extended until the *end of statement*.


We could have two versions for optimal performance
```cpp
void print(Person const& p); // (const) reference to existing data: no copy
void print(Person&& p);      // receiving temporary value (rvalue reference): move
```
in the same codebase which would be harder to maintain.
(For n parameters there would be 2^n versions. This is for experts only...)

### Exercises and questions:
* Would it be a good idea for `print()` to have a reference parameter?
* What about `const&` ?
* How to measure the costs of memory allocation/release, copy/move operations?
* What is *small string optimization*? When does it apply?