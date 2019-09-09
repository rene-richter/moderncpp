# 01 Introduction to Modern C++(17)

2019 Schülerrechenzentrum Dresden https://srz.tu-dresden.de/ ,
Dr. René Richter https://namespace-cpp.de/std/doku.php/modern_cpp

intended audience: newbies and programmers, who know
* other languages or
* "old style" C++

promotion video Bjarne Stroustrup:
https://isocpp.org/blog/2019/08/invisible-engine-of-everything

## A short C++ history
* 1980 C with classes (Bjarne Stroustrup), ideas from SIMULA
* 1983 named C++
* 1990 standardization in ANSI and ISO starts
* 1998 Standard ISO 14882, inofficially called `C++98`
* 2011 `C++11` <-- "Modern C++"
* 2014 `C++14`
* 2017 `C++17`
  * <-- we are here
* 2020 `C++20`
* 2023 ...

## Modern C++
* 2000--2010 "lost years" of scripting languages
* operations per Watt in data centers, battery life in mobile devices
* 2005 Herb Sutter: The Free Lunch Is Over ![Free Lunch Is Over](http://www.gotw.ca/images/CPU.png)
* need for efficiency, concurrent programming
* close to hardware *and* high level abstractions
* modern: make programming easier not only for experts
* increasing activity in ISO WG21 standard committee since 2011
[Herb Sutter:  https://herbsutter.com/2019/07/20/trip-report-summer-iso-c-standards-meeting-cologne/ ]
![WG21](https://herbsutter.files.wordpress.com/2019/07/wg21-attendance-2019-07.jpg)

## First steps
### The smallest "program"
```cpp
int main(){}
```
does nothing but returning a number to the operating system (0 on common systems or error code).

### Hello, world
is also not "a program" but more of a test for compiler or IDE:
```cpp
#include <iostream>
int main()
{
  std::cout << "Hello, world!\n";
}
```
try it on https://wandbox.org online compiler: edit/compile/run cycle

## Toolbox
* editor
	* Code::Blocks
	* MS Visual Studio Code
	* Notepad++ (Windows)
	* Vim, Emacs, ...
* compiler
	* GCC (Linux, Windows)
	* Clang (iOS, Linux)
	* MS Visual C++ (Windows)
* build tool
	* CMake, ...
* version control
	* Git, Mercurial, ...
* debugger, package manager, ...

... or a huge IDE (MS Visual Studio, Windows)?

## Online resources
* https://wandbox.org online compiler
* https://godbolt.org compiler explorer: How do various compilers turn your code into assembler?
* https://en.cppreference.com
* https://isocpp.org

# Disclaimer
* content will be heavily subjective, incomplet_, and incorre~~k~~t
* no guaranteed date of completion

Nevertheless, suggestions and issues are welcome.
