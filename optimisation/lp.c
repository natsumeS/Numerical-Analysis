#include <stdio.h>
#include <stdlib.h>
#include <float.h>

/*
max : c^T*x
s.t : Ax<=b , x>=0

dim : c,x in R^n
	: b in R^m
	: A in R^(m*n)

indexB:基底変数(0出ない要素のindex)
indexN:非基底変数(0となる要素のindex)

やること
1.	逆行列の計算(LU分解)
	1. cから負のものがあるかチェック->あればそれに対応する変数をselectBへ。なければ終了
	2. x[*]/A[*][selectB]最小の*をselectNへ
	3. c[selectN],A[*][selectB] (*=m/{selectN})=0,A[selectN][selectB]=1になるように基本変形
	4. 1.へ、
*/

double inner(int n,double *a,double *b);
int getSelectB(double *table,int n,int *selectB);
double Simplex(double *table,int n,int m);


double inner(int n,double *a,double *b){
	double value=0.0;
	int i;
	double *p,*q;
	p=a;
	q=b;
	for(i=0;i<n;i++){
		value+=(*p++)*(*q++);
	}
	return value;
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

double Simplex(double *table,int n,int m){
	double *p,*q,*r;
	double s,t;
	int i,j,k,selectB,selectN,n1,m1;
	n1=n+1;
	m1=m+1;
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
	}
	return -*(table+n);
}
int main(void){
	int n,m;
	double *p,*q,*r;
	double s,t;
	int i,j,k,selectB,selectN; 
	n=4;
	m=2;
	double c[4]={-1.0,-1.0,0.0,0.0};
	double A[2][4]={{3.0,2.0,1.0,0.0},{1.0,2.0,0.0,1.0}};
	double b[2]={12.0,8.0};
	int indexBlist[2]={0,1};
	int indexNlist[2]={2,3};
	double x[2]={12.0,8.0};
	double solutions=0.0;
	double *table;
	table=(double*)malloc((m+1)*(n+1)*sizeof(double));
	p=table;
	q=c;
	for(i=0;i<n;i++){
		(*p++)=(*q++);
	}
	(*p++)=solutions;
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			(*p++)=A[i][j];
		}
		(*p++)=x[i];
	}
	printf("optimisation=%f\n",Simplex(table,n,m));
	p=table;
	for(i=0;i<(n+1)*(m+1);i++){
		printf("%f\n",*p++);
	}
	return 0;


}