# C++ Basics

## Table of Contents
1. [Introduction](#introduction)
2. [Orthodox Canonical Form](#orthodox-canonical-form)
	- [Destructor](#destructor)
	- [Copy Constructor](#copy-constructor)
	- [Copy Assignment Operator](#copy-assignment-operator)
	- [Move Constructor](#move-constructor)
	- [Move Assignment Operator](#move-assignment-operator)
	- [Example](#example)
3. [Basic Syntax](#basic-syntax)
	- [Hello World](#hello-world)
	- [Variables and Data Types](#variables-and-data-types)
	- [Control Structures](#control-structures)
	  - [If-Else](#if-else)
	  - [For Loop](#for-loop)
	  - [While Loop](#while-loop)
4. [Functions](#functions)
5. [Pointers and References](#pointers-and-references)
	- [Pointers](#pointers)
	- [References](#references)
	- [Example Usage](#example-usage)
6. [Exception Handling](#exception-handling)
7. [Object-Oriented Programming (OOP)](#object-oriented-programming-oop)
8. [Memory Allocation](#memory-allocation)
	- [Stack Allocation](#stack-allocation)
	- [Heap Allocation](#heap-allocation)
9. [Conclusion](#conclusion)

## Introduction
C++ is a general-purpose programming language created by Bjarne Stroustrup as an extension of the C programming language. It is widely used for system/software development and game programming.

## Orthodox Canonical Form
The Orthodox Canonical Form, also known as the Rule of Five, is a set of guidelines in C++ for writing classes that manage resources. It ensures that resources such as dynamic memory, file handles, or network connections are properly managed and released. The Rule of Five states that if a class requires a user-defined destructor, copy constructor, copy assignment operator, move constructor, or move assignment operator, then it likely requires all five.

### Destructor
The destructor is responsible for cleaning up resources when an object goes out of scope or is deleted.

```cpp
~MyClass() {
	// Cleanup code
}
```

### Copy Constructor
The copy constructor initializes a new object as a copy of an existing object.

```cpp
MyClass(const MyClass& other) {
	// Copy initialization code
}
```

### Copy Assignment Operator
The copy assignment operator assigns the contents of one object to another existing object.

```cpp
MyClass& operator=(const MyClass& other) {
	if (this != &other) {
		// Copy assignment code
	}
	return *this;
}
```

### Move Constructor
The move constructor transfers resources from a temporary object to a new object.

```cpp
MyClass(MyClass&& other) noexcept {
	// Move initialization code
}
```

### Move Assignment Operator
The move assignment operator transfers resources from a temporary object to an existing object.

```cpp
MyClass& operator=(MyClass&& other) noexcept {
	if (this != &other) {
		// Move assignment code
	}
	return *this;
}
```

### Example
Here is an example of a class that follows the Orthodox Canonical Form:

```cpp
class MyClass {
private:
	int* data;

public:
	// Constructor
	MyClass(int value) : data(new int(value)) {}

	// Destructor
	~MyClass() {
		delete data;
	}

	// Copy Constructor
	MyClass(const MyClass& other) : data(new int(*other.data)) {}

	// Copy Assignment Operator
	MyClass& operator=(const MyClass& other) {
		if (this != &other) {
			delete data;
			data = new int(*other.data);
		}
		return *this;
	}

	// Move Constructor
	MyClass(MyClass&& other) noexcept : data(other.data) {
		other.data = nullptr;
	}

	// Move Assignment Operator
	MyClass& operator=(MyClass&& other) noexcept {
		if (this != &other) {
			delete data;
			data = other.data;
			other.data = nullptr;
		}
		return *this;
	}
};
```

By following the Orthodox Canonical Form, you ensure that your classes manage resources safely and efficiently, preventing resource leaks and undefined behavior.

## Basic Syntax
### Hello World
```cpp
#include <iostream>

int main() {
	std::cout << "Hello, World!" << std::endl;
	return 0;
}
```
- `#include <iostream>`: Includes the standard input-output stream library.
- `int main()`: The main function where execution begins.
- `std::cout`: Standard character output stream.
- `<<`: Stream insertion operator.
- `std::endl`: Ends the line.
### Variables and Data Types
```cpp
int			age = 25;
double		salary = 50000.50;
char		grade = 'A';
bool		isEmployed = true;
std::string	name = "John Doe";
```
- `int`: Integer type.
- `double`: Floating-point type.
- `char`: Character type.
- `bool`: Boolean type.
- `std::string`: String type from the standard library.

### Control Structures
#### If-Else
```cpp
if (age > 18) {
	std::cout << "Adult" << std::endl;
} else {
	std::cout << "Minor" << std::endl;
}
```

#### For Loop
```cpp
for (int i = 0; i < 5; i++) {
	std::cout << i << std::endl;
}
```

#### While Loop
```cpp
int i = 0;
while (i < 5) {
	std::cout << i << std::endl;
	i++;
}
```

## Functions
```cpp
int add(int a, int b) {
	return a + b;
}

int main() {
	int sum = add(5, 3);
	std::cout << "Sum: " << sum << std::endl;
	return 0;
}
```
- `int add(int a, int b)`: Function declaration and definition.
- `return`: Returns a value from the function.

## Pointers and References

### Pointers
Pointers are variables that store the memory address of another variable. They are used for dynamic memory allocation and to pass variables by reference.

```cpp
std::string str = "HI THIS IS BRAIN";
std::string *stringPTR = &str;
```
- `std::string *stringPTR = &str;`: Declares a pointer `stringPTR` that stores the address of the variable `str`.

### References
References are aliases for another variable. They conceptually act as constant pointers that are automatically dereferenced. Reference contains the address of the variable it refers to and cannot be `NULL`.
1) They must be initialized when they are created.
2) They cannot be changed to refer to another variable.

```cpp
std::string &stringREF = str;
```
- `std::string &stringREF = str;`: Declares a reference `stringREF` that refers to the variable `str`.

### Example Usage
```cpp
#include <iostream>

int main() {
	std::string str = "HI THIS IS BRAIN";
	std::string *stringPTR = &str;
	std::string &stringREF = str;

	std::cout << "Value of str: " << str << std::endl;
	std::cout << "Value pointed to by stringPTR: " << *stringPTR << std::endl;
	std::cout << "Value referred to by stringREF: " << stringREF << std::endl;

	return 0;
}
```
- `*stringPTR`: Dereferences the pointer to get the value of `str`.
- `stringREF`: Directly accesses the value of `str` through the reference.

## Exception Handling
Exception handling in C++ is done using `try`, `catch`, and `throw` keywords. It allows you to handle errors or exceptional situations in a controlled manner.

```cpp
#include <iostream>

int main() {
	try {
		int denominator = 0;
		if (denominator == 0) {
			throw std::runtime_error("Division by zero error");
		}
		int result = 10 / denominator;
		std::cout << "Result: " << result << std::endl;
	} catch (const std::runtime_error& e) {
		std::cerr << "Caught an exception: " << e.what() << std::endl;
	}
	return 0;
}
```
- `try`: Block of code to be tested for exceptions.
- `throw`: Throws an exception when a problem is detected.
- `catch`: Block of code that handles the exception.

In this example, if the denominator is zero, a `std::runtime_error` is thrown, and the `catch` block handles the exception by printing an error message.

## Object-Oriented Programming (OOP)
Object-Oriented Programming (OOP) is a programming paradigm based on the concept of "objects", which can contain data and code to manipulate that data. OOP aims to implement real-world entities like inheritance, polymorphism, encapsulation, and abstraction in programming.

- **Class**: A blueprint for creating objects. It defines a datatype by bundling data and methods that work on the data into one single unit.
- **Object**: An instance of a class. When a class is defined, no memory is allocated until an object of that class is created.
- **Encapsulation**: The bundling of data with the methods that operate on that data. It restricts direct access to some of an object's components.
- **Inheritance**: A mechanism where a new class inherits the properties and behavior of another class. It promotes code reusability.
- **Polymorphism**: The ability of different classes to be treated as instances of the same class through inheritance. It allows methods to do different things based on the object it is acting upon.
- **Abstraction**: The concept of hiding the complex implementation details and showing only the necessary features of an object.

```cpp
class Car {
public:
	std::string	brand;
	int			year;

	void display() {
		std::cout << "Brand: " << brand << ", Year: " << year << std::endl;
	}
};

int main() {
	Car car1;
	car1.brand = "Skoda";
	car1.year = 2025;
	car1.display();
	return 0;
}
```
- `class`: Defines a class.
- `public`: Access specifier.
- `std::string`: String type from the standard library.
- `car1`: Object of class `Car`.
- `display()`: Method to display the brand and year of the car.

### Memory Allocation
#### Stack Allocation
Stack allocation is used for static memory allocation, which is managed by the compiler. Variables allocated on the stack are automatically deallocated when they go out of scope.

```cpp
int main() {
	int x = 10; // Allocated on the stack
	std::cout << "Value of x: " << x << std::endl;
	return 0;
}
```

#### Heap Allocation
Heap allocation is used for dynamic memory allocation, which is managed by the programmer. Variables allocated on the heap must be manually deallocated using `delete`.

```cpp
int main() {
	int	*ptr = new int; // Allocated on the heap
	*ptr = 20;
	std::cout << "Value of *ptr: " << *ptr << std::endl;
	delete ptr; // Deallocate memory
	return 0;
}
```
- `new`: Allocates memory on the heap.
- `delete`: Deallocates memory on the heap.

## Conclusion
This README provides a brief overview of C++ basics, including syntax, control structures, functions, and object-oriented programming. For more detailed information, refer to C++ documentation and tutorials.