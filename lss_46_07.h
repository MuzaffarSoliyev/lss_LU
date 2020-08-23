#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#pragma warning(disable:4996)

#define epsilon 1e-14

int error, debug;

int lss_46_07(int n, double *A, double *B, double *X, double *tmp);
size_t stringLength(const char *str);
int stringComp(const char *str1, const char *str2);
void printEquation(double *A, double *B, int n);