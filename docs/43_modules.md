# Modules

## Farewell to cpp preprocessor?

Programs consist of (many) translation units. `#include`s

* slow down compilation, headers must be compiled again and again,
* can be order dependent or cyclic, have to prevent multiple inclusion
* may violate the *One Definition Rule*
* do not encapsulate implementation details (Pimpl idiom, macros, resulting in uglified names in libraries)

C++20 answers these problems by *modules*.

## Import modules

``` cpp
import hello;
int main()
{
    greeting();
}
```

Module names can be divided by periods: `std.core` and `std.core.algorithm` would be independent modules. The standard library isn't modularized yet. Module names `std`, eventually followed by digits, are reserved. 

## Module interface

A module consists of exactly one module interface unit.

``` cpp
export module hello;
export void greeting();
```

and zero or many implementation units. The `export` keyword marks single declarations of classes, functions, templates, namespaces or `export {...}` blocks. Macros are not exported.

## Module implementation

``` cpp
module hello;
import <iostream>;
void greeting() { std::cout < "Hello, world\n"; }
```

Module name and `import`statements precede all other declarations. All names declared in the interface can be referred.

## Reexport

``` cpp
export module noodles;
export import spaghetti;
...
```

## Partitions

``` cpp
export module geometry:vector;
...
```

have a colon `:` in their name, are importable by their owner module only, are allowed for reexport:

``` cpp
export module geometry;
export import :vector;
```

## Module binding

Variables defined in interfaces are visible in all translation units of the same module, and don not collide with other external variables, if not exported:

``` cpp
export module walk:position;
int x = 0;
```

``` cpp
export module walk:steps;
import :position;

export void forward() { ++x; }
export void back() { --x; }
```

``` cpp
export module walk;
export import :steps;
import :position;

export auto get_position() { return x; }
```

``` cpp
// does not collide with x in module walk:
int x = 7;
```

## Compilation process

Module interface units must be processed before import into some implementation defined format (compiled module interface `*.bmi`, `*.ifc`). Interface units as well as implementation units are translation units, resulting in (`*.o`, `*.obj`) files. 

| translation unit      |                       | file extension     | results in                 |
| --------------------- | --------------------- | ------------------ | -------------------------- |
| module interface      | `export module name;` | `*.cppm` / `*.ixx` | `.o` and `*.bmi` / `*.ifc` |
| importable header     | `import <header>;`    |                    |                            |
|                       | `import “header”;`    | `*.hpp` / `*.h`    | `.o` and `*.bmi` / `*.ifc` |
| module implementation | `module name;`        | `*.cpp`            | `.o`                       |
| consumer              | `import name;`        | `*.cpp`            | `.o`                       |

```
*.ixx -> Prepocess/Compile -> *.obj  Libraries           
            v                  \    / 
           *.ifc                Link -> program
            v                  /
*.cpp -> Compile -> *.obj
```

[Compiler support](http://en.cppreference.com/w/cpp/compiler_support) is in early experimental stages at this moment (July 2020).