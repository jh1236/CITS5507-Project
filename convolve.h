//
//  CITS 5507 2025 S2
//  Jared Healy (23398223)
//

#ifndef CITS5507PROJECT_CONVOLVE_H
#define CITS5507PROJECT_CONVOLVE_H

#include "Matrix.h"


int conv2dStatic(
    Matrix *feature,
    Matrix *kernel,
    Matrix *output
);

int conv2dDynamic(
    Matrix *feature,
    Matrix *kernel,
    Matrix *output
);

int conv2dGuided(
    Matrix *feature,
    Matrix *kernel,
    Matrix *output
);

int conv2dCollapseStatic(
    Matrix *feature,
    Matrix *kernel,
    Matrix *output
);

int conv2dLinear(
    Matrix *feature,
    Matrix *kernel,
    Matrix *output
);


#endif //CITS5507PROJECT_CONVOLVE_H
