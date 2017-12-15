#include <float.h>
#include "../matrix.h"

typedef struct{
	double *table;
	int *selectindexlist;
	int n;
	int m;
} Simplex;
void Simplex_setTable(Simplex *simp,double *c,double *A,double *b);
int getSelectB(double *table,int n,int *selectB);
void Simplex_runTable(Simplex *simp);
double Simplex_getOptValue(Simplex *simp);
double *Simplex_getOptSolution(Simplex *simp);
void Simplex_run(Simplex *simp,double *c,double *A,double *b);
void Simplex_printSolutions(Simplex *simp);