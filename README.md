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

This code is efficient because it uses the Basic Linear Algebra Subprograms (BLAS) library 
functions, specifically cblas_dtrmm and cblas_dgemm, which are highly optimized for 
matrix operations. 



_______________________________________________________________________________________________
