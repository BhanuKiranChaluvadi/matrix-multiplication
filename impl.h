
#include <emmintrin.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

void print128d(__m128d var)
{
	double v64val[2];
	memcpy(v64val, &var, sizeof(v64val));
	printf("%lf %lf\n", v64val[1], v64val[0]);
}

void print_array(double *src, int size)
{
	for (int i = 0; i < size; ++i)
	{
		std::cout << *(src + i) << std::endl;
	}
}

void naive_multiply(double *src1, double *src2, double *dst, int src1_w, int src1_h, int src2_w, int src2_h)
{
	memset(dst, 0, sizeof(int) * src1_h * src2_w);

	for (int i = 0; i < src1_h; ++i)
	{
		for (int j = 0; j < src2_w; ++j)
		{
			for (int k = 0; k < src2_h; ++k)
			{
				dst[i * src2_w + j] += src1[i * src1_w + k] * src2[k * src2_w + j];
			}
		}
	}
}

void sse_multiply(double *src1, double *src2, double *dst, int src1_w, int src1_h, int src2_w, int src2_h)
{
	for (int x = 0; x < src1_h; x += 2)
	{
		for (int y = 0; y < src2_w; y += 2)
		{
			// double is 8 bytes / 64 bits
			__m128d des0 = _mm_setzero_pd();
			__m128d des1 = _mm_setzero_pd();

			for (int k = 0; k < src2_h; k += 2)
			{
				__m128d I0 = _mm_loadu_pd((src1 + (x + 0) * src1_w + k));
				__m128d I1 = _mm_loadu_pd((src1 + (x + 1) * src1_w + k));

				__m128d I2 = _mm_set_pd(src2[(k + 1) * src2_w + y], src2[k * src2_w + y]);
				__m128d I3 = _mm_set_pd(src2[(k + 1) * src2_w + (y + 1)],
																src2[(k + 0) * src2_w + (y + 1)]);

				__m128d T0 = _mm_mul_pd(I0, I2);
				__m128d T1 = _mm_mul_pd(I0, I3);

				__m128d T2 = _mm_mul_pd(I1, I2);
				__m128d T3 = _mm_mul_pd(I1, I3);

				__m128d T4 = _mm_unpacklo_pd(T0, T1);
				__m128d T5 = _mm_unpackhi_pd(T0, T1);

				T4 = _mm_add_pd(T4, T5);
				des0 = _mm_add_pd(T4, des0);

				T4 = _mm_unpacklo_pd(T2, T3);
				T5 = _mm_unpackhi_pd(T2, T3);
				T4 = _mm_add_pd(T4, T5);
				des1 = _mm_add_pd(T4, des1);
			}

			_mm_store_pd((dst + ((x + 0) * src2_w) + y), des0);
			_mm_store_pd((dst + ((x + 1) * src2_w) + y), des1);
		}
	}
}