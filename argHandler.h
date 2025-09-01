//
// Created by healy on 1/09/2025.
//

#ifndef CITS5507PROJECT_ARGHANDLER_H
#define CITS5507PROJECT_ARGHANDLER_H

#include "Matrix.h"

typedef struct config {
    Matrix *feature;
    Matrix *kernel;
    Matrix *output;
    char *featureFilePath;
    char *kernelFilePath;
    char *outputFilePath;
} Config;

void setConfig(int argc, char **argV, Config *config);

void deleteConfig(Config *config);

#endif //CITS5507PROJECT_ARGHANDLER_H
