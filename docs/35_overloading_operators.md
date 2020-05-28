# Overloading operators

Define operator `op` for an user-defined type, when appropriate:

```cpp
class Foo
{
public:    
  result_type operator op (params) {...}  // as member
};

// or global
result_type operator op (Foo foo, params) {...}
```


| op (list incomplete) | reason/examples                                    |
| ---------------- | ------------------------------------------ |
| `=`              | copy/move assignment (resource management) |
| `<< >>`          | stream input/output            |
| `== !=`          | equality                                   |
| `< <= >= >`      | ordering                             |
| `+ - * / % =+ ...` | arithmetic (and compound assignments)      |
| `++ --`          | increment/decrement (iterators)            |
| `* ->`           | iterators, smart pointers                  |
| `[]`             | `std::array<T>`, `std::vector<T>`, `std::map<K,V>` |
| `()`            | function call operator |
| `type` | conversion to another type |

Example (not production level code):

 ```cpp
struct Rational
{
    Integer d = 0, n = 1; // assuming a BigInt type
    
    Rational& operator *= (Rational rhs) 
    { 
        d *= rhs.d; 
        n*= rhs.n; 
        return *this; 
    }
    
    explicit operator double () const { ... }
};

Rational operator * (Rational a, Rational b)
{
    return a *= b;
}

bool operator == (Rational a, Rational b)
{
    return a.d * b.n == a.n * b.d;
}

bool operator != (Rational a, Rational b)
{
    return !(a == b);
}

bool operator < (Rational a, Rational b)
{
    return a.d * b.n < a.n * b.d;
}
 ```

## Function objects

Class defines `operator ()`:

```cpp
struct Linear
{
    double slope, offset;
    
    double operator () (double x) const { return slope * x + offset; }
};

auto demo(doule x)
{
    Linear f { 2, 1 };
    return f(x); // function call
}   // 2 * x + 1
```

[Lambda expressions](14_lambdas.md) are compiler-generated function objects of an anonymous type with `const`-qualified `operator()`:

```cpp
auto demo2(double x)
{
    auto f = [slope = 2, offset = 1] (double x) 
    {
        return slope * x + offset;
    };
    
    return f(x); // function call
}
```

