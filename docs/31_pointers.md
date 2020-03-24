# Pointers: Handle with care
Pointers are chameleons inherited from C:

* they are used as output parameters of functions,
* to point to opaque types like `FILE*` in C (C++ has `std::fstream` for that),
* to iterate over arrays and character strings,
* to manage dynamic storage,
* to access shared memory blocks and hardware devices.

When pointers do not point to the intended addresses, bad things can happen (undefined behavior = UB). There are lots of possible mistakes to make and lots of recommendations: 

* Do not overrun array boundaries. 

* Use reference wherever you can, pointers wherever you must. Avoid pointers until you can't. [[Stackoverflow](https://stackoverflow.com/questions/7058339/when-to-use-references-vs-pointers)]

* Don’t use *naked pointers* to manage/own resources. They are not exception-safe. 

  Thrown exceptions break the intended program flow, so owning resources via naked pointers is best avoided in C++. Encapsulate owning pointers into managing classes. Destructors take care of releasing resources.

* Non-owning naked pointers *can be o.k.* (when used with care). 

## Pointers: Where to find them

Pointer are variables that (can) hold the address of some other data. Pointer declarations have (at least) one asterisk `*` before the name of the pointer variable, e.g. `int *p`. (Yes, there are pointers to pointers ...)

You have to assign an address (by address operator `&`) of some object to it: `p = &something`. If you do not, you have a dangling pointer.

After that `*p` means: Go to the memory address that is stored in `p` (dereferencing the pointer). The declaration of a pointer is a pattern how to get to the referred value.

```cpp
int i = 1, j = 2;
int *p, *q; // one star for each pointer
p = &i;     // get address of i, store it in p
q = &j;
std::cout << *p << ' ' << *q;  //  1 2
*p = *q; 
std::cout << *p << ' ' << *q;  //  2 2
p = q; // now both pointers point to j
*p = 42;
std::cout << *p << ' ' << *q;  //  42 42
std::cout << i << ' ' << j;    //  2 42
```
Compare with references (declared by `&name`):

```cpp
int i = 1, j = 2;
int &ri = i, &rj = j; // must identify reference immediately
std::cout << ri << ' ' << rj;  //  1 2
ri = rj; 
std::cout << ri << ' ' << rj;  //  2 2
// Nope, can't change what reference refers to
ri = 42;
std::cout << ri << ' ' << rj;  //  42 2
std::cout << i << ' ' << j;    //  42 2
```

Note: nobody will (should) write such convoluted code when the variables are available. It’s to get the idea: a pointer can point to various addresses / objects, a reference is similar to a constant pointer:

```cpp
int * const cp = &i;
*cp = 42;
```

You may use pointers without knowing it:

```cpp
int arr[10];
arr[5] = 105;  // *(arr + 5) = 105
for (int index = 0; index < 10; ++index)
    arr[index] = 0;
```

An array name `arr` is a constant pointer to the first element `&arr[0]`. Access via index operator `[]` uses pointer arithmetic behind the curtain. Don’t access `arr[-1]` or `arr[10]` or beyond. This would be UB. The same is true for pointers iterating over the array. You have to know where the array ends:

```cpp
int* p = arr;
int* end = arr + 10;
for (p = arr; p < end; ++p)
    *p = 0;
```

Zero-terminated character string arrays end with a char containing `'\0'`. Don’t forget to terminate a string, otherwise loops may run “forever”:

```cpp
char s[] = "Hello"; // 6 chars long {'H','e','l','l','o','\0'}
char c[] = "World";
char *p = s, *q = c;
while (*p != '\0')
{
    *q = *p;
    ++p; ++q;
}
*q = '\0'; // end of string
```

This could be done "elegantly" and terse:

```cpp
char *p = s, *q = c;
while (*q++ = *p++); // basically this is strcpy(c, s);
```

Don’t write beyond the end of the array, especially when handling user input. Where to store that information safely?

## Pointers : How to avoid them

### Input/output parameters

Instead of defining a function like

```cpp
void ptrswap(int* a, int* b)    
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
// ...
int i = 1, j = 2;
ptrswap(&i, &j);
```

use references instead:

```cpp
void refswap(int& a, int& b)    
{
    int temp = a;
    a = b;
    b = temp;
}
// ...
int i = 1, j = 2;
refswap(i, j);
```

### Arrays and character strings

Use `std::array<T,N>` with fixed size `N`, `std::vector<T>`, `std::string` and *range-based for loops* or `<algorithms>` for less error-prone, more expressive code:

```cpp
std:array<int,10> arr; // elements
arr[5] = 105;  // arr.at(5) is safe, can throw out_of_bounds exception
for (auto& e : arr) e = 0; 

std:vector<int> v(10, 42); // 10 elements with value 42
v[5] = 105;  // v.at(5) is safe ....
v.push_back(42);
std::replace(begin(v), end(v), 105, 23);
for (auto e : v) std::cout << e; 

std::string s = "Hello";
std::string c = "World";
c = s + ", " + c + "! This is safe.";
```

### Dynamic memory

Pointers can refer to zero, one or many objects:

```cpp
int* p = nullptr;
p = new int(99); // *p = 99
assert(*p == 99);
delete p; // memory release
// p points to released memory, p is invalid
p = nullptr;
// ...
p = new int[10]; // 10 int's
// ... loop over 10 int's
delete [] p; // don't mix with delete p !
// p points to released memory, p is invalid
p = nullptr;
// ...
if (p)  // is p a valid pointer?
{
    *p = 42;    
}                             
```

So it may be hard to get it right:

* Is the pointer valid? Invalid pointers should point to `nullptr` (nowhere). 
* Before referring to an object, test if it is valid (unless you *know* it is...). 
* Do you own memory? Don’t forget to delete (memory leak).
* Delete one or many objects? (UB)
* Have you released memory yet? Don’t delete twice (UB). 

When exceptions are thrown -- like `std::bad_alloc` (when no more dynamic memory is available) or `std::out_of_bounds` --, chances are to get it wrong. Nobody will release resources then. It’s best to avoid naked pointers here.

For zero to many objects there is `std::vector<T>`, for zero or one object there is `std::optional<T>`:

```cpp
std::optional<int> answer;
answer = 42; // *answer = 42 is also possible
if (answer)
{
    std::cout << *answer << '\n';
}
std::cout << answer.value_or(23) << '\n';
```

### Dangling pointers and references

Do not return a pointer or a reference to a local variable. It’s gone when function execution ends:

```cpp
int* dead_wrong()
{
    int i = 1;
    return &i; // compilers do not warn about this
}

int& also_wrong()
{
    int i = 2;
    return i; // compilers may warn about this
}
// ...
*dead_wrong() = 66;
also_wrong() = 23;
```

It may be more obvious in this code snippet:

```cpp
int p = nullptr;
{
	int i = 42;    
	p = &i;
}	// i is gone!
*p = 666;
```

However, a method is allowed to return a reference to a member of the class:

```cpp
class Vector
{
    int* data;
    int size;
    // ...
public:
    int& at(int index) 
    { 
        // test for index bounds... (omitted)
        return *(data+index);
    }
    // ...
};
```

Q: Why?

Exercise: Build your own Vector class (for educational purposes only).

### Multiple indirections

Pointers to pointers to pointers ... may make [good puzzles](http://nob.cs.ucdavis.edu/classes/ecs030-2015-04/handouts/ptrstew.html), but not maintainable code.