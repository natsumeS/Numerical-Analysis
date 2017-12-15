#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double inner(double *a,double *b,int dim);
void MVprod(double *M,double *v,double *output,int row,int column);
double norm2(double *v1,double *v2,int dim);
void GaussianEliminate(double *A,double *b,int n);
void Jacobi(double *A,double *b,double *x,int n);
void GS(double *A,double *b,double *x,int n);