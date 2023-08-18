#include "pch.h"
#include "gtest/gtest.h"
#include "../custom-allocators/include/basic_allocator.h"
#include <vector>
TEST(AllocationTest, HandlesTooManyBytesInput)
{
	BasicAllocator<unsigned int> ba; // construct test obj
	constexpr size_t num = (std::numeric_limits<size_t>::max() / sizeof(unsigned int)) + 1;
	
	// cant do angled brackets '<' or '>' within macros 
	EXPECT_THROW({
		if (ba.allocate(num)); // allocates only the return pointer is not NULL
	}, std::bad_array_new_length);

}

