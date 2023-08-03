#pragma once

template <typename T> class Allocator
{
public: 
	
	// Constructor 
	Allocator() = default; // default = create objects of this class without an initialiser pg 438

	[[nodiscard]] constexpr T* allocate(size_t n) 
	{ // allocate memory for n objects of type T
		return new (n * sizeof(T)); // pointer to the first of n objects allocated in memory but have not been constructed yet
	}

	void deallocate(T* ptr, size_t n) noexcept 
	{
		return delete(ptr, n * sizeof(T));
	}
};