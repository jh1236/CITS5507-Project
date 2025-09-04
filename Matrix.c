//
// Created by healy on 2/09/2025.
//

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"


Matrix *newMatrix(long H, long W) {
    float *array = malloc(sizeof(float) * H * W);
    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->array = array;
    matrix->height = H;
    matrix->width = W;
    return matrix;
}

void deleteMatrix(Matrix *matrix) {
    free(matrix->array);
}

float accessMatrixOrZero(Matrix *matrix, int x, int y) {
    if (x < 0 || matrix->width <= x) return 0;
    if (y < 0 || matrix->height <= y) return 0;
    return matrix->array[y * matrix->width + x];
}

void writeMatrixToFile(char *filePath, Matrix *matrix) {
    FILE *fptr = fopen(filePath, "w");
    if (fptr == NULL) {
        exit(EXIT_FAILURE);
    }
    fprintf(fptr, "%li %li", matrix->height, matrix->width);

    for (int i = 0; i < matrix->height; ++i) {
        fprintf(fptr, "\n");
        for (int j = 0; j < matrix->width; ++j) {
            fprintf(fptr, "%.3f", matrix->array[i * matrix->width + j]);
            if (j != matrix->width - 1) { //ensure no trailing space
                fprintf(fptr, " ");
            }
        }
    }

    fclose(fptr);
}

Matrix *readMatrixFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    long width, height;
    if (fscanf(file, "%li %li", &height, &width) != 2) {
        fprintf(stderr, "Failed to read matrix dimensions\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    Matrix *m = newMatrix(height, width);

    for (int i = 0; i < height * width; i++) {
        if (fscanf(file, "%f", &m->array[i]) != 1) {
            fprintf(stderr, "Failed to read matrix value at index %d\n", i);
            free(m->array);
            free(m);
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);
    return m;
}