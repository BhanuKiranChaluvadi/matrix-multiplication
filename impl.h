
#include <emmintrin.h>
#include <stdio.h>
#include <string.h>

void print128d(__m128d var)
{
	double v64val[2];
	memcpy(v64val, &var, sizeof(v64val));
	printf("%lf %lf\n", v64val[1], v64val[0]);
}

void sse_multiply(const double *src1, const double *src2, double *dst, int src1_w, int src1_h, int src2_w, int src2_h)
{
	for (int x = 0; x < src1_h; x += 2)
	{
		for (int y = 0; y < src2_w; y += 2)
		{
			// double is 8 bytes / 64 bits
			__m128d des0 = _mm_setzero_pd();
			__m128d des1 = _mm_setzero_pd();

			for (int k = 0; k < src2_w; k += 2)
			{
				// __m128d I0 = _mm_loadu_pd((__m128d *)(src1 + (x + 1) * src1_w + k));
				// __m128d I1 = _mm_loadu_pd((__m128d *)(src1 + (x + 1) * src1_w + k));

				// __m128d I2 = _mm_set_pd(src2[(k + 1) * src2_w + y], src2[k * src2_w + y]);
				// __m128i I3 = _mm_set_pd(src2[(k + 1) * src2_w + (y + 1)],
				// 												src2[(k + 0) * src2_w + (y + 1)]);

				// __m128d T0 = _mm_mul_pd(I0, I2);
				// __m128d T1 = _mm_mul_pd(I0, I3);

				// __m128d T2 = _mm_mul_pd(I1, I2);
				// __m128d T3 = _mm_mul_pd(I2, I3);

				// __m128d T4 = _mm_unpacklo_epi32(T0, T1);
			}
		}
	}
}