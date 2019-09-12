# Building and testing by example
## Programming task
A function declared as
```cpp
bool isLeapYear(int year);
```
in header `gregorian.h` is needed for this program leapyear.cpp:
```cpp
#include <iostream>
#include "gregorian.h"

int main()
{
	int year;
	std::cin >> year;
	std::cout << year << ' ' 
		<< std::boolalpha << isLeapYear(year) << '\n';
}
```

## Code requirements in automated tests first
Download the latest `doctest.h` from https://github.com/onqtam/doctest .
Describe requirements for Gregorian calendar in leapyeartests.cpp:
```cpp
#include "doctest.h"
#include "gregorian.h"

TEST_CASE("years not divisible by 4 are not leap years")
{
	CHECK(isLeapYear(2019) == false);
	CHECK(isLeapYear(2021) == false);
	CHECK(isLeapYear(2022) == false);
	CHECK(isLeapYear(2023) == false);
	CHECK(isLeapYear(2025) == false);
	CHECK(isLeapYear(2026) == false);
	CHECK(isLeapYear(2027) == false);
	CHECK(isLeapYear(2099) == false);
}

TEST_CASE("years divisible by 4 are leap years")
{
	CHECK(isLeapYear(2020) == true);
	CHECK(isLeapYear(2024) == true);
	CHECK(isLeapYear(2028) == true);
	CHECK(isLeapYear(2096) == true);
}

TEST_CASE("years divisible by 100 are not leap years")
{
	CHECK(isLeapYear(1900) == false);
	CHECK(isLeapYear(2100) == false);
	CHECK(isLeapYear(2200) == false);
	CHECK(isLeapYear(2300) == false);
	CHECK(isLeapYear(2500) == false);
}

TEST_CASE("years divisible by 400 are leap years")
{
	CHECK(isLeapYear(2000) == true);
	CHECK(isLeapYear(2400) == true);
}
```
Add a testmain.cpp:
```cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
```

## CMake build script
Write a CMake project description into CMakeLists.txt:
```txt

cmake_minimum_required (VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

project (LeapYearDemo)

add_executable(myprogram leapyear.cpp gregorian.cpp)
add_executable(testleapyear testmain.cpp leapyeartests.cpp gregorian.cpp)

add_test(leapyear testleapyear)
```
Create a build directory and let CMake create Makefiles or project files appropriate for your compiler:
```
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
```

## Start building and testing
```
cmake -G "MinGW Makefiles" ..
```
will obviously fail: gregorian.cpp does not exist.
Take an engineer's approach to programming: Start debugging an empty file.

Create an empty file gregorian.cpp. Redo the CMake command. It succeeds. 
Building executables with
```
cmake --build .
```
fails with a linker error: function isLeapYear() does not exist yet.

## A stub implementation
A minimal version of gregorian.cpp, which is correct for about 75% of all years:
```cpp
bool isLeapYear(int year)
{
	return false;
}
```
compiles, passes 2 of 4 tests:
```
ctest
ctest -V
```
The first command fails: Not all tests pass.
The verbose option `-V` gives details about which test failed and why.

## Improving implementation
Refine the implementation, build and `ctest` again until all tests pass ("are green").
```cpp
// TODO: years divisible by 4, 100, 400
```
Now 
```
myprogram
```
should work correctly. Done.

## Refactoring
Done? Why so much test code for such a simple function?

Sometimes later somebody finds a problem: this heavily used function is too slow.
It does a lot of computation before running into the trivial case in the end.

Change implementation without creating wrong results (so-called regressions).
All tests must stay green.
```cpp
// TODO: reorder conditions, study assembler output on godbolt.org, measure performance
```
Hopefully, the new implementation will be faster -- and stay correct.
