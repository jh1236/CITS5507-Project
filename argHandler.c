#pragma clang diagnostic push
//it doesn't like the way I generate random numbers
#pragma ide diagnostic ignored "cert-msc51-cpp"
#pragma ide diagnostic ignored "cert-msc50-cpp"
//
// Created by healy on 1/09/2025.
//

#include <malloc.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "argHandler.h"
#include "Matrix.h"


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
    int H = -1, W = -1, kH = -1, kW = -1;
    int opt;
    srand(time(NULL));
    while ((opt = getopt(argc, argv, "f:g:o:H:W:x:y:")) != -1) {
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

            default:
                fprintf(stderr,
                        "Usage: %s -f [feature.txt] -g [kernel.txt] -o [output.txt] -H [feature height] -W [feature width] -x [kernel width] -y [kernel height] \n",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    if (H > 0 || W > 0) {
        if (H == -1 || W == -1) {
            fprintf(stderr, "Passing -H requires passing -W and vice versa");
            exit(EXIT_FAILURE);
        }
        Matrix *output = newMatrix(H, W);
        Matrix *feature = newMatrix(H, W);
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
        config->output = newMatrix(config->feature->height, config->feature->width);
    } else {
        fprintf(stderr, "You must specify either a random size for feature or a file input.");
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
    }
}

#pragma clang diagnostic pop