#include <stdio.h>
#include "convolve.h"
#include "argHandler.h"
#include <omp.h>
#include <malloc.h>
#include <time.h>
#include <unistd.h>

#define TEST_ITERATIONS 100


void test(Config *config);

int main(int argc, char **argv) {
    Config config = {
            .featureFilePath = NULL,
            .kernelFilePath = NULL,
            .outputFilePath = NULL,
            .output = NULL,
            .kernel = NULL,
            .feature = NULL,
    };
    setConfig(argc, argv, &config);
    test(&config);
    for (int i = 0; i < config.output->height; i++) {
        for (int j = 0; j < config.output->width; ++j) {
            printf("%f", config.output->array[i * config.output->width + j]);
        }
        printf("\n");
    }
    if (config.outputFilePath != NULL) {
        writeMatrixToFile(config.outputFilePath, config.output);
    }
    deleteConfig(&config);
    return 0;
}

void test(Config *config) {
    omp_set_num_threads(1);
    clock_t begin = clock();
    for (int i = 0; i < TEST_ITERATIONS; ++i) {
        if (!conv2d(config->feature, config->kernel, config->output)) {
            return;
        }
    }

    clock_t end = clock();

    printf("%f\n", (double) (end - begin) / CLOCKS_PER_SEC / TEST_ITERATIONS);
}

