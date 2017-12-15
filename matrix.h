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
void createSQMatrix(SQMatrix *m,double *e,int dim);
double inner(Vector *a,Vector *b);
Vector *MVprod(Matrix *M,Vector *v);
double norm2(Vector *v1,Vector *v2);
void GaussianEliminate(SQMatrix *A,Vector *b);