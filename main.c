#include <stdio.h>
#include "convolve.h"
#include "argHandler.h"
#include <time.h>


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
    
    if (!conv2d(config->feature, config->kernel, config->output)) {
        return;
    }

    clock_t end = clock();
    printf("Time Taken (Seconds): %f\n", (double) (end - begin) / CLOCKS_PER_SEC);
}

