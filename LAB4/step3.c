// Name: Laurence Kim
// Date: 02/04/22
// Title: Lab4 - Step 3
// Description: Threads to perform parallel matrix multiply.

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define N 2
#define M 3
#define L 3

double matrixA[N][M];
double matrixB[M][L];
double matrixC[N][L];

int rowNumbers[N];
pthread_t threads[N];

void * matrixMultiply(void *rowNumber) {
        int n = *(int *)rowNumber;
        int c, r;
        for (c = 0; c < L; c++) {
                for (r = 0; r < M; r++) {
                        matrixC[n][c] += matrixA[n][r] * matrixB[r][c];
                }
        }
        return NULL;
}

void printMatrix(int r, int c, double matrix[r][c]) {
	int i, j;
	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++) {
			printf("%f ", matrix[i][j]);
		}
		printf("\n");
	}	
}

int main() {
	/* Fill in matrices A and B. */
	srand(time(NULL));
	int i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < M; j++)
			matrixA[i][j] = (double)(rand() % 10);
	time_t new_seed = 5;
	time_t * seed_ptr = &new_seed;
	srand(time(seed_ptr));
	for (i = 0; i < M; i++)
		for (j = 0; j < L; j++)
			matrixB[i][j] = (double)(rand() % 10);

	/* Go through each row and send it to the thread */
	for (i = 0; i < N; i++) {
		rowNumbers[i] = i;
		pthread_create(&threads[i], NULL, matrixMultiply, &rowNumbers[i]);	
	}
	/* Join the threads. */
	for (i = 0; i < N; i++) {
		pthread_join(threads[i], NULL);
	}
	/* Print Results. */
	printf("Matrix A: \n");
	printMatrix(N, M, matrixA);
	printf("Matrix B: \n");
	printMatrix(M, L, matrixB);
	printf("Matrix C: \n");
	printMatrix(N, L, matrixC);
	return 0;
}	

