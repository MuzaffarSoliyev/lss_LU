#include "lss_46_07.h"

void multiplicationMatrix(double *A, double *B, int n, double *AB, double precision)
{
	int i, j, k;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			AB[i*n + j] = 0;
			for (k = 0; k < n; k++)
			{
				AB[i*n + j] += A[i*n + k] * B[k*n + j];
			}
			if (fabs(AB[i*n + j]) < precision)
			{
				AB[i*n + j] = 0;
			}
		}
	}
}

void printEquation(double *A, double *B, int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%lf ", A[i*n + j]);
		}
		printf(" = %lf", B[i]);
		printf("\n");
	}
	printf("\n");
}

void printMatrix(double *A, int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%lf ", A[i*n + j]);
		}
		printf("\n");
	}
	printf("\n");
}

size_t lss_memsize_46_07(int n)
{
	return n*sizeof(double);
}

int lss_46_07(int n, double *A, double *B, double *X, double *tmp)
{
	int i, k, j;
	double *L = tmp, *U = tmp + n*n, sumL, sumU;
	
	for (i = 0; i < n*n; i++)
	{
		L[i] = 0;
		U[i] = 0;
	}
	
	
	for (i = 0; i < n; i++)
	{
		L[i*n + 0] = A[i*n + 0];
		U[i*n + i] = 1;
		//X[i] = 0;
	}

	//printMatrix(L, n);
	//printMatrix(U, n);

	if (debug)
	{
		printMatrix(L, n);
		printMatrix(U, n);
	}

	for (k = 0; k < n; k++)
	{
		if (fabs(L[0 * 0 + 0]) > epsilon)
		{
			U[0 * n + k] = A[0 * n + k] / L[0 * 0 + 0];
		}
		else
		{
			return -1;
		}
	}
	//printMatrix(L, n);
	//printMatrix(U, n);

	if (debug)
	{
		printMatrix(L, n);
		printMatrix(U, n);
	}


	for (i = 1; i < n; i++)
	{
		for (k = i; k < n; k++)
		{
			sumL = 0;
			for (j = 0; j < i; j++)
			{
				sumL += L[k*n + j] * U[j*n + i];
			}
			L[k*n + i] = A[k*n+i] - sumL;
		}
	

	
		for (k = i; k < n; k++)
		{
			sumU = 0;
			for (j = 0; j < i; j++)
			{
				sumU += L[i*n + j] * U[j*n + k];
			}
			if (fabs(L[i*n + i]) > epsilon)
			{
				U[i*n + k] = (A[i*n + k] - sumU) / L[i*n + i];
			}
			else
			{
				return -1;
			}
		}
	}

	if (debug)
	{
		printMatrix(L, n);
		printMatrix(U, n);
	}

	//printMatrix(A, n);
	//printMatrix(L, n);
	//printMatrix(U, n);
	//multiplicationMatrix(L, U, n, A, epsilon);
	//printMatrix(A, n);
	//printMatrix(L, n);
	//printMatrix(U, n);
	//print(A, B, n);

	if (debug)
	{
		printEquation(L, B, n);
	}

	for (i = 0; i <n; i++)
	{
		sumL = 0;
		for (j = 0; j < i; j++)
		{
			sumL += L[i*n + j] * X[j];
		}
		
			X[i] = (B[i] - sumL) / L[i*n + i];
		
	}
	
	if (debug)
	{
		printEquation(U, X, n);
	}

	for (i = n - 1; i >= 0; i--)
	{
		sumU = 0;
		for (j = i + 1; j < n; j++)
		{
			sumU += U[i*n + j] * X[j];
		}
		
			X[i] = (X[i] - sumU) / U[i*n + i];
	
	}
	
	return 0;
}
