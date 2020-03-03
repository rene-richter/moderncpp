# References

A (lvalue) reference `T&` is an *alias* to an existing object, another name for an already defined variable:

```cpp
int i = 2;
int& r = i;
assert(r == 2);
r = 3;
assert(i == 3);
```

When defining a reference, you have to give an object name. The reference is tied to this object as long as the reference exists. References can be useful to “shorten” long and complicated names into more descriptive names:

```cpp
int matrix[3][3];
auto& center = matrix[1][1];
center = 5;
```

References in range-based for loops have read/write access to data: 

````cpp
std::vector<int> data;
// ...
for (auto& e : data)
{
    e *= 2;
}
````

By using constant reference parameters `T const&` function calls do not copy large amounts of data:

```cpp
void read(std::vector<int> const& bigdata)
{
    // ...
}
```

Reference parameters are essential for function *output parameters* like in

```cpp
void swap(int& x, int& y)
{
    auto temp = x;
    x = y;
    y = temp;
}

// ...
int a = 1, b = 2;
swap(a, b);
assert(a == 2 && b == 1);
```

or I/O stream operators:

```cpp
struct Point { int x, y; };

std::istream& operator>>(std::istream& in, Point& p)
{
    int x, y;
    if (in >> x >> y) p = {x, y};
    return in;
}

// ...
Point a, b;
std::cin >> a >> b;
```

The values  `a.x` and `a.y` change on successful input. Also `istream` and `ostream` objects can not be copied. Their state changes during I/O operations --- and they should be returned as references for the next I/O operation (like reading `b`). In fact, references were invented for I/O stream operators. Otherwise we would have to use variable addresses (pointers) instead:

```cpp
&std::cin >> &a >> &b; // this is not C++!
read(&std::cin, &a);   // similar to C
```

Methods can grant (read/write or read-only) access to members of classes:

```cpp
class X
{
    std::string name_ {"N.N."};
public:
    auto& name() { return name_; }
    auto const& name() const { return name_; }
};

// ...
X obj;
assert(obj.name() == "N.N.");
obj.name() = "nobody";
```

Exercise: Does possible mean useful or sensible? Compare to getter/setter patterns in other languages.

## Dangling references: A road to nowhere

Read this sentence again: The reference is tied to the object *as long as the reference exists*. In most cases the object outlives the reference. Otherwise you are in big trouble:

```cpp
int& wrong()
{
    int local = 42;
    return local;
}
// ...
int& dangling = wrong();
dangling = 666; // undefined behavior
```

Exercise:

* Why would this be dangerous? What does “dangling” mean?
* What does “undefined behavior” mean? 
* Why is a method returning a member reference o.k. then? 
* What about that:

```cpp
X f() { return {}; }
// ...
f().name() = "gone"; // how long do temporaries live?
```