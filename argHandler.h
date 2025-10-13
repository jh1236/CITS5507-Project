//
//  CITS 5507 2025 S2
//  Jared Healy (23398223)
//

#ifndef CITS5507PROJECT_ARGHANDLER_H
#define CITS5507PROJECT_ARGHANDLER_H

#include "Matrix.h"

enum Algorithm {
    LINEAR,
    OPENMP,
    MPI,
    BOTH
};

extern const char *NAMES[5];

typedef struct config {
    Matrix *feature;
    Matrix *kernel;
    Matrix *output;
    int sw;
    int sh;
    char *featureFilePath;
    char *kernelFilePath;
    char *outputFilePath;
    enum Algorithm algorithm;
} Config;

void setConfig(int argc, char **argV, Config *config);

void deleteConfig(Config *config);

#endif //CITS5507PROJECT_ARGHANDLER_H
