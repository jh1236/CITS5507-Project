//
//  CITS 5507 2025 S2
//  Jared Healy (23398223)
//

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
    printf("OpenMP max threads = %d\n", omp_get_max_threads());
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
    //1.635000
    omp_set_num_threads(omp_get_max_threads());
    switch (config->algorithm) {

        case LINEAR:
            conv2dLinear(config->feature, config->kernel, config->sx, config->sy, config->output);
            break;
        case OPENMP:
            conv2dOpenMP(config->feature, config->kernel, config->sx, config->sy, config->output);
            break;
        case MPI:
            conv2dMPI(config->feature, config->kernel, config->sx, config->sy, config->output);
            break;
        case BOTH:
            conv2dMPIAndOpenMP(config->feature, config->kernel, config->sx, config->sy, config->output);
            break;
    }

    double end = omp_get_wtime();
    printf("Strategy: %s\n", NAMES[config->algorithm]);
    printf("Time Taken (Seconds): %f\n", (double) (end - begin));
}

