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

Q: Where are `std::cin` and `std::cout` defined?

A: Global variables which static lifetime. --- Warning: There are dragons! (static initialization order fiasco, singletons, dead letter box debugging)

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

## Construction time again

When a variable is created, a *constructor* is called. It can take parameters, can (should?) assign initialization values to member variables. After construction an object should be in a valid state.

```cpp
struct Point
{
    int x, y;
    
    Point() : x{0}, y{0} {}  // default constructor
    Point(int xv, int yv) : x{xv}, y{yv} {} // user defined constructor
};

Point p;
Point q{1,2}; // error
Point r(3,4);
```

When your class provides a constructor, it must be called. Members are constructed before entering the constructor body, even if not in the member initializer list.

Q: In which order are members constructed? Can you change the order in the member initialization list?

Do you have a lot of work to do in constructor and you don't want to repeat code? Use a delegating constructor:

````cpp
struct Point{    
    int x, y;
    
    Point() : Point{0,0} {}  // delegate member initialization to user defined constructor:
    Point(int xv, int yv) : x{xv}, y{yv} {}
};
````

Zero-initialization for fundamental type members in >= C++17 without constructors:

```cpp
struct Point
{
    int x{}, y{};
};

Point p;
Point q{1,2};
Point r(3,4); // error
```

When you provide no constructor(s), the compiler provides a default constructor. It does nothing. Member variables are build using their own default constructors (if they have one). Brace list initializers are handed over to member variables. 

## Keep it simple

Constructors can do complicated things (acquire memory blocks, open file handles, ...)

*RAII principle*: Resource Acquisition Is Initialization

In aggregated objects there should be one "wrapper" for each resource (*Single Responsibility principle*), e.g. a `std:string`, `std::vector`, `std::ifstream` / `std::ofstream`, `std::file`,  `std::optional<T>`, `std::shared_pointer<T>`, `std::unique_pointer<T>`etc.

```cpp
struct DataCollection
{
  std::string description;
  std::vector<double> data;  
};

DataCollection temperatures { "Dresden", { 1, 5, 7, 3 } };
```

When member variables are responsible for their own resources, your class does not need to worry about freeing resources: *Rule of Zero*.

## Time to die

The C++ garbage collector is `}`.

Each class has to free its resources in the *destructor*. It's called automatically when the object lifetime ends. 

```cpp
class X
{
  ~X() { /* free resources here */ }  
};
```

Member variables are destroyed with their aggregates.

If a class has to provide a destructor, in most cases all *special functions* have to be user-defined (or deleted) --- *Rule of Five*:

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



