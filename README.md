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

Using extra_input the following values will be obtained:
___________________________

    N=400: Time=0.040290

    N=500: Time=0.080949

    N=600: Time=0.131025

    N=700: Time=0.198116

    N=800: Time=0.285428

    N=900: Time=0.396836

    N=1000: Time=0.561678

    N=1100: Time=0.734086

    N=1200: Time=0.934723

    N=1300: Time=1.169696

    N=1400: Time=1.431724

    N=1500: Time=1.822059

    N=1600: Time=2.179854

___________________________

This code is efficient because it uses the Basic Linear Algebra Subprograms (BLAS) library 
functions, specifically cblas_dtrmm and cblas_dgemm, which are highly optimized for 
matrix operations. 

**The optimized version implementation**

`the code is found in solver_opt.c`

* The code defines functions for matrix multiplication and dot product calculation.
* The functions are used to compute matrix C, which is the sum of two other matrices.
* The code dynamically allocates memory for the matrices and frees it after the computation.
* The matrix computations are performed using pointer arithmetic and register optimization.
* The code returns the resulting matrix C as a double pointer.

Using extra_input the following values will be obtained:

___________________________

    N=400: Time=0.368568

    N=500: Time=0.713883

    N=600: Time=1.231407

    N=700: Time=1.942642

    N=800: Time=2.904663

    N=900: Time=4.118597

    N=1000: Time=5.652847

    N=1100: Time=7.523404

    N=1200: Time=9.823234

    N=1300: Time=12.547029

    N=1400: Time=15.774285

    N=1500: Time=19.510212

    N=1600: Time=23.775011
___________________________


This code is efficient because it makes use of optimization techniques such as register variables. 
However, it is less efficient than BLAS because BLAS is a highly optimized library specifically 
designed for linear algebra operations.


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

Using extra_input the following values will be obtained:

___________________________

    N=400: Time=1.118085
    
    N=500: Time=2.190298
    
    N=600: Time=3.891463
    
    N=700: Time=5.948505
    
    N=800: Time=9.445211
    
    N=900: Time=12.603328
    
    N=1000: Time=16.913977
    
    N=1100: Time=22.865772
    
    N=1200: Time=30.707788
    
    N=1300: Time=43.487358
    
    N=1400: Time=53.864227
    
    N=1500: Time=72.666016
    
    N=1600: Time=91.181343
___________________________

_______________________________________________________________________________________________
