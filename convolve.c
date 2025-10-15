//
//  CITS 5507 2025 S2
//  Jared Healy (23398223)
//

#include "convolve.h"
#include <mpi.h>
#include <stdio.h>
#include "Matrix.h"


int conv2dOpenMP(
    Matrix *feature,
    Matrix *kernel,
    int sx, int sy,
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
    // clang spits the dummy if this isn't default(none)
    // sw and sh could be first-private here, but shared should be more performant
#pragma omp parallel for default(none) shared(sx, sy, feature, kernel, output) schedule(dynamic)
    for (long x = 0; x < output->width; x++) {
        for (long y = 0; y < output->height; y++) {
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
    int sw, int sh,
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

    for (long x = 0; x < output->width; x++) {
        for (long y = 0; y < output->height; y++) {
            float total = 0;
            for (long j = 0; j < kernel->width * kernel->height; ++j) {
                const int kX = j % kernel->width;
                const int kY = j / kernel->width;
                total += kernel->array[j] *
                        accessMatrixOrZero(feature, (sw * x) + (kX - kernel->width / 2),
                                           (sh * y) + (kY - kernel->height / 2));
            }
            output->array[y * output->width + x] = total;
        }
    }

    return 1;
}

int conv2dMPI(
    Matrix *feature,
    Matrix *kernel,
    int sw, int sh,
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
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int total_iterations = output->height * output->width;

    int lower = (total_iterations * rank) / size;
    int upper = (total_iterations * (rank + 1)) / size;
    if (rank == size) {
        upper = total_iterations;
    }

    for (long i = lower; i < upper; i++) {
        int x = i % kernel->width;
        int y = i / kernel->width;
        float total = 0;
        for (long j = 0; j < kernel->width * kernel->height; ++j) {
            const int kX = j % kernel->width;
            const int kY = j / kernel->width;
            total += kernel->array[j] *
                    accessMatrixOrZero(feature, (sw * x) + (kX - kernel->width / 2),
                                       (sh * y) + (kY - kernel->height / 2));
        }
        output->array[y * output->width + i] = total;
    }
    if (rank == 0) {
        //we are the root process, and need to do a bit of extra work
        int sizes[size];
        int displ[size];
        for (long i = 0; i < size; i++) {
            sizes[i] = (total_iterations * (rank + 1)) / size - (total_iterations * rank) / size;
            displ[i] = (total_iterations * (rank)) / size;
        }
        int recv[total_iterations];
        //we can cheat a little bit here because we know our rank
        MPI_Gatherv(output, upper, MPI_FLOAT, recv, sizes, displ, MPI_FLOAT, 0, MPI_COMM_WORLD);
    } else {
        MPI_Gatherv(output + lower, upper - lower, MPI_FLOAT, NULL, NULL, NULL, MPI_FLOAT, 0, MPI_COMM_WORLD);
    }
    
    return 1;
}

int conv2dMPIAndOpenMP(
    Matrix *feature,
    Matrix *kernel,
    int sw, int sh,
    Matrix *output
) {
    if (feature == NULL) {
        fprintf(stderr, "No Passed Feature\n");
        return 0;
    }
    if (kernel == NULL) {
        fprintf(stderr, "No Passed Kernel\n");
        return 0;
    }
    if (output == NULL) {
        fprintf(stderr, "No Passed Output\n");
        return 0;
    }
    if (feature->height < kernel->height || feature->width < kernel->width) {
        fprintf(stderr, "Feature is smaller than kernel\n");
        return 0;
    }

    for (long x = 0; x < output->width; x++) {
        for (long y = 0; y < output->height; y++) {
            float total = 0;
            for (long j = 0; j < kernel->width * kernel->height; ++j) {
                const int kX = j % kernel->width;
                const int kY = j / kernel->width;
                total += kernel->array[j] *
                        accessMatrixOrZero(feature, (sw * x) + (kX - kernel->width / 2),
                                           (sh * y) + (kY - kernel->height / 2));
            }
            output->array[y * output->width + x] = total;
        }
    }

    return 1;
}
