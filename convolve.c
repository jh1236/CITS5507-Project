//
// Created by healy on 1/09/2025.
//

#include <stdio.h>
#include "convolve.h"
#include "Matrix.h"


int conv2dParallel(
        Matrix *feature,
        Matrix *kernel,
        Matrix *output
);

int conv2dParallelFlat(
        Matrix *feature,
        Matrix *kernel,
        Matrix *output
);

int conv2d(
        Matrix *feature,
        Matrix *kernel,
        Matrix *output
) {
    return conv2dParallel(feature, kernel, output);

}

int conv2dParallel(
        Matrix *feature,
        Matrix *kernel,
        Matrix *output
) {
    if (feature == NULL) {
        fprintf(stderr, "No Passed Feature");
        return 0;
    }
    if (kernel == NULL) {
        fprintf(stderr, "No Passed Kernel");
        return 0;
    }
    if (output == NULL) {
        fprintf(stderr, "No Passed Output");
        return 0;
    }
    if (feature->height < kernel->height || feature->width < kernel->width) {
        fprintf(stderr,"Feature is smaller than kernel");
        return 0; 
    }
//clang spits the dummy if this isn't default(none)
#pragma omp parallel for default(none) shared(feature, kernel, output)
    for (long x = 0; x < feature->width; ++x) {
        for (long y = 0; y < feature->height; ++y) {
            float total = 0;
            for (long j = 0; j < kernel->width * kernel->height; ++j) {
                const int kX = j % kernel->width;
                const int kY = j / kernel->height;
                total += kernel->array[j] *
                         accessMatrixOrZero(feature, x + (kX - kernel->width / 2), y + (kY - kernel->height / 2));
            }
            output->array[y * feature->height + x] = total;
        }
    }

    return 1;
}
