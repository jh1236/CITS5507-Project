//
//  CITS 5507 2025 S2
//  Jared Healy (23398223)
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
