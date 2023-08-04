#pragma once

#include <cstddef> // for 'size_t'

template <typename T> 
class Allocator
{
	using Type = typename T::value_type; // user-defined value

	[[nodiscard]] Type* allocate(size_t num) return new Type[num]; // initialises the memory requested
	void deallocate(Type* p, size_t num) noexcept { // deallocate should not throw runtime exceptions
		delete(p); 
	}
};

/*
* 'value_type' meaning: https://cplusplus.com/forum/beginner/275487/
* 'using' logic/meaning: https://stackoverflow.com/questions/20790932/what-is-the-logic-behind-the-using-keyword-in-c
* New operator vs. operator new: https://www.geeksforgeeks.org/new-vs-operator-new-in-cpp/
* 
*/