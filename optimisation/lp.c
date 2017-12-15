#include "lp.h"

/*
max : c^T*x
s.t : Ax<=b , x>=0

dim : c,x in R^n
	: b in R^m
	: A in R^(m*n)

indexB:基底変数(0出ない要素のindex)
indexN:非基底変数(0となる要素のindex)


1. cから負のものがあるかチェック->あればそれに対応する変数をselectBへ。なければ終了
2. x[*]/A[*][selectB]最小の*をselectNへ
3. c[selectN],A[*][selectB] (*=m/{selectN})=0,A[selectN][selectB]=1になるように基本変形
4. 1.へ、
------
c:目的関数の係数 c in R^n
A:制約条件の係数 A in R^(m*n)
b:制約条件の右辺 b in R^m
*/
void Simplex_setTable(Simplex *simp,double *c,double *A,double *b){
	double *p,*q,*r,*table,u,v;
	int *s;
	int i,j,n=simp->n,m=simp->m;
	table=(double*)malloc((n+1)*(m+1)*sizeof(double));
	//基底解を求める。->V
	double *M,*V;
	M=(double*)malloc(m*m*sizeof(double));
	V=(double*)malloc(m*sizeof(double));
	p=M;
	q=V;
	for(i=0;i<m;i++){
		s=simp->selectindexlist;
		for(j=0;j<m;j++){
			(*p++)=*(A+i*n+(*s++));
		}
		(*q++)=1.0;
	}
	GS(M,b,V,simp->m);
	free(M);
	//現在の最適値の計算->optimisation
	p=table;
	q=c;
	r=V;
	s=simp->selectindexlist;
	u=0.0;
	for(i=0;i<n;i++){
		if(i==*s){
			if(*r<0){
				printf("selectindexlist invalid!");
				exit(1);
			}
			u+=(*q)*(*r++);
			s++;
		}
		*p++=*q++;
	}
	*p++=u;
	//
	q=A;
	r=V;
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			*p++=*q++;
		}
		*p++=*r++;
	}
	free(V);
	simp->table=table;
}
int getSelectB(double *table,int n,int *selectB){
	int i;
	double *p;
	p=table;
	for(i=0;i<n;i++){
		if((*p++)<0){
			*selectB=i;
			return 1;
		}
	}
	*selectB=-1;
	return 0;
}
void Simplex_runTable(Simplex *simp){
	double *p,*q,*r,*table=simp->table;
	double s,t;
	int i,j,k,selectB,selectN,n=simp->n,m=simp->m,n1=n+1,m1=m+1;
	while(getSelectB(table,n,&selectB)){
		selectN=0;
		p=table+n1+selectB;
		q=table+n*2+1;
		s=DBL_MAX;
		for(i=1;i<=m;i++){
			if((t=(*q)/(*p))<s){
				s=t;
				selectN=i;
			}
			p=p+n1;
			q=q+n1;
		}
		p=table+n1*selectN;
		s=*(p+selectB);
		for(i=0;i<=n;i++){
			(*p++)/=s;
		}
		p=table;
		q=table+n1*selectN;
		for(i=0;i<=m;i++){
			if(i==selectN){
				p=p+n1;
				continue;
			}
			r=q;
			s=*(p+selectB);
			for(j=0;j<=n;j++){
				(*p++)-=(*r++)*s;
			}
		}
		simp->selectindexlist[selectN-1]=selectB;
	}
}
double Simplex_getOptValue(Simplex *simp){
	return -*(simp->table+simp->n);
}
double *Simplex_getOptSolution(Simplex *simp){
	double *p,*q,*x,s;
	int *r;
	int i,n=simp->n,m=simp->m;
	x=(double*)malloc(n*sizeof(double));
	p=simp->table+2*n+1;
	q=x;
	r=simp->selectindexlist;
	for(i=0;i<m;i++){
		s=0.0;
		if(i==*r){
			s=*p;
			p=p+n+1;
			r++;
		}
		*q++=s;
	}
	return x;
}
void Simplex_run(Simplex *simp,double *c,double *A,double *b){
	Simplex_setTable(simp,c,A,b);
	Simplex_runTable(simp);
}
void Simplex_printSolutions(Simplex *simp){
	int i;
	printf("-------optimisation(Simplex)--------\n");
	printf("optimal_value=%f\n",Simplex_getOptValue(simp));
	double *x=Simplex_getOptSolution(simp);
	for(i=0;i<simp->n;i++){
		printf("x_%d:%f\n",i,x[i]);
	}
}
