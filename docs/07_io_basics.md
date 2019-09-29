# Input/output stream basics

```cpp
#include <iostream>
```
defines streams `std::cin`, `std::cout` for in- and output and `std::cerr` for error messages.

## Redirecting console I/O

By using `<` and `>` on command line, I/O streams are redirected to files:
```
prog < readinput.txt > writeoutput.txt
prog >> appendoutput.txt
prog 2> errorlog.txt
program1 | program2
```
Pipes `|` connect the output stream of `program1` to the input stream of `program2`.

## Input idioms
Input data have to fit to input variables -- you can't read `xyz` into an `int`.
If an error occurs, no further data are processed.

```cpp
if (std::cin >> x >> y) ...

while (std::cin >> x >> y) ...
```

"Read and test"
* read some values `x`,`y` from console input
* test, if they were read successfully

"While reading input was successful"
* as long as data fit to types of x and y,
* until END OF FILE: type Ctrl+D (Unix) / Ctrl+Z Enter (Windows) on keyboard.



Whitespace characters (space `' '` / tab `'\t'` / newline `'\n'`) act as data delimiters, they are discarded by `operator>>`.

Read (possibly long) text into string of characters:

```cpp
std::string s;
std::cin >> s;             // skips whitespace at beginning, reads text until whitespace
                           // '\n' is not processed yet!
std::cin.ignore(100,'\n'); // skip up to 100 chars until (including) '\n'
std::getline(std::cin, s); // read until end of line '\n', including whitespace
```
Get lines of data, process them later for more robust input.
```cpp
while (std::getline(std::cin, s)) ...
```

## Reading from / writing to string streams
```cpp
#include <sstream>
```
Text strings can be used as input stream
```cpp
std::string s = "1213 45";
auto is = std::istringstream{s};
is >> x >> y;
```
and written to an output string stream
```cpp
auto os = std::ostringstream{};
os << x << ' ' << y;
auto s2 = os.str(); // return output as string
```
## Reading from / writing to text files
```cpp
#include <fstream>
```
```cpp
{
	auto in = std::ifstream{"inputfilename.txt"};
	if (in) in >> x >> y;

	auto out = std::ofstream{"outputfilename.txt"};
	if (out) out << x << ' ' << y;
	// in.close();  // done automatically
	// out.close();
}
```
Files for input and output get automatically closed when reaching end of the defining block.
Beware: Opening a file for output erases any containing data.

If something goes wrong when opening a file, the stream is in bad state.
Some possible reasons:
* file path not correct (relative to active directory)
* no filesystem access rights to read, create, or write file
* file already opened/locked by (another) process
