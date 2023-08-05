#pragma once

#include <cstddef> // for 'size_t'

template <typename T> 
class BasicAllocator
{
	using Type = typename T::value_type; // user-defined value

	// constructor has nothing to do because it is empty (has no params) -> 'stateless'
	BasicAllocator() noexcept {}

	// copy constuctor is also stateless
	// this allows the value type of the object created to be consistent when copied 
	// There are explicit and implicit ways of doing this *.
	BasicAllocator(const BasicAllocator<Type>&) noexcept {}

	[[nodiscard]] Type* allocate(size_t num) return new Type[num]; // initialises the memory requested
	void deallocate(Type* p, size_t num) noexcept { // deallocate should not throw runtime exceptions
		delete(p); 
	}
};

/*
* What is a constructor?: https://en.cppreference.com/w/cpp/language/constructor
* 'value_type' meaning: https://cplusplus.com/forum/beginner/275487/
* 'using' logic/meaning: https://stackoverflow.com/questions/20790932/what-is-the-logic-behind-the-using-keyword-in-c
* New operator vs. operator new: https://www.geeksforgeeks.org/new-vs-operator-new-in-cpp/
* '[[nodiscard]]' meaning: throws exception if function does not return anything (is unused).
* 'stateless': A class if stateless if it has no non-static members or virtual functions.
* 'static': https://www.geeksforgeeks.org/cpp-static-data-members/ 
* 'virtual': A function which can be overwritten in a class derived from the current one.
* 'noexcept': https://en.cppreference.com/w/cpp/language/noexcept_spec
* Different forms of copy constructors: https://stackoverflow.com/questions/32537994/c-template-copy-constructor-on-template-class
*
*/