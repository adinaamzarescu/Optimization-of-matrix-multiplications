# Optimization of matrix multiplications
### Copyright Adina-Maria Amzarescu 331CA

_______________________________________________________________________________________________

Clarifications:

- ' is used for a transposed matrix
- the program implements C = A * B * A' + B' * B'
- performance is measured using 13 tests found in extra_input

_______________________________________________________________________________________________

## Implementation

**BLAS implementation**

`the code is found in solver_blas.c`

* Allocates memory for two matrices.
* Calculates the product of two matrices using optimized BLAS functions.
* Calculates the sum of two matrices using optimized BLAS functions.
* Checks for NaN or infinity values in the result matrix.
* Returns a pointer to the result matrix or NULL if there are NaN or 
infinity values or memory allocation fails.

Using _**extra_input**_ the following values will be obtained:
___________________________
        N=400: Time=0.040512
        
        N=500: Time=0.081174
        
        N=600: Time=0.132254
        
        N=700: Time=0.199691
        
        N=800: Time=0.287245
        
        N=900: Time=0.398964
        
        N=1000: Time=0.566673
        
        N=1100: Time=0.741773
        
        N=1200: Time=0.940245
        
        N=1300: Time=1.174512
        
        N=1400: Time=1.439273
        
        N=1500: Time=1.830243
        
        N=1600: Time=2.188797

___________________________

This code is efficient because it uses the Basic Linear Algebra Subprograms (BLAS) library 
functions, specifically cblas_dtrmm and cblas_dgemm, which are highly optimized for 
matrix operations. 

_______________________________________________________________________________________________

**The optimized version implementation**

`the code is found in solver_opt.c`

Additional functions: 
        * allocate_matrix: dynamically allocates memory for a matrix of a given size.
        * free_matrices: frees the memory allocated for several matrices.
        * allocate_all_matrices: allocates the memory for several matrices used in the computations.
        * matrix_multiply: performs a matrix multiplication operation between two matrices A and B, storing the * result in a pre-allocated matrix A_B.
        * matrix_multiply_transpose: performs a matrix multiplication operation between the matrix A_B and the transpose of A, storing the result in a pre-allocated matrix A_B_A_transpose.
        * matrix_multiply_b_transpose_b: performs a matrix multiplication operation between the transpose of B and B, storing the result in a pre-allocated matrix B_B_transpose.
        * matrix_addition: performs a matrix addition operation between two matrices, storing the result in a pre-allocated matrix C.

* The functions are used to compute matrix C, which is the sum of two other matrices.
* The code dynamically allocates memory for the matrices and frees it after the computation.
* The matrix computations are performed using pointer arithmetic and register optimization.
* The code returns the resulting matrix C as a double pointer.

Using _**extra_input**_ the following values will be obtained:

___________________________

        N=400: Time=0.291104

        N=500: Time=0.549925

        N=600: Time=1.608891

        N=700: Time=3.565503

        N=800: Time=2.268724

        N=900: Time=3.194524

        N=1000: Time=4.369854

        N=1100: Time=5.512434

        N=1200: Time=7.195324

        N=1300: Time=9.529752

        N=1400: Time=11.998105

        N=1500: Time=15.678024

        N=1600: Time=24.465864
___________________________


This code is efficient because it makes use of optimization techniques such as register variables. 
However, it is less efficient than BLAS because BLAS is a highly optimized library specifically 
designed for linear algebra operations.

_______________________________________________________________________________________________

**The non-optimized version implementation**

`the code is found in solver_neopt.c`

The code defines a set of functions for matrix operations:

1. allocate_matrix: allocates memory for a matrix of a given size.
2. free_matrices: frees the memory allocated for multiple matrices.
3. allocate_all_matrices: allocates memory for all matrices required in the computation.
4. matrix_multiplication: performs matrix multiplication of two matrices.
5. multiply_A_B_A_transpose: multiplies the resulting matrix from step 1 with the transpose of another matrix.
6. multiply_B_B_transpose: multiplies the transpose of a matrix with itself.
7. add_matrices: adds two matrices.

The main function my_solver performs matrix multiplication, transposition, 
and addition operations to compute the matrix C, which is the sum of two other matrices.

Using _**extra_input**_ the following values will be obtained:

___________________________

        N=400: Time=1.115916

        N=500: Time=2.180850

        N=600: Time=3.882337

        N=700: Time=5.935851

        N=800: Time=9.266505

        N=900: Time=12.521920

        N=1000: Time=16.939447

        N=1100: Time=23.407904

        N=1200: Time=31.416428

        N=1300: Time=43.221939

        N=1400: Time=53.519012

        N=1500: Time=72.440521

        N=1600: Time=90.029343
___________________________

    extra_input:

    13
    400 123 out1
    500 123 out2
    600 123 out3
    700 123 out4
    800 456 out5
    900 456 out6
    1000 456 out7
    1100 456 out8
    1200 789 out9
    1300 789 out10
    1400 789 out11
    1500 789 out12
    1600 789 out13

_______________________________________________________________________________________________

## Graph

To create the graph, I created a python script, plot_functions.py

![graph](https://github.com/adinaamzarescu/Tema2_ASC/blob/main/grafice/graph_all_functions.png)

As the input size N increases, the runtime of all three functions also 
increases. However, the rate at which the runtime increases differs between the 
functions. The blas function has the lowest increase in runtime as N increases, 
followed by opt, and then neopt.

To analyze the functions separately:

![graph2](https://github.com/adinaamzarescu/Tema2_ASC/blob/main/grafice/graph_separate_functions.png)

The reason why the graph is faster for multiples of 4 is most likely due to the way CPUs handle
memory and cache. In most modern CPUs, the memory is organized into "cache lines" which are blocks
of memory that are typically 64 bytes in size. 

_______________________________________________________________________________________________

## Memory management

You can see the results of the command **valgrind --leak-check=full --tool=memcheck --track-origins=yes** 
in the memory folder where there are 3 files corresponding to the 3 functions.

The blas function contains 78 memory allocations, the optimized 10 and the non-optimized 10.

While it's true that memory allocations can be expensive in terms of time and resources, the 
efficiency of this code is not solely determined by the number of memory allocations it uses.

_______________________________________________________________________________________________

## Cache

You can see the results of the command **valgrind --tool=cachegrind --branch-sim=yes** in the
cache folder where there are 3 files corresponding to the 3 functions.

`neopt.cache`

Looking at the output, we see that the program executed with N=400 and took 33.522308 
seconds to complete. The program made 5,924,927,004 instruction references, 
out of which 1,620 were instruction cache (I1) misses and 1,545 were last-level 
instruction cache (LLi) misses. This indicates that the instruction cache hit 
rate was high, at 99.99%. Similarly, the data cache (D1) miss rate was 3.2%, 
with 94,362,179 data cache misses out of 2,962,907,724 data references. 
The last-level data cache (LLd) miss rate was 0.0%, with 113,276 misses 
out of 94,363,799 references.

`opt_m.cache`

Based on the output, it seems like the program had very few instruction cache 
misses (I1 misses and LLi misses both have a miss rate of 0.00%), which means that 
the instructions were efficiently cached. However, the data cache misses 
(D1 misses and LLd misses) are quite high, with a miss rate of 19.9% and 
0.0%, respectively. This suggests that the program is not efficiently 
using the data cache.

However the program has improved in terms of cache misses and branch mispredictions compared 
to the previous version.

`blas.cache`

From the output, we can see that the cache miss rates for both instruction and data caches 
are relatively low, with only 0.01% and 1.7% miss rates respectively. The LL cache miss rate 
is also low for data, at 0.1%. 

The program is performing better in terms of cache usage and branch prediction compared to 
the previous two programs.

_______________________________________________________________________________________________

## Conclusions

* BLAS is the most optimized version
* While reducing the number of memory allocations can sometimes improve performance, it's not 
always the most important factor in determining the efficiency of a program.
* Using the BLAS implementation leads to a significant reduction in cache misses.

_______________________________________________________________________________________________

## References

1. https://netlib.org/blas/faq.html
2. https://netlib.org/lapack/lug/
3. https://ocw.cs.pub.ro/courses/asc/laboratoare/05
4. https://www.ibm.com/docs/en/xcfbg/121.141?topic=blas-function-syntax

_______________________________________________________________________________________________
