# CITS 5507 Project

This is Jared Healy (23398223)'s CITS5507 Project write-up. There wasn't a suggested word limit, so I won't go to crazy,
but I'll try to explain to you my thought processes for the decisions that I made.

## Description of How I have Parallelised the System

The way that the algorithm has been parallelised is through the use of the pragma directive to parallelise the for loop
in `convolve.c`. The iteration has been left in 2 dimensions and not collapsed intentionally, to ensure that no false
sharing occurs, as the memory that each thread will be working on will not be close in memory. This could theoretically
lead to performance to very tall or very wide arrays, but those cases are not common use cases (when I say tall or wide
I mean like 5 or 6 on the short dimension - not very practical). Another consideration was the schedule method to use. I
tested the file on schedule static as well as guided and dynamic and decided to use

# TODO PUT THE RESULTS HERE

## Description of How I am Representing My Arrays

The way that all the arrays are being represented in memory is as a `Matrix` struct, which is defined as follows:

```c
typedef struct matrix {
    long height;
    long width;
    float *array;
} Matrix;
```

From this example, you can see that the arrays are stored as flat arrays with a height and width stored. To accommodate
for the boundary access and provide the padding, I have a function called `accessMatrixOrZero`, which ensures that the
boundaries of the array are respected in both dimensions.

## Have I considered the cache when developing my algorithm

While the cache was admittedly not my first issue when designing the algorithm, it was one of the main areas that I
worked to optimise. Almost every kernel access is linear in memory, making use of the flat array to ensure that it is
accessed in order. The feature map is less cache-optimised, but it will be accessed in order for each row of the kernel
(that is, if the kernel is m * n, then each m accesses will be in order before the array has to move to the next "row").
Having said that, I can't think of any way to improve this strategy; given that the algorithm needs to access the data
in a grid, the nature of a one dimensional array means that there needs to be a jump between rows, and there was no
data structure that would improve the cache hits. (My understanding about 2D arrays is that they end up the same as 1d
arrays in memory anyway, and no other data structure really made sense.)

## Performance Metrics and analysis of solution

Running both the parallel & linear 

Strategy: STATIC
Time Taken (Seconds): 526.404774

Strategy: DYNAMIC
Time Taken (Seconds): 525.822754

Strategy: GUIDED
Time Taken (Seconds): 525.136301

Strategy: COLLAPSE_STATIC
Time Taken (Seconds): 522.211076

Successfully Loaded config
Strategy: LINEAR
Time Taken (Seconds): 525.951473
