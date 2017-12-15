#include "lp.h"

int main(void){
	int n=4,m=2;
	double c[4]={-1.0,-1.0,0.0,0.0};
	double A[8]={3.0,2.0,1.0,0.0,1.0,2.0,0.0,1.0};
	double b[2]={12.0,8.0};
	int selectindexlist[4]={2,3};
	//
	Simplex simp;
	simp.selectindexlist=selectindexlist;
	simp.n=n;
	simp.m=m;
	//
	Simplex_run(&simp,c,A,b);
	Simplex_printSolutions(&simp);
	return 0;
}