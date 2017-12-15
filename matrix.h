#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
	int dim;
	double *element;
} Vector;
typedef struct{
	int row;
	int column;
	double *element;
} Matrix,SQMatrix;

void createVector(Vector *v,double *e,int dim);
void createMatrix(Matrix *m,double *e,int row,int column);
void createSQMatrix(Matrix *m,double *e,int dim);
double inner(Vector *a,Vector *b);
void MVprod(Matrix *M,Vector *v,Vector *output);
double norm2(Vector *v1,Vector *v2);
void GaussianEliminate(Matrix *A,Vector *b);
void Jacobi(Matrix *A,Vector *b,Vector *x);
void GS(SQMatrix *A,Vector *b,Vector *x);