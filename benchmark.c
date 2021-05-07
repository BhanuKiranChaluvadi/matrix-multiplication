// g++ -O2 -msse3 benchmark.c -o benchmark
// ./benchmark > result.txt
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#include <immintrin.h>
#include <malloc.h>

#include <chrono>
#include <thread>

#include "impl.h"

static float diff_in_us(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec - t1.tv_nsec < 0)
    {
        diff.tv_sec = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    }
    else
    {
        diff.tv_sec = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec * 1000000.0 + diff.tv_nsec / 1000.0);
}

int main(int argc, char *argv[])
{
    unsigned int max_size = 512;
    unsigned int loop_cout = 1000;

    for (unsigned int size = 2; size <= max_size; size += 2)
    {
        printf("size %d\n", size);
        float naive_total_elapsed_time = 0;
        float sse_total_elapsed_time = 0;

        for (unsigned int i = 0; i <= loop_cout; i++)
        {
            // square matrix
            unsigned int TEST_H = size;
            unsigned int TEST_W = size;

            struct timespec start, end;
            double *src1 = (double *)memalign(64, sizeof(double) * TEST_W * TEST_H);
            double *src2 = (double *)memalign(64, sizeof(double) * TEST_W * TEST_H);
            double *dst = (double *)memalign(64, sizeof(double) * TEST_W * TEST_H);
            double *correct = (double *)memalign(64, sizeof(double) * TEST_W * TEST_H);

            srand(time(NULL));
            for (int i = 0; i < TEST_H; ++i)
            {
                for (int j = 0; j < TEST_W; ++j)
                {
                    src1[i * TEST_W + j] = rand();
                    src2[i * TEST_W + j] = rand();
                }
            }

            clock_gettime(CLOCK_REALTIME, &start);
            naive_multiply(src1, src2, correct, TEST_W, TEST_H, TEST_W, TEST_H);
            clock_gettime(CLOCK_REALTIME, &end);
            naive_total_elapsed_time += diff_in_us(start, end);

            clock_gettime(CLOCK_REALTIME, &start);
            sse_multiply(src1, src2, dst, TEST_W, TEST_H, TEST_W, TEST_H);
            clock_gettime(CLOCK_REALTIME, &end);
            sse_total_elapsed_time += diff_in_us(start, end);

            // if (0 != memcmp(correct, dst, sizeof(double) * TEST_W * TEST_H))
            // {
            // printf("naive : ");
            // print_array(correct, size * size);
            // printf("sse : ");
            // print_array(correct, size * size);
            // }
            // assert(0 == memcmp(correct, dst, sizeof(double) * TEST_W * TEST_H) &&
            //    "Verification fails");
            // std::this_thread::sleep_for(std::chrono::milliseconds(100));

            delete src1;
            delete src2;
            delete dst;
            delete correct;
        }
        float avg_native_elapsed_time = naive_total_elapsed_time / float(loop_cout);
        float avg_sse_elapsed_time = sse_total_elapsed_time / float(loop_cout);
        printf("naive  %lf\n", avg_native_elapsed_time);
        printf("sse  %lf\n", avg_sse_elapsed_time);
    }
    return 0;
}
