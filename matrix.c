#include "matrix.h"

double inner(double *a,double *b,int dim){
	int i;
	double *p,*q;
	double value=0.0;
	p=a;
	q=b;
	for(i=0;i<dim;i++){
		value+=(*p++)*(*q++);
	}
	return value;
}
void MVprod(double *M,double *v,double *output,int row,int column){
	int i,j;
	double *p,*q,*r;
	double sum;
	p=M;
	q=output;
	for(i=0;i<row;i++){
		sum=0.0;
		r=v;
		for(j=0;j<column;j++){
			sum+=(*p++)*(*r++);
		}
		(*q++)=sum;
	}
}
double norm2(double *v1,double *v2,int dim){
	double *p,*q;
	double dif,sum=0.0;
	int i=0;
	p=v1;
	q=v2;
	for(i=0;i<dim;i++){
		dif=(*p++)-(*q++);
		sum+=dif*dif;
	}
	return sqrt(sum);
}
void GaussianEliminate(double *A,double *b,int n){
	int i,j,k,pivotindex,n1=n-1;
	double *p,*q,*r,**s,**t,**indexlist,maxv,u,v,*db;
	indexlist=(double **)malloc(n*sizeof(double *));
	p=A;
	s=indexlist;
	for(i=0;i<n;i++){
		(*s++)=p;
		p=p+n;
	}
	//
	db=b;
	s=indexlist;
	for(i=0;i<n1;i++){
		//pivot
		t=s;
		maxv=0.0;
		pivotindex=i;
		for(j=i;j<n;j++){
			if((u=fabs(*(*t++)))>maxv){
				maxv=u;
				pivotindex=j;
			}
		}
		p=*s;
		t=indexlist+pivotindex;
		*s=*t;
		*t=p;
		u=*db;
		*db=*(b+pivotindex);
		*(b+pivotindex)=u;
		//
		t=s+1;
		u=**s;
		r=db+1;
		for(j=i+1;j<n;j++){
			p=*s;
			q=(*(t++))++;
			v=-(*q)/u;
			for(k=i;k<n;k++){
				(*q++)+=v*(*(p++));
			}
			*(r++)+=v*(*db);
		}
		s++;
		db++;
	}
	//
	s=indexlist+n1;
	p=b+n1;
	for(i=0;i<n;i++){
		u=**s;
		q=p+1;
		r=(*s--)+1;
		for(j=n-i;j<n;j++){
			(*p)-=(*q++)*(*r++);
		}
		(*p--)/=u;
	}
	free(indexlist);
}
void Jacobi(double *A,double *b,double *x,int n){
	int i,counter,endflag,n1=n+1;
	double e=1.0e-6;
	double *p,*q,*r,*s,*dlist,*x2;
	dlist=(double*)malloc(n*sizeof(double));
	x2=(double*)malloc(n*sizeof(double));
	//
	p=A;
	q=dlist;
	for(i=0;i<n;i++){
		(*q++)=*p;
		*p=0.0;
		p=p+n1;
	}
	//
	counter=1;
	do{
		MVprod(A,x,x2,n,n);
		p=dlist;
		q=x2;
		r=b;
		s=x;
		endflag=0;
		for(i=0;i<n;i++){
			*q=((*r++)-*q)/(*p++);
			if(fabs(*q-*s)>e){
				endflag=1;
			}
			*s++=*q++;
		}
		counter++;
	}while(endflag);
	printf("Jacobi method takes %d steps\n",counter);
	//
	free(dlist);
	free(x2);
}
void GS(double *A,double *b,double *x,int n){
	double *p,*q,*r,*s,*t,*dlist,u;
	double e=1.0e-6;
	int i,j,counter,n1=n+1,endflag;
	dlist=(double*)malloc(n*sizeof(double));
	p=A;
	q=dlist;
	for(i=0;i<n;i++){
		(*q++)=*p;
		*p=0.0;
		p=p+n1;
	}
	//
	counter=0;
	do{
		p=A;
		q=b;
		r=dlist;
		s=x;
		endflag=0;
		for(i=0;i<n;i++){
			t=x;
			u=0.0;
			for(j=0;j<n;j++){
				u+=(*p++)*(*t++);
			}
			u=((*q++)-u)/(*r++);
			if(fabs(u-*s)>e){
				endflag=1;
			}
			(*s++)=u;
		}
		counter++;
	}while(endflag);
	printf("GS method takes %d steps\n",counter);
	free(dlist);
}


