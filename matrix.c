#include "matrix.h"

void createVector(Vector *v,double *e,int dim){
	v->element=e;
	v->dim=dim;
}
void createMatrix(Matrix *m,double *e,int row,int column){
	m->row=row;
	m->column=column;
	m->element=e;
}
void createSQMatrix(SQMatrix *m,double *e,int dim){
	m->element=e;
	m->row=dim;
	m->column=dim;
}
double inner(Vector *a,Vector *b){
	int dim,i;
	double *p,*q;
	double value=0.0;
	if((dim=a->dim)!=b->dim){
		printf("dim dont match");
		exit(1);
	}
	p=a->element;q=b->element;
	for(i=0;i<dim;i++){
		value+=(*p++)*(*q++);
	}
	return value;
}
void MVprod(Matrix *M,Vector *v,Vector *output){
	int row,column,i,j;
	double *p,*q,*r;
	double sum;
	if((column=M->column)!=v->dim){
		printf("M's column and v'dim not match");
		exit(1);
	}
	row=M->row;
	p=M->element;
	q=output->element;
	for(i=0;i<row;i++){
		sum=0.0;
		r=v->element;
		for(j=0;j<column;j++){
			sum+=(*p++)*(*r++);
		}
		(*q++)=sum;
	}
}
double norm2(Vector *v1,Vector *v2){
	double *p,*q;
	double dif,sum=0.0;
	int dim,i=0;
	if((dim=v1->dim)!=v2->dim){
		printf("dim dont match");
		exit(1);
	}
	p=v1->element;
	q=v2->element;
	for(i=0;i<dim;i++){
		dif=(*p++)-(*q++);
		sum+=dif*dif;
	}
	return sqrt(sum);
}
void GaussianEliminate(SQMatrix *A,Vector *b){
	int i,j,k,pivotindex,n=A->row,n1=n-1;
	double *p,*q,*r,*output,**s,**t,**indexlist,maxv,u,v,*db;
	if(n!=A->column||n!=b->dim){
		exit(1);
	}
	indexlist=(double **)malloc(n*sizeof(double *));
	p=A->element;
	s=indexlist;
	for(i=0;i<n;i++){
		(*s++)=p;
		p=p+n;
	}
	//
	db=b->element;
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
		*db=*(b->element+pivotindex);
		*(b->element+pivotindex)=u;
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
	p=b->element+n1;
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
void Jacobi(SQMatrix *A,Vector *b,Vector *x){
	int i,counter,endflag,n=A->row,n1=n+1;
	double e=1.0e-6;
	double *p,*q,*r,*s,*dlist;
	Vector *x2;
	if(n!=A->column||n!=b->dim||n!=x->dim){
		exit(1);
	}
	dlist=(double*)malloc(n*sizeof(double));
	x2=(Vector*)malloc(sizeof(Vector));
	x2->dim=n;
	x2->element=(double*)malloc(n*sizeof(double));
	//
	p=A->element;
	q=dlist;
	for(i=0;i<n;i++){
		(*q++)=*p;
		*p=0.0;
		p=p+n1;
	}
	//
	counter=1;
	do{
		MVprod(A,x,x2);
		p=dlist;
		q=x2->element;
		r=b->element;
		s=x->element;
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
	double *p,*q,*r,*s,*t,*dlist,u;
	double e=1.0e-6;
	int i,j,counter,n=A->row,n1=n+1,endflag;
	if(n!=A->column||n!=b->dim||n!=x->dim){
		exit(1);
	}
	dlist=(double*)malloc(n*sizeof(double));
	p=A->element;
	q=dlist;
	for(i=0;i<n;i++){
		(*q++)=*p;
		*p=0.0;
		p=p+n1;
	}
	//
	counter=0;
	do{
		p=A->element;
		q=b->element;
		r=dlist;
		s=x->element;
		endflag=0;
		for(i=0;i<n;i++){
			t=x->element;
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

}

int main(void){
	int i;
	Vector v1,v2;
	SQMatrix m1;
	// double a[4]={1.0,2.0,3.0,2.0};
	// double x[4]={1.0,1.0,1.0,1.0};
	// double N[16]={3.0,2.0,1.0,0.0,3.0,5.0,-3.0,-2.0,0.0,-1.0,6.0,9.0,4.0,3.0,-2.0,1.0};
	// createVector(&v1,a,4);
	// createSQMatrix(&m1,N,4);
	// createVector(&v2,x,4);
	double a[2]={1.0,3.0};
	double x[2]={1.0,5.0};
	double N[4]={1.0,2.0,-1.0,4.0};
	createVector(&v1,a,2);
	createSQMatrix(&m1,N,2);
	createVector(&v2,x,2);
	
	// GaussianEliminate(&m1,&v1);
	// for(i=0;i<4;i++){
	// 	printf("x_%d:%f\n",i,v1.element[i]);
	// }
	// Jacobi(&m1,&v1,&v2);
	GS(&m1,&v1,&v2);
	for(i=0;i<2;i++){
		printf("x_%d:%f\n",i,v2.element[i]);
	}

	return 0;
}


