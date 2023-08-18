#include "pch.h"
#include "gtest/gtest.h"
#include "../custom-allocators/include/basic_allocator.h"
#include <vector>

namespace project_allocator 
{
	class BasicAllocationTest : public ::testing::Test {

	public:
		void SetUp() override {} // construct
		void TearDown() override {}

	protected:
		BasicAllocator<unsigned int> ba1_;
		BasicAllocator<char> ba2_;
	};
	TEST_F(BasicAllocationTest, HandlesTooManyBytesInput)
	{
		constexpr size_t num = (std::numeric_limits<size_t>::max() / sizeof(unsigned int)) + 1;
		EXPECT_THROW({
			if (ba1_.allocate(num)); // allocates only if the return pointer is not NULL
			}, std::bad_array_new_length);
	}
	TEST_F(BasicAllocationTest, IsBytesEqual)
	{
		constexpr unsigned int num = 1; // allocates 4 bytes
		char c[4]{ 'a', 'b', 'c', 'd' }; // should also allocate 4 bytes despite type difference

		if (ba1_.allocate(sizeof(num)) && ba2_.allocate(sizeof(c)))
		{
			EXPECT_TRUE(ba1_ == ba2_);
		}
	}
}

/* Notes:
* Cannot use angled brackets '<' or '>' within macros
* 'override' allows the function i.e., SetUp to be changed from its base/parent class
* Global SetUp & TearDown: http://google.github.io/googletest/advanced.html#global-set-up-and-tear-down
*/