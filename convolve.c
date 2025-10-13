//
//  CITS 5507 2025 S2
//  Jared Healy (23398223)
//

#include <stdio.h>
#include "convolve.h"
#include "Matrix.h"


int conv2dStatic(
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
        fprintf(stderr, "Feature is smaller than kernel");
        return 0;
    }
    //clang spits the dummy if this isn't default(none)
#pragma omp parallel for default(none) shared(feature, kernel, output) schedule(static)
    for (long x = 0; x < feature->width; ++x) {
        for (long y = 0; y < feature->height; ++y) {
            float total = 0;
            for (long j = 0; j < kernel->width * kernel->height; ++j) {
                const int kX = j % kernel->width;
                const int kY = j / kernel->width;
                total += kernel->array[j] *
                         accessMatrixOrZero(feature, x + (kX - kernel->width / 2), y + (kY - kernel->height / 2));
            }
            output->array[y * feature->width + x] = total;
        }
    }

    return 1;
}

int conv2dDynamic(
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
        fprintf(stderr, "Feature is smaller than kernel");
        return 0;
    }
    //clang spits the dummy if this isn't default(none)
#pragma omp parallel for default(none) shared(feature, kernel, output) schedule(dynamic)
    for (long x = 0; x < feature->width; ++x) {
        for (long y = 0; y < feature->height; ++y) {
            float total = 0;
            for (long j = 0; j < kernel->width * kernel->height; ++j) {
                const int kX = j % kernel->width;
                const int kY = j / kernel->width;
                total += kernel->array[j] *
                         accessMatrixOrZero(feature, x + (kX - kernel->width / 2), y + (kY - kernel->height / 2));
            }
            output->array[y * feature->width + x] = total;
        }
    }

    return 1;
}

int conv2dGuided(
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
        fprintf(stderr, "Feature is smaller than kernel");
        return 0;
    }
    //clang spits the dummy if this isn't default(none)
#pragma omp parallel for default(none) shared(feature, kernel, output) schedule(guided)
    for (long x = 0; x < feature->width; ++x) {
        for (long y = 0; y < feature->height; ++y) {
            float total = 0;
            for (long j = 0; j < kernel->width * kernel->height; ++j) {
                const int kX = j % kernel->width;
                const int kY = j / kernel->width;
                total += kernel->array[j] *
                         accessMatrixOrZero(feature, x + (kX - kernel->width / 2), y + (kY - kernel->height / 2));
            }
            output->array[y * feature->width + x] = total;
        }
    }

    return 1;
}

int conv2dCollapseStatic(
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
        fprintf(stderr, "Feature is smaller than kernel");
        return 0;
    }
    //clang spits the dummy if this isn't default(none)
    //set the size to 100 so that we don't get false sharing
#pragma omp parallel for default(none) shared(feature, kernel, output) schedule(static, 200) collapse(2)
    for (long x = 0; x < feature->width; ++x) {
        for (long y = 0; y < feature->height; ++y) {
            float total = 0;
            for (long j = 0; j < kernel->width * kernel->height; ++j) {
                const int kX = j % kernel->width;
                const int kY = j / kernel->width;
                total += kernel->array[j] *
                         accessMatrixOrZero(feature, x + (kX - kernel->width / 2), y + (kY - kernel->height / 2));
            }
            output->array[y * feature->width + x] = total;
        }
    }

    return 1;
}


int conv2dLinear(
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
        fprintf(stderr, "Feature is smaller than kernel");
        return 0;
    }

    for (long x = 0; x < feature->width; ++x) {
        for (long y = 0; y < feature->height; ++y) {
            float total = 0;
            for (long j = 0; j < kernel->width * kernel->height; ++j) {
                const int kX = j % kernel->width;
                const int kY = j / kernel->width;
                total += kernel->array[j] *
                         accessMatrixOrZero(feature, x + (kX - kernel->width / 2), y + (kY - kernel->height / 2));
            }
            output->array[y * feature->width + x] = total;
        }
    }

    return 1;
}
