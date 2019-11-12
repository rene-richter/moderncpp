# Types = values & operations

A type in programming languages is like a structure in math, e.g. real numbers,
which consists of 
* a (possibly infinite) set of values (numbers) and
* a set of operations like adding, multiplying, taking the opposite(x) or the inverse(x).

## User-defined types

For a user-defined type choose a bundle of data 
```cpp
struct Point { int x, y; };
```
and a set of operations to apply on this struct:
```
Point A {1,2};
Point B = displace(A, dx, dy);
auto dist = distance(A, B); 
```
The set of possible values for `Point` is the cross product Z x Z of two sets of integer numbers Z. Therefore such types are called _cross product types_ in math.

## Same structure, but different types

To stage a problem: Sometimes we have to deal with points on screen (integer pixel coordinates) 
and points in the two-dimensional real plane (floating-point coordinates):

Q: Is it possible to have two different sorts of `Point` types in the same program like this:

```cpp
auto pixel = Point{2, 3};
auto point = Point{1.57, 2.718};

```
Would it be desirable?
