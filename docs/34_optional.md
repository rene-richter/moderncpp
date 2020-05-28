# Nullable types

Sometimes a value can, but does not have to exist (cardinality: zero or one). Using a vector would be overkill and misleading. `std::optional<T>` provides a solution for this situation.

```cpp
struct Person
{
    std::string name, firstname;
    std::optional<std::string> title;
};

auto show(Person p)
{
    if (p.title) std::cout << *(p.title) << ' ';
    std::cout << p.name << ", " << p.firstname;    
}
```

Optional return values are great when not finding a result is a possible outcome, but not an error or exception:

```cpp
std::optional<Person> find(Database db, Request r)
{
    // ...
    if (!result) return {}; // std::nullopt
    // ...
    return person_in_db;
}
```

`std::optional<T>` mimics the pointer syntax without dynamically allocating memory:

```cpp
std::optional<int> answer; // std::nullopt
*answer = 42;
if (answer) std::cout << *answer;
```

Do not read a value before assignment, it will result in undefined behavior. By calling `o.value_or(x)` you can present an alternative value. Unfortunately, `std::optional<T>` does not allow other functional style [continuations](https://github.com/TartanLlama/optional) like `o.map(function).and_then(func2)` [up to now](https://wg21.tartanllama.xyz/monadic-optional). For a more complete documentation see [cppreference](https://en.cppreference.com/w/cpp/utility/optional).

Q: Find other use cases for `std::optional<T>`. What would be alternatives? Which solution would you prefer?