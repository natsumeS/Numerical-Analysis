#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double inner(double *a,double *b,int dim);
void MVprod(Matrix *M,Vector *v,Vector *output);
double norm2(Vector *v1,Vector *v2);
void GaussianEliminate(Matrix *A,Vector *b);
void Jacobi(Matrix *A,Vector *b,Vector *x);
void GS(SQMatrix *A,Vector *b,Vector *x);