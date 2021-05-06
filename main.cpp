// g++ -O2 -msse3 MatrixMN.cpp main.cpp
#include "impl.h"
#include "MatrixMN.h"
#include <iostream>

using namespace std;

int main()
{
	__m128d d = _mm_set_pd(1.0, 2.0);
	print128d(d);

	math::MatrixMN mat1(2, 3);
	cout << "mat1 : " << mat1 << endl;

	// Test 1
	double test_src1[4] = {0, 1,
												 2, 3};
	double test_src2[4] = {0, 1,
												 2, 3};
	double testout[4];
	double expected[4] = {2, 3,
												6, 11};

	sse_multiply(test_src1, test_src1, testout, 2, 2, 2, 2);
	std::cout << "\n Test 1 : " << std::endl;
	print_array(testout, 4);

	/*
	// Test 2
	double test2_src1[16] = {0, 1, 2, 3,
													 4, 5, 6, 7,
													 8, 9, 10, 11,
													 12, 13, 14, 15};
	double test2_src2[16] = {0, 1, 2, 3,
													 4, 5, 6, 7,
													 8, 9, 10, 11,
													 12, 13, 14, 15};
	double test2out[16];
	double expected2[16] = {56, 62, 68, 74,
												 152, 174, 196, 218,
												 248, 286, 324, 362,
												 344, 398, 452, 506};

	sse_multiply(test2_src1, test2_src2, test2out, 4, 4, 4, 4);
	std::cout << "\n Test 2 : " << std::endl;
	print_array(test2out, 16);

	// Test 3
	double test3_src1[16] = {12, 27, 15, 18,
													 45, 18, 144, 55,
													 92, 45, 74, 9,
													 89, 5, 99, 127};
	double test3_src2[8] = {-12, 3,
													1.5, -5,
													4, 0,
													125.5, 2.7};
	double test3out[8];
	double expected3[8] = {2215.5, -50.4,
												6965.5, 193.5,
												389, 75.3,
												15274, 584.9};

	sse_multiply(test3_src1, test3_src2, test3out, 4, 4, 4, 2);
	std::cout << "\n Test 3 : " << std::endl;
	print_array(test3out, 8);
	*/
	return 0;
}