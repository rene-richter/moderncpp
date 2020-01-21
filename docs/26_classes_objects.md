# The object paradigm

## Paradigms

> C++ is a multiparadigm programming language with a bias towards system programming. 

A paradigm is a mindset, a framework of thought patterns. So programming can be viewed from various angles, resulting in different programming styles:

- imperative, structured, procedural, generic,
- descriptive, functional, logical,
- data-driven, message-driven, object-based or object-oriented.

Object-based programming is based on some principles:

- abstraction (of internal mechanisms),
- encapsulation (of data and methods for their manipulation, data hiding),
- persistence (objects are alive before and after operating with them).

Object-oriented programming is object-based programming with

- inheritance (of interfaces and/or implementation),
- polymorphism (subtyping).

Objects (based on ideas of Plato, ancient greek) are things you can think about. An object has 

- an identity: this hammer,
- a state: 1 kg stainless steel head, hickory handle,
- some behavior: it puts nails into wood.

## Planning: class diagrams, object diagrams, sequence diagrams

> If a hammer is your only tool, the whole world seems to consist of nails. 

A class declares what *methods* (operations) can be applied to (called for) objects (*instance*s) of that class. The Unified Modelling Language (UML) uses diagrams as tools for software engineering. A class diagram helps planning the design. Here is an example for objects, that generate a sequence of numbers:

```txt
----------------[Number]---
 ArithmeticSequence
---------------------------
+ Constructor(start, step)
+ value() : Number {readonly}
+ next()
---------------------------
```

Some implementation details are hidden at this stage. To instantiate a class, define a variable of that type:

```cpp
// #include class header

int main()
{
    auto odd = ArithmeticSequence{1,2};
    
    for (int i=0; i<10; ++i)
    {
        std::cout << odd.value() << ' ';
        odd.next();
    }
}
```

An object diagram describes the state of the that instance at some time, e.g. after `i==2`:

```txt
----------------[double]---
 odd : ArithmeticSequence
---------------------------
- current = 5
- step = 2
---------------------------
```

A sequence diagram describes interactions with such objects (*use cases*), which *messages* go to the object, how it responds:

```txt
+------+             +-----+
| main |             | odd |
+------+             +-----+
   |      value()       |
   | ------------------>|
   |       <--- 1       |
   |      next()        |
   | ------------------>|
   |      value()       |
   | ------------------>|
   |       <--- 3       |
   |      next()        |
   | ------------------>|
   v                    v
```

How it works internally is an implementation detail. This can (and will) change over time, when *use cases* are refined.

## Class interface definition

```cpp
// class header

using Number = double;

class ArithmeticSequence
{
public:
    ArithmeticSequence(Number start, Number step);
    Number value() const;
    void next();
private:    
    Number current_;
    Number step_;
};
```

Data are hidden (private), users can only call public methods (encapsulation). Read-only (`const`) methods are not allowed to mutate the object state.

## Method implementation

The implementation can go into another source file:

````cpp
// #include class header

ArithmeticSequence::ArithmeticSequence(Number start, Number step)
: current_{start}
, step_{step}
{
}

auto ArithmeticSequence::value() const { return current; }
void ArithmeticSequence::next() { current += step; }
````

Test:

```cpp
auto seq = ArithmeticSequence{1,2};
assert(1 == seq.value());
for (auto expected : {1,3,5,7})
{
    assert(expected == seq.value());
    seq.next();    
}
assert(9 == seq.value());
```

Exercise:

+ Design, implement and test another class `GeometricSequence`, generating numbers 1,2,4,8, ... etc., when instantiated with `GeometricSequence{1,2}`.
+ Do you see some similarities?

