cmake_minimum_required(VERSION 3.26)
project(CITS5507Project C)

set(CMAKE_C_STANDARD 11)

find_package(OpenMP REQUIRED)
add_executable(CITS5507Project
        main.c
        convolve.c
        convolve.h
        fileHelper.c
        fileHelper.h
        argHandler.c
        argHandler.h
        Matrix.c
        Matrix.h
)
target_link_libraries(CITS5507Project PUBLIC OpenMP::OpenMP_C)

