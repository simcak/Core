# Module 05 - Repetition and Exceptions == Bureaucrats

This exercise focuses on exception handling using `try`/`catch` blocks and basic class design in C++.
We will learn how to properly manage errors and design robust classes that handle exceptional situations gracefully.

`try`/`catch` blocks shouldn't containg throw inside them. Neither one function lower. It should be: 
```cpp
myFunctionThatThrows() {
	throw std::runtime_error("An error occurred");
}

myFunction() {
	myFunctionThatThrows();
}

try {
	myFunction(); // function that doesn't throw
} catch (const std::exception &e) {
	// handle exception
}
```
In our exercise we use the naughty implementation that throws inside the `try`/`catch` block. That is not a good practice but Module 05 is about exceptions and not about good practices. It is also too easy to implement the good practice. So in the future, those cases will be handeled with if/else conditions and return values.

Wrong but our exercise implementation:
```cpp
void	Bureaucrat::decrementGrade() {
	try {
		if (getGrade() + 1 > GRADE_MIN)
			throw Bureaucrat::GradeTooLowException();
		_grade++;
	}
	catch(const std::exception& e) {
		std::cout << BREXC << getName() << "cannot ⬇️ decrement because: " <<
		e.what() << std::endl;
	}
}
```
We used it to avoid trying and catching in the main function. That leads to a lot of code duplication in 'main.cpp'.

Try/catch/throw in constructors:
```cpp
// correct and clean implementation:
Bureaucrat::Bureaucrat(const std::string &name, unsigned int grade) : _name(name) {
	if (grade < GRADE_MAX)
		throw Bureaucrat::GradeTooHighException();
	if (grade > GRADE_MIN)
		throw Bureaucrat::GradeTooLowException();
	_grade = grade;
}

// correct but not clean implementation:
Bureaucrat::Bureaucrat(const std::string &name, unsigned int grade) : _name(name) {
	try {
		if (grade < GRADE_MAX)
			throw Bureaucrat::GradeTooHighException();
		if (grade > GRADE_MIN)
			throw Bureaucrat::GradeTooLowException();
		_grade = grade;
	}
	catch(const std::exception& e) {
		std::cout << e.what() << std::endl;
		throw ; // !!
		// we re-throw (propagate) the exception up where we have to catch it again - so it is not nice but works and saves us one line of code upper in catch
	}
}

// wrong implementation - don't catch in constructor:
Bureaucrat::Bureaucrat(const std::string &name, unsigned int grade) : _name(name) {
		try {
		if (grade < GRADE_MAX)
			throw Bureaucrat::GradeTooHighException();
		if (grade > GRADE_MIN)
			throw Bureaucrat::GradeTooLowException();
		_grade = grade;
	}
	catch(const std::exception& e) {
		std::cout << e.what() << std::endl;
		// !! we don't re-throw - so the exception is lost and the object is created in an invalid state
	}
}
```

### Benefits of using exceptions:
- Separates error handling code from regular code, improving readability.
- Avoid multiple return values for error handling - mainly in deeper call stacks.

### Warnings:
- We don't use it here correctly - the throw, try and catch blocks are not implemented consistently.