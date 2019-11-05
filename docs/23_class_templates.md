# Class templates

To stage a problem: Sometimes we have to deal with points on screen (integer pixel coordinates) 
and points in the two-dimensional real plane (floating-point coordinates):

Q: Is it possible to have two different sorts of `Point` types in the same program like this:

```cpp
auto pixel = Point{2, 3};
auto point = Point{1.57, 2.718};

```
Would it be desirable?
