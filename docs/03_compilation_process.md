# A sketch of the compilation and build process
Caveat: The description given here may vary in detail on different systems.
GCC is used as an example. 
The simplest command to compile a program and build an executable is something like

`g++ source.cpp -o executable`

Real world programs consist of many source files.
As more gets involved, the process gets more complicated.

## Compilation step

`g++ -c source.cpp`

The unit of translation is a sourcefile (`*.cpp` or `*.cc`).

### Preprocessing
* includes `<headers>`, `*.h` files 
* type definitions and declaration of functions, that have to be known in multiple source files 
* replaces text defined in macros
resulting in an input stream to the compiler

Preprocessing is expensive: Headers can be very large.
It will eventually be replaced by the new C++20 module system.

### Compiling
Compiler output is an "object file" (`*.o` or `*.obj`).

Object files can be collected into static or shared object (dynamic) libraries.

## Linking

`gcc *.o -llibraryxyz -o executable`

Object files and libraries, eventually from different programming languages, are connected to an executable program.
One translation unit has to contain the `main()` function.

# Build systems
Build systems keep track of which sources have changed (or the headers they include).
Then they have to be to compiled again.
When all dependencies are updated, a new executable can be linked.

IDEs have their own way of project file,
start the build process by clicking a button or selecting a menu item. 
`make` is command line build tool. 
`Makefile`s contain descriptions of dependencies and commands needed to build executables. 
However, they are not portable: Syntax, commands and options differ from compiler to compiler. 

## CMake
Portable way to describe dependencies and organize these steps.
