//
//  CITS 5507 2025 S2
//  Jared Healy (23398223)
//

#ifndef CITS5507PROJECT_CONVOLVE_H
#define CITS5507PROJECT_CONVOLVE_H

#include "Matrix.h"


int conv2dOpenMP(
    Matrix *feature,
    const Matrix *kernel,
    int sw, int sh,
    const Matrix *output
);

int conv2dMPI(
    Matrix *feature,
    const Matrix *kernel,
    int sw, int sh,
    const Matrix *output
);

int conv2dMPIAndOpenMP(
    Matrix *feature,
    const Matrix *kernel,
    int sw, int sh,
    const Matrix *output
);

int conv2dLinear(
    Matrix *feature,
    const Matrix *kernel,
    int sw, int sh,
    const Matrix *output
);


#endif //CITS5507PROJECT_CONVOLVE_H
