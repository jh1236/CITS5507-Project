//
// Created by healy on 1/09/2025.
//

#ifndef CITS5507PROJECT_CONVOLVE_H
#define CITS5507PROJECT_CONVOLVE_H

#include "Matrix.h"

int conv2d(
        Matrix *feature,
        Matrix *kernel,
        Matrix *output
);

#endif //CITS5507PROJECT_CONVOLVE_H
