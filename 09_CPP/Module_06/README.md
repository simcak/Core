# Module 06 - Casting
In this module, we will explore the concept of casting in C++. Casting is the process of converting a variable from one type to another. This is particularly useful when working with inheritance and polymorphism.

## Quick recap of Inheritance and Polymorphism
**Inheritance** allows a class (derived / child class) to inherit properties and behaviors (methods) from another class (base / parent class). It inherits from public (multiple inheritance) and protected (single inheritance) members and does not inherit private members.

**Polymorphism** enables a derived class to be treated as a base class, allowing for dynamic method resolution. For example, polymorphism allows multiple same-named methods to exist in different classes, and the appropriate method is called based on the object type at runtime.

```cpp
class Base {
	public:
		virtual void foo() { std::cout << "Base\n"; }
};

class Derived : public Base {
	public:
		void foo() override { std::cout << "Derived\n"; }
};

Base* obj = new Derived();
obj->foo(); // writes out "Derived"
```

In OCF, the `(void)other;` is a no-op. It just tells the compiler: "I know this parameter is unused, that's intentional." because we dont copy anything from `other` to `this`.

## Types of Casting
There are four main types of casting in C++:

1. **Static Casting**: This is the most common type of casting. It is checked at compile-time and is used for conversions between compatible types.
```cpp
	int a = 5;
	double b = static_cast<double>(a);
```

2. **[Dynamic Casting](https://www.geeksforgeeks.org/cpp/dynamic-_cast-in-cpp/)**:
This type of casting is used for safely downcasting in inheritance hierarchies. It is checked at runtime and returns `nullptr` if the cast is not valid.
```cpp
	Base* base = new Derived();
	Derived* derived = dynamic_cast<Derived*>(base);
```

3. **Const Casting**: This type of casting is used to add or remove the `const` qualifier from a variable.
```cpp
	const int a = 5;
	int* b = const_cast<int*>(&a);
```

4. **Reinterpret Casting**: This type of casting is used for low-level reinterpreting of bit patterns. It is not type-safe and should be used with caution.
```cpp
	int a = 5;
	char* b = reinterpret_cast<char*>(&a);
```
