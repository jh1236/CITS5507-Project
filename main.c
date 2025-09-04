#include <stdio.h>
#include "convolve.h"
#include "argHandler.h"
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
    double begin = omp_get_wtime();

    switch (config->algorithm) {
        case STATIC:
            omp_set_num_threads(10);
            conv2dStatic(config->feature, config->kernel, config->output);
            break;
        case DYNAMIC:
            omp_set_num_threads(10);
            conv2dDynamic(config->feature, config->kernel, config->output);
            break;
        case GUIDED:
            omp_set_num_threads(10);
            conv2dGuided(config->feature, config->kernel, config->output);
            break;
        case COLLAPSE_STATIC:
            omp_set_num_threads(10);
            conv2dCollapseStatic(config->feature, config->kernel, config->output);
            break;
        case LINEAR:
            omp_set_num_threads(1);
            conv2dLinear(config->feature, config->kernel, config->output);
            break;
    }

    double end = omp_get_wtime();
    printf("Strategy: %s\n", NAMES[config->algorithm]);
    printf("Time Taken (Seconds): %f\n", (double) (end - begin));
}

