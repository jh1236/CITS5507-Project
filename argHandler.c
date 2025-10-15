//
//  CITS 5507 2025 S2
//  Jared Healy (23398223)
//

#pragma clang diagnostic push
//it doesn't like the way I generate random numbers
#pragma ide diagnostic ignored "cert-msc51-cpp"
#pragma ide diagnostic ignored "cert-msc50-cpp"

#include <malloc.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "argHandler.h"
#include "Matrix.h"

const char *NAMES[4] = {
    "LINEAR",
    "OPENMP",
    "MPI",
    "MPI+OPENMP"
};

void deleteConfig(Config *config) {
    free(config->featureFilePath);
    free(config->kernelFilePath);
    free(config->outputFilePath);
    deleteMatrix(config->feature);
    free(config->feature);
    deleteMatrix(config->kernel);
    free(config->kernel);
    deleteMatrix(config->output);
    free(config->output);
}

/*
 * Takes a blank config and initialises it based on the programs args 
 */
void setConfig(int argc, char **argv, Config *config) {
    long H = -1, W = -1, kH = -1, kW = -1, sw = 1, sh = 1;
    int opt;
    srand(time(NULL));
    while ((opt = getopt(argc, argv, "f:g:o:H:W:x:y:a:s:p:")) != -1) {
        switch (opt) {
            case 'f': {
                unsigned int len = strlen(optarg);
                config->featureFilePath = malloc(sizeof(char) * (len + 1));
                strcpy(config->featureFilePath, optarg);
                break;
            }
            case 'g': {
                unsigned int len = strlen(optarg);
                config->kernelFilePath = malloc(sizeof(char) * (len + 1));
                strcpy(config->kernelFilePath, optarg);
                break;
            }
            case 'o': {
                unsigned int len = strlen(optarg);
                config->outputFilePath = malloc(sizeof(char) * (len + 1));
                strcpy(config->outputFilePath, optarg);
                break;
            }
            case 'H':
                H = strtol(optarg, NULL, 10);
                break;
            case 'W':
                W = strtol(optarg, NULL, 10);
                break;
            case 'x':
                kH = strtol(optarg, NULL, 10);
                break;
            case 'y':
                kW = strtol(optarg, NULL, 10);
                break;
            case 's':
                sw = strtol(optarg, NULL, 10);
                break;
            case 'p':
                sh = strtol(optarg, NULL, 10);
                break;
            case 'a': {
                errno = 0;
                long result = strtol(optarg, NULL, 10) - 1;
                if ((result == LONG_MAX || result == LONG_MIN) && errno == ERANGE) {
                    switch (optarg[0]) {
                        case 'l':
                        case 'L':
                            config->algorithm = 1;
                            break;
                        case 'o':
                        case 'O':
                            config->algorithm = 2;
                            break;
                        case 'm':
                        case 'M':
                            config->algorithm = 3;
                            break;
                        case 'b':
                        case 'B':
                            config->algorithm = 4;
                            break;
                        default: fprintf(stderr,
                                         "Unrecognised Algorithm Signifier: %s",
                                         argv[0]);
                            exit(EXIT_FAILURE);
                    }
                } else {
                    config->algorithm = (int) result;    
                }
            }
            break;

            default:
                fprintf(stderr,
                        "Usage: %s -f [feature.txt] -g [kernel.txt] -o [output.txt] -H [feature height] -W [feature width] -x [kernel width] -y [kernel height] -s [stride x] -p [stride y] -a [Algorithm #]\n",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (H > 0 || W > 0) {
        if (H == -1 || W == -1) {
            fprintf(stderr, "Passing -H requires passing -W and vice versa");
            exit(EXIT_FAILURE);
        }
        Matrix *feature = newMatrix(H, W);
        int outputW = H / sw, outputH = W / sh;

        // if the division is not clean, we need to add one (so the partial row is calculated)
        if (H % sh != 0) outputH++;
        if (W % sw != 0) outputW++;

        Matrix *output = newMatrix(outputH, outputW);
        for (int i = 0; i < H * W; ++i) {
            feature->array[i] = (float) rand() / (float) (RAND_MAX);
        }
        config->feature = feature;
        config->output = output;
        if (config->featureFilePath != NULL) {
            writeMatrixToFile(config->featureFilePath, feature);
        }
    } else if (config->featureFilePath != NULL) {
        config->feature = readMatrixFromFile(config->featureFilePath);
        int outputW = config->feature->height / sw, outputH = config->feature->width / sh;

        // if the division is not clean, we need to add one (so the partial row is calculated)
        if (H % sh != 0) outputH++;
        if (W % sw != 0) outputW++;
        config->output = newMatrix(outputH, outputW);
    } else {
        fprintf(stderr, "You must specify either a random size for feature or a file input.");
        exit(EXIT_FAILURE);
    }
    if (kH > 0 || kW > 0) {
        if (kH == -1 || kW == -1) {
            fprintf(stderr, "Passing -x requires passing -y and vice versa");
            exit(EXIT_FAILURE);
        }
        Matrix *kernel = newMatrix(kH, kW);
        for (int i = 0; i < kH * kW; ++i) {
            kernel->array[i] = (float) rand() / (float) (RAND_MAX);
        }
        config->kernel = kernel;
        if (config->kernelFilePath != NULL) {
            writeMatrixToFile(config->kernelFilePath, kernel);
        }
    } else if (config->kernelFilePath != NULL) {
        config->kernel = readMatrixFromFile(config->kernelFilePath);
    } else {
        fprintf(stderr, "You must specify either a random size for feature or a file input.");
        exit(EXIT_FAILURE);
    }

    if (sw > config->feature->width || sh > config->feature->height) {
        fprintf(stderr, "The stride must be smaller than the matrix!");
        exit(EXIT_FAILURE);
    } else {
        config->sw = sw;
        config->sh = sh;
    }
}

#pragma clang diagnostic pop
