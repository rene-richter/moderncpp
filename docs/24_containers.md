# Data containers

> When choosing a container remember: vector is best.
> Leave a comment if you choose from the rest.
>
> > --- Tony van Eerd: [PostModern C++](https://www.youtube.com/watch?v=Zx_Tjp9WIII), C++ Meeting Group, Prague (2020)

C++ standard library _containers_ 

* store data of a selected type, 
* copy or move data around,
* differ in the way they arrange data,
* have different methods for access/insert/remove operations 
* with different time complexities, 
* provide common interface through _iterators_,
* allocate memory for data and release it automatically (no garbage collectors needed).

There are
* sequential containers:
	* array-like containers: `array` `vector` `deque`
	* list containers: `list` `forward_list`
* associative containers
	* (ordered) containers: `set` `multiset` `map` `multimap`
	* unordered (hash) containers: `unordered_set` ...

```
array<T,5>           [1|2|3|4|5]
vector<T>            [1|2|3|4|5] <->
deque<T>         <-> [1|2|3|4|5] <->
list<T>          [1]-[2]-[3]-[4]-[5]
forward_list<T>  [1]->[2]->[3]->
set<T>           {1 2 3 4 5}
multiset<T>      {1 2 3 3 5}
map<K, V>        Mueller : 3373721 
                 Schulze : 4632536 
```
see also: [Kurzreferenz C++](https://namespace-cpp.de/std/lib/exe/fetch.php/kurzref.pdf), p.3

Q: 
* Characterize each container type. 
	* When would you use which container type?
	* Discuss their pro's and con's.
* How expensive is it to
	* copy
	* return
	* pass a container by value with respect to the amount of stored data? 
* Prove your findings by measuring (profiling).

## Array-like containers
a block of memory with 
random access by index operator `seq[i]`:
```cpp
auto sequence = std::array<int,5>{ 1, 4, 9, 16, 25 };
	
for (size_t i = 0; i != sequence.size(); ++i)
{
	std::cout << i << " :\t" << sequence[i] << '\n'; 
}
```

## Uniform iterator access
```
     iter ++ -->
     |	 
     V
[1|2|3|4|5]
 ^         ^
 |         |
 first     last
```
Iterators provide a "pointer-like" access to data for all containers:
* data access at a selected position by `*iter`
* advancing to the next position by `++iter` 
The `first` and `last` iterator pairs 
* refer to a _half-open range_ of data,
* are retrieved by `begin()` and `end()` functions (or methods) applied to a container.

```cpp
auto first = begin(sequence);
auto last  = end(sequence);

for (auto iter = first; iter != last; ++iter)
{
	auto element = *iter;
	
	std::cout << element << ' ';
}
```
(mostly) equivalent to _range-based for loop_:
```cpp
for (auto element : sequence)
{
	std::cout << element << ' ';		
}
```
Q:
* What's the point of the iterator abstraction?

## Associative containers
Sorted containers `set<K>` and `map<K,V>` 
(aka _dictionary_ or _associative array_) etc.

* always keep data in an "less-than" ordered sequence of _keys_.
* Inserting, finding, and removing data shall be done in O(log n) time.
  So they can be implemented as balanced binary search tree (_red-black tree_).
* `multiset` and `multimap` can store multiple values for one key.

Unordered containers
* require a `std::hash<K>` defined
* to find the bucket for the data key.

Q:
* What`s a binary search tree? 
* Why balanced trees? 
* What's a red-black tree?
* What's a hash set/hash table?
* Which time complexity provide hashed data accesses?
* When to use them?

## Container adapters
* LIFO storage: `stack<T>`
* FIFO storage: `queue<T>`
* "Me first!": `priority_queue<T>`

Q:
* When to use them? Find typical applications.
