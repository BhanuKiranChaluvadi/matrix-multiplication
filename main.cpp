// g++ -O2 -msse3 main.cpp
#include "impl.h"
#include <iostream>

using namespace std;

int main()
{
	// Test 1
	double test_src1[4] = {0, 1,
												 2, 3};
	double test_src2[4] = {0, 1,
												 2, 3};
	double testout[4];
	double expected[4] = {2, 3,
												6, 11};

	sse_multiply(test_src1, test_src2, testout, 2, 2, 2, 2);
	std::cout << "\n Test 1 : " << std::endl;
	print_array(testout, 4);

	// Test 2 : Negative
	double test2_src1[4] = {0, -1,
													2, 3};
	double test2_src2[4] = {0, 1,
													2, -3};
	double test2out[4];
	double expected2[4] = {-2, 3,
												 6, -7};

	sse_multiply(test2_src1, test2_src2, test2out, 2, 2, 2, 2);
	std::cout << "\n Test 2 : " << std::endl;
	print_array(test2out, 4);

	// Test 3
	double test3_src1[16] = {0, 1, 2, 3,
													 4, 5, 6, 7,
													 8, 9, 10, 11,
													 12, 13, 14, 15};
	double test3_src2[16] = {0, 1, 2, 3,
													 4, 5, 6, 7,
													 8, 9, 10, 11,
													 12, 13, 14, 15};
	double test3out[16];
	double expected3[16] = {56, 62, 68, 74,
													152, 174, 196, 218,
													248, 286, 324, 362,
													344, 398, 452, 506};

	sse_multiply(test3_src1, test3_src2, test3out, 4, 4, 4, 4);
	std::cout << "\n Test 3 : " << std::endl;
	print_array(test2out, 16);

	double test4_src1[16] = {0, 1, 2, 3,
													 4, 5, 6, 7,
													 8, 9, 10, 11,
													 12, 13, 14, 15};
	double test4_src2[8] = {0, 1,
													2, 3,
													4, 5,
													6, 7};
	double test4out[8];
	double expected4[8] = {28, 34,
												 76, 98,
												 124, 162,
												 172, 226};

	sse_multiply(test4_src1, test4_src2, test4out, 4, 4, 2, 4);
	std::cout << "\n Test 4 : " << std::endl;
	print_array(test4out, 8);

	// Test 5
	double test5_src1[16] = {12, 27, 15, 18,
													 45, 18, 144, 55,
													 92, 45, 74, 9,
													 89, 5, 99, 127};
	double test5_src2[8] = {-12, 3,
													1.5, -5,
													4, 0,
													125.5, 2.7};
	double test5out[8];
	double expected5[8] = {2215.5, -50.4,
												 6965.5, 193.5,
												 389, 75.3,
												 15274, 584.9};

	sse_multiply(test5_src1, test5_src2, test5out, 4, 4, 2, 4);
	std::cout << "\n Test 5 : " << std::endl;
	print_array(test5out, 8);

	return 0;
}