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
	cout <<  "mat1 : "<< mat1 << endl;

	return 0;
}