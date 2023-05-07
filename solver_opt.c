/*
 * Tema 2 ASC
 * 2023 Spring
 */
#include <stdlib.h>

/* Memory */
int alloc_matrix(int N, double **result_matrix, double **A_transpose, 
                        double **B_transpose, double **A_times_A_transpose);
void dealloc_matrix(double *A_transpose, double *B_transpose, double *A_times_A);

/* Compute */
void compute_transpose(int N, double* A, double* B);
void compute_multiply(int N, double* A, double* B, double* C);
void compute_square(int N, double* A, double* B);

double* my_solver(int N, double *A, double* B)
{
	int res;
	double *A_transpose;     // Transpose of matrix A
	double *B_transpose;     // Transpose of matrix B
	double *A_times_A;       // Square of matrix A
	double *result_matrix;   // Output matrix C

    res = alloc_matrix(N, &result_matrix, &A_transpose, &B_transpose, &A_times_A);
	if (res == -1) {
		dealloc_matrix(A_transpose, B_transpose, A_times_A);
		return 0;
	}

    // Compute the transpose of matrix A and store it in A_transpose
    compute_transpose(N, A, A_transpose);

    // Compute the transpose of matrix B and store it in B_transpose
    compute_transpose(N, B, B_transpose);

    // Compute the product of matrix B and the transpose of matrix A, and store it in C
    compute_multiply(N, B, A_transpose, result_matrix);

    // Compute the product of matrix A and the transpose of matrix A, and store it in A_times_A
    compute_square(N, A, A_times_A);

    // Compute the product of matrix A_times_A and the transpose of matrix B, and store it in C
    compute_multiply(N, A_times_A, B_transpose, result_matrix);

    // Free the memory allocated for the auxiliary matrices
    dealloc_matrix(A_transpose, B_transpose, A_times_A);

    // Return the result matrix C
    return result_matrix;
}

/*
 * This function allocates memory for four matrices of size N x N: result_matrix,
 * A_transpose, B_transpose, and A_times_A_transpose. It takes in N as an integer, 
 * and four double pointers that will be used to store the address of each allocated 
 * matrix. 
 */
int alloc_matrix(int N, double **result_matrix, double **A_transpose, 
                        double **B_transpose, double **A_times_A_transpose) {

    // Calculate the size of a matrix with N rows and N columns in bytes.
    int size = N * N * sizeof(double);

    // Allocate memory for result_matrix and check if the allocation was successful.
    *result_matrix = malloc(size);
    if (*result_matrix == NULL) {
        // printf("Error: failed to allocate memory for result_matrix of size %d x %d.\n", N, N);
        return -1;
    }

    // Allocate memory for A_transpose and check if the allocation was successful.
    *A_transpose = malloc(size);
    if (*A_transpose == NULL) {
        // printf("Error: failed to allocate memory for A_transpose of size %d x %d.\n", N, N);
        free(*result_matrix); // Free the previously allocated memory.
        return -1;
    }

    // Allocate memory for B_transpose and check if the allocation was successful.
    *B_transpose = malloc(size);
    if (*B_transpose == NULL) {
        // printf("Error: failed to allocate memory for B_transpose of size %d x %d.\n", N, N);
        free(*result_matrix); // Free the previously allocated memory.
        free(*A_transpose); // Free the previously allocated memory.
        return -1;
    }

    // Allocate memory for A_times_A_transpose and check if the allocation was successful.
    *A_times_A_transpose = malloc(size);
    if (*A_times_A_transpose == NULL) {
        // printf("Error: failed to allocate memory for A_times_A_transpose of size %d x %d.\n", N, N);
        free(*result_matrix); // Free the previously allocated memory.
        free(*A_transpose); // Free the previously allocated memory.
        free(*B_transpose); // Free the previously allocated memory.
        return -1;
    }
	return 0;
}

/* This function deallocates memory for three matrices: A_transpose, B_transpose, and A_times_A.
It takes in three pointers to the matrices. */
void dealloc_matrix(double *A_transpose, double *B_transpose, double *A_times_A) {
    free(A_transpose); // Deallocate memory for A_transpose
    free(B_transpose); // Deallocate memory for B_transpose
    free(A_times_A); // Deallocate memory for A_times_A
}

/* Transposes a square matrix A of size N by N and stores the result in B. */
void compute_transpose(int N, double* A, double* B) {
    register int i, j;
    register double* A_transpose_ptr;
    register double* A_ptr;

    // Iterate over the rows of A and columns of B
    for (i = 0; i != N; ++i) {
        // Set a pointer to the i-th column of B
        A_transpose_ptr = B + i;
        // Set a pointer to the i-th row of A
        A_ptr = A + i * N;

        // Iterate over the columns of A and rows of B
        for (j = 0; j != N; ++j, A_transpose_ptr += N, ++A_ptr) {
            // Transpose the current element of A to B
            *A_transpose_ptr = *A_ptr;
        }
    }
}
/* Performs matrix multiplication A * B and stores the result in C. */
void compute_multiply(int N, double* A, double* B, double* C) {
    register int i, j, k;
    register double result;
    register double* C_ptr;
    register double* B_copy;
    register double* A_ptr;
    register double* B_ptr;

    for (i = 0; i != N; ++i) {
        // pointer to the start of the i-th row in C
        C_ptr = C + i * N;
        // pointer to the start of the i-th row in B
        B_copy = B + i * N;

        for (j = 0; j != N; ++j, ++C_ptr) {
            // compute the dot product of the j-th column in A and i-th row in B
            result = 0;

            // pointer to the start of the j-th column in A
            A_ptr = A + j * (N + 1);
            // pointer to the start of the i-th row in B
            B_ptr = B_copy + j;

            // compute dot product using loop unrolling for performance
            for (k = j; k < N; ++k, ++B_ptr, ++A_ptr)
                result += *B_ptr * *A_ptr;

            // store the result in C
            *C_ptr = result;
        }
    }
}

/*
 * Calculates the square of matrix A and stores the result in matrix B.
 * Uses an optimization where it only calculates the upper triangle of the
 * result matrix, since the matrix is symmetric.
 */
void compute_square(int N, double* A, double* B) {
    register int i, j, k;
    register double result;
    register double* A_times_A_ptr;
    register double* A_copy;
    register double* A_ptr;
    register double* A_transpose_ptr;

    for (i = 0; i != N; ++i) {
        // Pointers for the diagonal and below it
        A_times_A_ptr = B + i * (N + 1);
        A_copy = A + i * N;

        for (j = i; j != N; ++j, ++A_times_A_ptr) {
            result = 0;

            // Pointers for the current row of A and column of A transpose
            A_ptr = A_copy + i;
            A_transpose_ptr = A + j * N + i;

            // Calculate the dot product of the i-th row of A and the j-th
            // column of A transpose, up to the diagonal
            for (k = i; k <= j; ++k, ++A_ptr, ++A_transpose_ptr)
                result += *A_ptr * *A_transpose_ptr;

            // Store the result in the output matrix B
            *A_times_A_ptr = result;
        }
    }
}
