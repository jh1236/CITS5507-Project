//
// Created by healy on 1/09/2025.
//

#ifndef CITS5507PROJECT_MATRIX_H
#define CITS5507PROJECT_MATRIX_H

typedef struct matrix {
    long height;
    long width;
    float *array;
} Matrix;

Matrix *newMatrix(long H, long W);

void deleteMatrix(Matrix *matrix);

float accessMatrixOrZero(Matrix *matrix, int x, int y);

void writeMatrixToFile(char *filePath, Matrix *matrix);

Matrix *readMatrixFromFile(const char *filename);

#endif //CITS5507PROJECT_MATRIX_H
