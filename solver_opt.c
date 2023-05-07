/*
 * Tema 2 ASC
 * 2023 Spring
 */
#include "utils.h"

// Memory
double* allocate_matrix(int rows, int cols);
void free_matrices(double *A, double *B, double *C);
void allocate_all_matrices(int N, double** A_B, double** A_B_A_transpose, double** B_B_transpose, double** C);

// Compute 
void matrix_multiply(double* A_B, double* A, double* B, int N);
void matrix_multiply_transpose(double* A_B_A_transpose, double* A_B, double* A, int N);
void matrix_multiply_b_transpose_b(double* B_B_transpose, double* B, int N);
void matrix_addition(double* C, double* A_B_A_transpose, double* B_B_transpose, int N);


double* my_solver(int N, double *A, double* B) {
    double *A_B, *A_B_A_transpose, *B_B_transpose, *C;

    // Allocate memory for all matrices
    allocate_all_matrices(N, &A_B, &A_B_A_transpose, &B_B_transpose, &C);

    // Multiply A and B matrices and store result in A_B matrix
    matrix_multiply(A_B, A, B, N);

    // Multiply A_B and A_transpose matrices and store result in A_B_A_transpose matrix
    matrix_multiply_transpose(A_B_A_transpose, A_B, A, N);

    // Multiply B_transpose and B matrices and store result in B_B_transpose matrix
    matrix_multiply_b_transpose_b(B_B_transpose, B, N);

    // Compute C matrix by adding A_B_A_transpose and B_B_transpose matrices
    matrix_addition(C, A_B_A_transpose,B_B_transpose, N);

    // Free memory for all matrices
    free_matrices(A_B, A_B_A_transpose, B_B_transpose);

    // Return computed C matrix
    return C;
}


void matrix_multiply(double* A_B, double* A, double* B, int N) {
    // Loop variables and temporary variables as registers
    register int i, j, k;
    register double* A_B_ptr;
    register double* A_ptr;
    register double* B_ptr;
    register double s;
    
    // Iterate over the rows of matrix A_B
    for (i = 0; i < N; ++i) {
        // Setting the pointer to the start of row i in matrix A_B
        A_B_ptr = A_B + i * N;
        // Iterate over the columns of matrix A_B
        for (j = 0; j < N; ++j) {
            // Initialize the sum to zero
            s = 0;
            // Setting the pointer to the start of row i in matrix A
            A_ptr = A + i * N + i;
            // Setting the pointer to the start of column j in matrix B
            B_ptr = B + i * N + j;
            // Iterate over the elements in row i of matrix A and column j of matrix B
            for (k = i; k < N; ++k, ++A_ptr, B_ptr += N) {
                // Compute the dot product of row i of matrix A and column j of matrix B
                s += *A_ptr * *B_ptr;
            }
            // Storing the result in the current element of matrix A_B
            *A_B_ptr++ = s;
        }
    }
}

void matrix_multiply_transpose(double* A_B_A_transpose, double* A_B, double* A, int N)
{
    // Loop variables and temporary variables as registers
    register int i, j, k;
    register double* A_B_A_transpose_ptr;
    register double* A_B_ptr;
    register double* A_transpose_ptr;
    register double s;
    
    // Iterate over the rows of matrix A_B_A_transpose
    for (i = 0; i < N; ++i) {
        // set the pointer to the start of row i in matrix A_B_A_transpose
        A_B_A_transpose_ptr = A_B_A_transpose + i * N;
        // Iterate over the columns of matrix A_B_A_transpose
        for (j = 0; j < N; ++j) {
            // initialize the sum to zero
            s = 0;
            // set the pointer to the start of element (i,j) in matrix A_B
            A_B_ptr = A_B + i * N + j;
            // set the pointer to the start of row j in the transpose of matrix A
            A_transpose_ptr = A + j * N + j;
            // Iterate over the elements in row j of the transpose of matrix A
            // and column j and after in matrix A_B
            for (k = j; k < N; ++k, ++A_B_ptr, ++A_transpose_ptr) {
                // compute the dot product of column j of matrix A_B and row j of the transpose of matrix A
                s += *A_B_ptr * *A_transpose_ptr;
            }
            // store the result in the current element of matrix A_B_A_transpose
            *A_B_A_transpose_ptr++ = s;
        }
    }
}

void matrix_multiply_b_transpose_b(double* B_B_transpose, double* B, int N)
{
    // Loop variables and temporary variables as registers
    register int i, j, k;
    register double* B_B_transpose_ptr;
    register double* B_transpose_ptr1;
    register double* B_transpose_ptr2;
    register double s;
    
    // Iterate over each row of B_B_transpose
    for (i = 0; i < N; ++i) {
        B_B_transpose_ptr = B_B_transpose + i * N;
        // Iterate over each column of B_B_transpose
        for (j = 0; j < N; ++j) {
            s = 0;
            B_transpose_ptr1 = B + j * N;   // points to the start of the j-th column of B
            B_transpose_ptr2 = B + i;       // points to the i-th element of B
            // Iterate over each element of the j-th column of B and the i-th row of B (with a stride of N)
            for (k = 0; k < N; ++k, ++B_transpose_ptr1, B_transpose_ptr2 += N) {
                s += *B_transpose_ptr1 * *B_transpose_ptr2; // compute the dot product of the j-th column and i-th row
            }
            *B_B_transpose_ptr++ = s; // store the result in the i-th row and j-th column of B_B_transpose
        }
    }
}

void matrix_addition(double* C, double* A_B_A_transpose, double* B_B_transpose, int N)
{
    // Loop variables and temporary variables as registers
    register int i, j;
    register double* C_ptr;
    register double* A_B_A_transpose_ptr;
    register double* B_B_transpose_ptr;
    register double sum;
    
    // Iterate over rows of C, A_B_A_transpose, and B_B_transpose
    for (i = 0; i < N; ++i) {
        C_ptr = C + i * N;                              // pointer to the i-th row of C
        A_B_A_transpose_ptr = A_B_A_transpose + i * N;  // pointer to the i-th row of A_B_A_transpose
        B_B_transpose_ptr = B_B_transpose + i * N;      // pointer to the i-th row of B_B_transpose
        for (j = 0; j < N; ++j) {
            // Adding the corresponding elements of A_B_A_transpose and B_B_transpose
            sum = *A_B_A_transpose_ptr++ + *B_B_transpose_ptr++;
            // Storing the sum in the corresponding element of C
            *C_ptr++ = sum;
        }
    }
}

double* allocate_matrix(int rows, int cols)
{
    double* ptr = calloc(rows * cols, sizeof(double));
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
