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
Vector *MVprod(Matrix *M,Vector *v){
	int row,column,i,j;
	double *p,*q,*r;
	double sum;
	if((column=M->column)!=v->dim){
		printf("M's column and v'dim not match");
		exit(1);
	}
	row=M->row;
	Vector *output;
	double *outv;
	output=(Vector*)malloc(sizeof(Vector));
	outv=(double*)malloc(row*sizeof(double));
	output->dim=row;
	output->element=outv;
	p=M->element;
	q=outv;
	for(i=0;i<row;i++){
		sum=0.0;
		r=v->element;
		for(j=0;j<column;j++){
			sum+=(*p++)*(*r++);
		}
		(*q++)=sum;
	}
	return output;
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
}
int main(void){
	int i;
	double a[4]={1.0,2.0,3.0,2.0};
	double N[16]={3.0,2.0,1.0,0.0,3.0,5.0,-3.0,-2.0,0.0,-1.0,6.0,9.0,4.0,3.0,-2.0,1.0};
	Vector v1;
	SQMatrix m1;
	createVector(&v1,a,4);
	createSQMatrix(&m1,N,4);
	GaussianEliminate(&m1,&v1);
	for(i=0;i<4;i++){
		printf("x_%d:%f\n",i,v1.element[i]);
	}

	return 0;
}


