#include <stdio.h>
#include "convolve.h"
#include "argHandler.h"
#include <time.h>
#include <omp.h>


void test(Config *config);

int main(int argc, char **argv) {
    Config config = {
            .featureFilePath = NULL,
            .kernelFilePath = NULL,
            .outputFilePath = NULL,
            .output = NULL,
            .kernel = NULL,
            .feature = NULL,
            .algorithm = 0
    };
    setConfig(argc, argv, &config);
    printf("Successfully Loaded config\n");
    test(&config);
    if (config.outputFilePath != NULL) {
        writeMatrixToFile(config.outputFilePath, config.output);
    }
    deleteConfig(&config);
    return 0;
}

void test(Config *config) {
    clock_t begin = clock();

    switch (config->algorithm) {
        case STATIC:
            conv2dStatic(config->feature, config->kernel, config->output);
            break;
        case DYNAMIC:
            conv2dDynamic(config->feature, config->kernel, config->output);
            break;
        case GUIDED:
            conv2dGuided(config->feature, config->kernel, config->output);
            break;
        case COLLAPSE_STATIC:
            conv2dCollapseStatic(config->feature, config->kernel, config->output);
            break;
        case LINEAR:
            omp_set_num_threads(1);
            conv2dLinear(config->feature, config->kernel, config->output);
            break;
    }

    clock_t end = clock();
    printf("Strategy: %s\n", NAMES[config->algorithm]);
    printf("Time Taken (Seconds): %f\n", (double) (end - begin) / CLOCKS_PER_SEC);
}

