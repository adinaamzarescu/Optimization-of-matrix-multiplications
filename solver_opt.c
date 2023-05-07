/*
 * Tema 2 ASC
 * 2023 Spring
 */
#include "utils.h"

double dot_product(double *a, double *b, int n) {
    register double s = 0.0; // Initialize the dot product to 0
    for (register int i = 0; i < n; ++i) { // Loop over the elements in the arrays
        s += *a++ * *b++; // Add the product of the corresponding elements to the dot product
    }
    return s; // Return the dot product
}

void multiply_matrices(double *a, double *b, double *c, int n) {
    for (register int i = 0; i < n; ++i) { // Loop over the rows of the first matrix
        for (register int j = 0; j < n; ++j) { // Loop over the columns of the second matrix
            // Compute the dot product of the i-th row of the first matrix and the j-th column of the second matrix,
            // and store the result in the corresponding element of the resulting matrix
            *c++ = dot_product(a + i * n, b + j, n);
        }
    }
}

void multiply_a_b_a_transpose(double *a, double *b, double *c, int n) {
    for (register int i = 0; i < n; ++i) { // Loop over the rows of the first matrix
        for (register int j = 0; j < n; ++j) { // Loop over the columns of the second matrix
            // Compute the dot product of the i-th row of the first matrix, and the j-th column of the second matrix
            // up to the diagonal element, since the rest is zero due to the transpose operation.
            *c++ = dot_product(a + i * n, b + j * n, n - j);
        }
    }
}

void multiply_b_transpose_b(double *b, double *c, int n) {
    for (register int i = 0; i < n; ++i) { // Loop over the rows of the matrix
        for (register int j = 0; j < n; ++j) { // Loop over the columns of the matrix
            // Compute the dot product of the j-th column and the i-th column (i.e., the transpose of the i-th row)
            *c++ = dot_product(b + j * n, b + i, n);
        }
    }
}

void compute_C(double* A_B_A_transpose, double* B_B_transpose, double* C, int N) {
    for (register int i = 0; i < N; ++i) { // Loop over the rows of the matrix
        for (register int j = 0; j < N; ++j) { // Loop over the columns of the matrix
            // Compute the sum of corresponding elements of matrices A_B_A_transpose and B_B_transpose
            *C++ = *A_B_A_transpose++ + *B_B_transpose++;
        }
    }
}

double* allocate_matrix(int rows, int cols)
{
    double* ptr = malloc(rows * cols * sizeof(double));
    if (ptr == NULL) {
        // printf("Error: failed to allocate memory for %d x %d matrix\n", rows, cols);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void free_matrices(double *A, double *B, double *C)
{
    free(A);
    free(B);
    free(C);
}

void allocate_all_matrices(int N, double** A_B, double** A_B_A_transpose, double** B_B_transpose, double** C)
{
    *A_B = allocate_matrix(N, N);
    *A_B_A_transpose = allocate_matrix(N, N);
    *B_B_transpose = allocate_matrix(N, N);
    *C = allocate_matrix(N, N);
}

double* my_solver(int N, double *A, double* B) {
    double *A_B, *A_B_A_transpose, *B_B_transpose, *C;

    // Allocate memory for all matrices
    allocate_all_matrices(N, &A_B, &A_B_A_transpose, &B_B_transpose, &C);

    // Multiply A and B matrices and store result in A_B matrix
    multiply_matrices(A, B, A_B, N);

    // Multiply A_B and A_transpose matrices and store result in A_B_A_transpose matrix
    multiply_a_b_a_transpose(A_B, A, A_B_A_transpose, N);

    // Multiply B_transpose and B matrices and store result in B_B_transpose matrix
    multiply_b_transpose_b(B, B_B_transpose, N);

    // Compute C matrix by adding A_B_A_transpose and B_B_transpose matrices
    compute_C(A_B_A_transpose, B_B_transpose, C, N);

    // Free memory for all matrices
    free_matrices(A_B, A_B_A_transpose, B_B_transpose);

    // Return computed C matrix
    return C;
}
