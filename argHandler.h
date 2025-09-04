//
// Created by healy on 1/09/2025.
//

#ifndef CITS5507PROJECT_ARGHANDLER_H
#define CITS5507PROJECT_ARGHANDLER_H

#include "Matrix.h"

enum Algorithm {
    STATIC,
    DYNAMIC,
    GUIDED,
    COLLAPSE_STATIC,
    LINEAR
};

const char *NAMES[5] = {
        "STATIC",
        "DYNAMIC",
        "GUIDED",
        "COLLAPSE_STATIC",
        "LINEAR",
};

typedef struct config {
    Matrix *feature;
    Matrix *kernel;
    Matrix *output;
    char *featureFilePath;
    char *kernelFilePath;
    char *outputFilePath;
    enum Algorithm algorithm;
} Config;

void setConfig(int argc, char **argV, Config *config);

void deleteConfig(Config *config);

#endif //CITS5507PROJECT_ARGHANDLER_H
