# CPP08

## Main topics

```
Templated containers, iterators, algorithms
```

### ex00 – easyfind
Tiny function template working with any integer container + `<algorithm>`.
- `template <typename T> typename T::iterator	easyfind(T &cont, int match)` refresh the memory about templates and `typename` keyword.
- `std::find` is part of the C++ Standard Library and is used to search for a specific value within a range defined by two iterators. If it fails to find the value, it returns the `end` iterator of the range.

### ex01 – Span
Your own class that internally uses an STL container and algorithms to compute distances.
- for the first time, I used `inline` for a getter function for faster compilation.
- I used `std::vector` so its faster to sort and/or access elements randomly (`min/max_element`).
- `std::vector<int>::iterator` is an object that lets you traverse and access elements of a `std::vector<int>` (O(1) access time). It works with standard algorithms like `std::sort`, `std::min_element`, and `std::max_element`.
- `std::sort`, `.front()`, `.back()`, `std::min_element`, and `std::max_element` are all part of the C++ Standard Library and provide efficient ways to manipulate and access elements in containers like `std::vector`.

I tried to sort it on the push_back (with hope of optimizing) but it was slower than just sorting when needed (in the smallestSpan function). Because the sorting alg is the most time consuming part of the code.

### ex02 – MutantStack
Extend `std::stack` so that you can iterate over it (expose iterators of the underlying container).