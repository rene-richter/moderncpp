# Creation and destruction of objects

> Drum besser wär's, daß nichts entstünde
>
> > --- Mephistopheles

## The rise and fall of variables

Each name has a *scope*, every object has a *lifetime*.

```cpp
void f(int parameter = 2019) // <- (1)
{                            // <- (2)
    auto year = 2020;        // <- (3)
    // ...                   // <- (4)
}                            // <- (5)
```

Q: 

* When do these variables come into existence?
* Which value do they have? When? From where?
* At which point disappears a local variable?

A: ...

Q: Where and when are `std::cin` and `std::cout` defined?

A: Global variables with static lifetime. --- Warning: There are dragons! (static initialization order fiasco, singletons, dead letter box debugging)

## Variations on I-N-I-T

[Lots of ways](https://mobile.twitter.com/timur_audio/status/1004017362381795329) to (not) assign a value at beginning of variable lifetime ([*initialization*](https://en.cppreference.com/w/cpp/language/initialization)):

```cpp
int  a;              
int  b{};
auto c{};            // error, why?
auto d = 2;          
auto e(3);
auto f{4};           

auto g = {5};        // error: #include <initializer_list>
auto h = {6,7};      // dto. 
auto i{8,9};         // error: direct-list-initilization with more than 1 value 

std::string j = "Hello"; // #include <string>
auto k = std::string("Hello");
auto l = "Hello";

auto m = "Hello"s;    // error, if not using namespace std::literals
auto n = 11s;         // #include <chrono>
auto o = 12i;         // #include <complex>

Point p;              // struct Point{ int x, y; };
Point q = {1,2};
Point r{3,4};
auto s = Point{5,6};
auto t = Point(7,8); // error

auto u = std::vector{1,2};
auto v = std::vector<int>{3,4};
auto w = std::vector<int>(5,6);
```

Q: 

* Which types do variables have (consider *auto type deduction*)? 
* Are they initialized? 
* Which values do they contain?
* Why and when to use {} or ()?

A: ...

## Construction time (again)

When a variable is created, a *constructor* is called. It can take parameters, can (should?) assign initialization values to member variables. After construction an object should be in a valid state.

```cpp
struct Point
{
    int x, y;
    
    Point() : x{0}, y{0} {}  // default constructor
    Point(int xv, int yv) : x{xv}, y{yv} {} // user-defined constructor
};

Point p;
Point q{};
Point r{1,2};
Point s(3,4);
```

When your class provides a constructor, it must be called. Members are constructed before entering the constructor body, even if not in the member initializer list.

Q: In which order are members constructed? Can you change the order in the member initialization list?

Do you have a lot of work to do in constructor and you don't want to repeat code? Use a delegating constructor:

````cpp
struct Point
{    
    int x, y;
    
    Point() : Point{0,0} {}  // delegate member initialization to user defined constructor:
    Point(int xv, int yv) : x{xv}, y{yv} {}
};
````

Default-initialize (i.e. zero-initialize fundamental type members) in >= C++17 without constructors using braces:

```cpp
struct Point
{
    int x{}, y{}; // x = 0, y = 0
};

Point p;
Point q{};
Point r{1,2};
Point s(3,4); // error: no user-defined constructor taking two parameters
```

When you provide no constructor(s), the compiler provides a default constructor. It does nothing. Member variables are build using their own default constructors (if they have one). Brace list initializers are handed over to member variables. 

### Made for loving you (*KISS* = Keep it simple, stupid )

```cpp
struct DataCollection
{
  std::string description;
  std::vector<double> data;  
};

DataCollection temperatures { "Dresden", { 1, 5, 7, 3 } };
```

Each member variable of a class has it's own way how to deal with resources; `std::string`and `std::vector` free their memory automatically, when the lifetime of `DataCollection temperatures` ends. No need to worry about freeing them for your class or `struct`, follow the *Rule of Zero*. It's much simpler compared to the *Rule of Five* described below.

In aggregated objects there should be one "wrapper" for each resource (*Single Responsibility principle*), e.g. a `std:string`, `std::vector`, `std::ifstream` / `std::ofstream`, `std::file`,  `std::optional<T>`, `std::shared_pointer<T>`, `std::unique_pointer<T>`etc.

### Resource Acquisition Is Initialization (*RAII*)

(This principle should better be named AC/DC = Acquire in Constructor/Destructor Cleans up.)

Constructors can do complicated things like acquiring memory blocks, opening file handles:

```cpp
#include <fstream>

auto write_to_file(std::string filename)
{
    std::ofstream out{filename};  // std::ofstream out;
                                  // out.open(filename); 
    out << "Hello file\n";
}                                 // out.flush();
                                  // out.close();
```

When lifetime of `out` ends, `std::ofstream` flushes file buffer and closes file handle.  The „garbage collector“ of C++ is `}`. 

## Time to die

Each class should free its resources in the *destructor*. It's called automatically when the object lifetime ends. Member variables are destroyed with (more exactly, after the destruction of) their aggregate. 

```cpp
class X
{
  ~X() { /* free resources here */ }  
};
```

If a class provides a user-defined destructor, all [*special member functions*](https://namespace-cpp.de/std/doku.php/kennen/spezielle_methoden#regeln) of the class should be user-defined or deleted --- *Rule of Five*:

```cpp
struct E
{
    ~E() = default;                       // destructor

    E() = default;                        // default constructor
    E(E const& e) = default;              // copy constructor
    E(E&& e) = default;                   // move constructor
    E& operator=(E const& rhs) = default; // copy assignment
    E& operator=(E&& rhs) = default;      // move assignment
};
```

Q: What if you declare the destructor ` = delete`?

```cpp
struct Nondestructible 
{ 
    ~Nondestructible() = delete;
};

Nondestructible until_eternity; // error
```

## Big log 

Exercise: Create a class `Log` containing a `std::string` that writes a log message to `std::cerr` when a special member function of this class is called. Analyze the following program. Understand which special member function is called when:

```cpp
class Log 
{
	// TODO:
};

Log global{"global"};

auto f(Log param)
{
	static Log slocal{"static local"};

	Log local{"local in f()"};
	return Log{"result"};
}

int main()
{
	Log start{"in main"};
	Log copy{start};
	Log log;

	for (int i = 0; i < 2; ++i)
	{
		Log log{"loop body"};
		Log result = f({"param"});
	}

	{	
		Log log{"a moving story"};
		Log movedfrom = std::move(log);
		log = std::move(movedfrom);
	}
	Log end{"leaving main"};
	copy = end;
}
```

[Example](../examples/logging/lifetime.cpp) output (including memory address `this` of each Log object):

```
0x521040 : 'global' constructed.
0x132fce0 : 'in main' constructed.
0x132fd00 : 'in main' copy constructed.
0x132fd20 : 'default' constructed.
0x132fd40 : 'loop body' constructed.
0x132fda0 : 'param' constructed.
0x521080 : 'static local' constructed.
0x132fbf0 : 'local in f()' constructed.
0x132fd60 : 'result' constructed.
0x132fbf0 : 'local in f()' destroyed.
0x132fda0 : 'param' destroyed.
0x132fd60 : 'result' destroyed.
0x132fd40 : 'loop body' destroyed.
0x132fd40 : 'loop body' constructed.
0x132fda0 : 'param' constructed.
0x132fbf0 : 'local in f()' constructed.
0x132fd60 : 'result' constructed.
0x132fbf0 : 'local in f()' destroyed.
0x132fda0 : 'param' destroyed.
0x132fd60 : 'result' destroyed.
0x132fd40 : 'loop body' destroyed.
0x132fd80 : 'a moving story' constructed.
0x132fda0 : 'a moving story' move constructed.
0x132fd80 : 'a moving story' move assigned.
0x132fda0 : '' destroyed.
0x132fd80 : 'a moving story' destroyed.
0x132fda0 : 'leaving main' constructed.
0x132fd00 : 'leaving main' copy assigned.
0x132fda0 : 'leaving main' destroyed.
0x132fd20 : 'default' destroyed.
0x132fd00 : 'leaving main' destroyed.
0x132fce0 : 'in main' destroyed.
0x521080 : 'static local' destroyed.
0x521040 : 'global' destroyed.
```



 

