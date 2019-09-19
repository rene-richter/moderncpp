# Building blocks of imperative programs
## Algorithm -- a sequence of statements

* program (or algorithm) = sequence of statements, executed in a given order
* some statements to be executed only when some condition is met
* some have to be repeated many times or skipped completely
* function: named block of statements, transforming some given input (parameters) into an output (returning a result)

## Selection -- decide what to do

```cpp
	if (isLeapYear(year))
	{
		std::cout << year << " is a leapyear\n";
	}
	else
	{
		std::cout << year << " is not a leapyear\n";
	}
```
The `else`branch is optional.
If more than two *alternatives* are needed, nest if-statements or write a `if (...) ... else if ...`-ladder.

## Iteration -- do it again
The body of a *loop* is executed when the *condition* at the start of the loop is true.
After that the loop condition is evaluated again. 
When the condition fails, program execution continues after the end of the iteration statement.
```cpp
	auto year = 2017;
	while (!isLeapYear(year))
	{
		std::cout << year << " is not a leapyear\n";
		++year;
	}
	std::cout << year << " is not a leapyear\n";
```
A `do { ... } while (condition);` decides after executing the loop body whether to repeat the loop body again.

Loop-*init*, loop-*condition*, and *increment* can be bundled like this:
```cpp
	for (auto year = 2017; year < 2030; ++year)
	{
		std::cout << year << "\n";
	}
```
but variables defined inside the for-init statement  like `year` are gone after leaving the loop.
`for(;;) ...` means `while(true) ...`, i.e. *forever*.

for each value in a sequence or *range* (called *range-for loop*):
```cpp
	for (auto year : {2017, 2018, 2019, 2020, 2100})
	{
		std::cout << year << "\n";
	}
```

## Function -- same procedure as last year

* an algorithm in itself, the *function body* contains a sequence of statements
* a *pure* function returns the same result when given same input, has no *side effects*
* *return type* can be *auto*matically deduced from returned value or  *expression*

```cpp
auto isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}
```

A function returning no result (a *procedure*) is of type `void`:

```cpp
void print(int year)
{
	std::cout << year << "\n";
}
```
Side effects can change the behaviour / result of a function:
* reading input from / writing output to console, files or data bases
* changing values declared outside the function

TODO: examples, exercises
