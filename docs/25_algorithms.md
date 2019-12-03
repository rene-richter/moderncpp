# Algorithms
## 

Q: An algorithm is ... ?

The C++ standard library comes with some (about 100) predefined algorithms, which
* do typical programming tasks like searching, modifying, and rearranging sequences of data,
* work on a range of data, marked by a begin and an end iterator,
* return a result or write results into (another) given range of data.

Iterators define the interface between algorithms and containers. 
They reduce programming complexity from (k algorithms for m container types of n types of data => k x m x n programs) to (k algorithms for j iterator categories
+ m container types).

Containers/sequences provide iterator categories with different capabilities.
They can traverse data
* forward,
* bidirectional, or by
* random access
with implications on the _efficiency_ of algorithms.

Example: Rotate a sequence of data by a given number of elements.
Exercise: Implement an efficient algorithm for each category of iterators.

## Time complexity

The number of necessary operations depends on how many (N) elements are in a sequence. Typical time complexities are (from fast to slow):

* logarithmic O(log N)
* linear O(N)
* linear-logarithmic O(N log N)
* quadratic O(N^2)
* exponential O(n!)

Example: A linear algorithm takes twice the time for twice number of data,
a quadratic algorithm four times as long.

Time complexity does not consider how long it takes to process one data element,
constant factors are abstracted away.
Nevertheless it is important if another algorithm of same complexity is faster by a factor of 2.

## Typical algorithmic tasks

Exercise: Solve the following tasks for a sequence of data, e.g. a string of characters:

* Print each element.
* Convert all characters of a string to lowercase.
* Replace all characters 'l' to 'r'.
* Remove all spaces form a string.
* Sort all characters in ascending asciibetical order.
* Discard characters that occure more than once, safe only unique (different) characters.
* Reorder the sequence of characters so that all vocals come at first.
* Replace all non-vocals by underscores.
* Reorder the vocals in every possible sequence (permutations).
* Reorder all elements in a randomized sequence.

## Further information

* CppCon 2019 talk: Conor Hoekstra: Algorithm Intuition. https://www.youtube.com/watch?v=pUEnO6SvAMo
* CppCon 2018 talk: Jonathan Boccara: 105 STL Algorithms in Less Than an Hour. https://www.youtube.com/watch?v=2olsGf6JIkU
* GoingNative 2013 talk: Sean Parent: C++ Seasoning. https://channel9.msdn.com/Events/GoingNative/2013/Cpp-Seasoning