#pragma once

#include <iostream> // for 'std::cout'
#include <cstddef> // for 'size_t'
#include <new> // for 'std::bad_alloc'
#include <limits> // for 'std::numeric_limits'

template <typename T> 
class BasicAllocator
{
public:
	typedef T value_type; // user-defined value

	// constructor has nothing to do -> 'stateless'
	BasicAllocator() noexcept {}

	// copy constuctor is also stateless
	// this allows the value type of the object created to be consistent when copied 
	// There are explicit and implicit ways of doing this *
	template<typename U> 
	BasicAllocator(const BasicAllocator<U>&) noexcept {}

	[[nodiscard]] T* allocate(size_t num) 
	{ 
		if (num > std::numeric_limits<std::size_t>::max() / sizeof(T)) 
		{
			throw std::bad_array_new_length();
		}
		
		auto p = new T[num]; 

		monitor(p, num, true);
		return p; // initialises the memory requested
	} 
	void deallocate(T* p, size_t num) noexcept // deallocate should not throw runtime exceptions
	{ 
		monitor(p, num, false);
		delete(p);  
	}
private: 
	void monitor(T* p, size_t num, bool is_alloc)
	{
		std::cout << (is_alloc ? "Allocated: " : "Deallocated: ") << sizeof(T) * num << ", at address -> " << &p << "\n";
	}
};

// See 'Relationship between instances' -> 'a1 == a2': https://en.cppreference.com/w/cpp/named_req/Allocator
// Checks to see if the storage of the allocator of type T
// can be used to deallocate storage of the same allocator of U. 
// Returns true if it can and false if it cannot. 
// It also should not throw any exceptions.

template <typename T1, typename T2> 
bool operator==(const BasicAllocator<T1>&, const BasicAllocator<T2>&) noexcept
{
	return true; 
}

template <typename T1, typename T2> 
bool operator!= (const BasicAllocator<T1>&, const BasicAllocator<T2>&) noexcept
{
	return false; 
}

/*
* '&': A reference to the address of the object. 
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
* 'bool operator==': https://stackoverflow.com/questions/23162870/c-bool-operator
*/