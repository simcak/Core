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
- `std::vector<int>::iterator` is an iterator type — a lightweight, pointer-like object used to traverse and access elements of a `std::vector<int>`. For random-access iterators (like `std::vector<int>::iterator`) operations and iterator arithmetic are O(1). Iterators are compatible with standard algorithms such as `std::sort`, `std::min_element`, and `std::max_element`.
- `std::sort`, `.front()`, `.back()`, `std::min_element`, and `std::max_element` are all part of the C++ Standard Library and provide efficient ways to manipulate and access elements in containers like `std::vector`.

I tried to sort it on the push_back (with hope of optimizing) but it was slower than just sorting when needed (in the smallestSpan function). Because the sorting alg is the most time consuming part of the code.

### ex02 – MutantStack
Extend `std::stack` so that you can iterate over it (expose iterators of the underlying container).
- first time seeing `template<class T>` syntax = its the same as `template<typename T>`.
- `std::stack` is a container adaptor that provides a stack (LIFO - Last In, First Out) interface. It is built on top of other container types (i read in man than on top of `std::deque`) and provides stack-specific operations such as `push`, `pop`, and `top`.
- **container adaptor** is a class template that provides a specific interface (like stack, queue, or priority queue) by using an underlying container (like `std::vector`, `std::deque`, or `std::list`) to store the actual elements.
- we simply expose the iterators of the underlying container (by default `std::deque`) using `this->c.begin()` and `this->c.end()`. Those protected members are already there in the `std::stack` class and we simply access them through inheritance.
- `typedef typename` is just telling that we are using aliases for `std::stack<T>::container_type`. From `container_type` we can get the (const_)iterator type of the underlying container.