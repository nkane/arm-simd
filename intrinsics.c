#include <Accelerate/Accelerate.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>  // Added for malloc

#define SIZE 1000000

void add_arrays_simd(float* a, float* b, float* result, size_t size) {
    vDSP_vadd(a, 1, b, 1, result, 1, size);
}

void add_arrays_no_simd(float* a, float* b, float* result, size_t size) {
    for (size_t i = 0; i < size; i++) {
        result[i] = a[i] + b[i];
    }
}

double get_time() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1e-6;
}

int main() {
    float *a = malloc(SIZE * sizeof(float));
    float *b = malloc(SIZE * sizeof(float));
    float *result_simd = malloc(SIZE * sizeof(float));
    float *result_no_simd = malloc(SIZE * sizeof(float));

    for (int i = 0; i < SIZE; i++) {
        a[i] = (float)i;
        b[i] = (float)i;
    }

    double start_time, end_time;

    start_time = get_time();
    add_arrays_simd(a, b, result_simd, SIZE);
    end_time = get_time();
    printf("SIMD time: %.6f seconds\n", end_time - start_time);

    start_time = get_time();
    add_arrays_no_simd(a, b, result_no_simd, SIZE);
    end_time = get_time();
    printf("Non-SIMD time: %.6f seconds\n", end_time - start_time);

    free(a);
    free(b);
    free(result_simd);
    free(result_no_simd);

    return 0;
}
