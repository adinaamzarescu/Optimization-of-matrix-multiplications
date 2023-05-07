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
void matrix_multiplication(int N, double *A, double *B, double *A_B);
void multiply_A_B_A_transpose(int N, double *A_B, double *A, double *A_B_A_transpose);
void multiply_B_B_transpose(int N, double *B, double *B_B_transpose);
void add_matrices(int N, double *A_B_A_transpose, double *B_B_transpose, double *C);

// Main function
double* my_solver(int N, double *A, double *B)
{
    double *A_B, *A_B_A_transpose, *B_B_transpose, *C;

    // Allocate memory for all matrices
    allocate_all_matrices(N, &A_B, &A_B_A_transpose, &B_B_transpose, &C);

    // Matrix multiplication of A and B
    matrix_multiplication(N, A, B, A_B);

    // Multiply the resulting matrix from step 1 with the transpose of A
    multiply_A_B_A_transpose(N, A_B, A, A_B_A_transpose);

    // Multiply the transpose of B with B
    multiply_B_B_transpose(N, B, B_B_transpose);

    // Add the resulting matrices from steps 2 and 3
    add_matrices(N, A_B_A_transpose, B_B_transpose, C);

    // Free memory for all matrices
    free_matrices(A_B, A_B_A_transpose, B_B_transpose);

    return C;
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

// Function to perform matrix multiplication of A and B
void matrix_multiplication(int N, double *A, double *B, double *A_B)
{
	int i, j, k;
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            for (k = i; k < N; ++k) {
                A_B[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }
}

// Function to multiply the resulting matrix from step 1 with the transpose of A
void multiply_A_B_A_transpose(int N, double *A_B, double *A, double *A_B_A_transpose)
{
	int i, j, k;
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            for (k = j; k < N; ++k) {
                A_B_A_transpose[i * N + j] += A_B[i * N + k] * A[j * N + k];
            }
        }
    }
}

// Function to multiply the transpose of B with B
void multiply_B_B_transpose(int N, double *B, double *B_B_transpose)
{
	int i, j, k;
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            for (k = 0; k < N; ++k) {
                B_B_transpose[j * N + i] += B[k * N + j] * B[i * N + k];
            }
        }
    }
}

// Function to add the resulting matrices from steps 2 and 3
void add_matrices(int N, double *A_B_A_transpose, double *B_B_transpose, double *C)
{
	int i, j;
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            C[i * N + j] = A_B_A_transpose[i * N + j] + B_B_transpose[i * N + j];
        }
    }
}
