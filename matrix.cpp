#include <iostream>
#include <math.h>
using namespace std;


class Vector{
public:
	int dim;
	double *element;
	Vector(double *e,int dim);
	void print();
	double get_inner(Vector *v2);
	double get_norm2(Vector *v2);
	double operator*(Vector v2){
		return get_inner(&v2);
	}
	double operator||(Vector v2){
		return get_norm2(&v2);
	}
};
class Matrix{
public:
	int row;
	int column;
	double *element;
	Matrix(double *e,int row,int column);
	Vector MVprod(Vector *v);
	void print();
	Vector operator*(Vector v){
		return MVprod(&v);
	}
};
//
//

Matrix::Matrix(double *e,int row,int column){
	this->row=row;
	this->column=column;
	this->element=e;
}
void Matrix::print(){
	int i,j;
	double *p;
	cout<<"---Matrix---"<<endl;
	cout<<"row="<<row<<",column="<<column<<endl;
	for(i=0,p=element;i<row;i++){
		for(j=0;j<column;j++){
			cout<<*p++<<",";
		}
		cout<<endl;
	}
}
Vector Matrix::MVprod(Vector *v){
	int i,j;
	if(column!=v->dim){
		cout<<"Matrix::MVprod->dim error"<<endl;
		exit(1);
	}
	double *p,*q,*r,*ov,sum;
	ov=(double*)malloc(row*sizeof(double));
	p=element;
	q=ov;
	for(i=0;i<row;i++){
		r=v->element;
		sum=0.0;
		for(j=0;j<column;j++){
			sum+=(*p++)*(*r++);
		}
		(*q++)=sum;
	}
	Vector output(ov,row);
	return output;
}
Vector::Vector(double *e,int dim){
	this->dim=dim;
	this->element=e;
}
void Vector::print(){
	int i;
	double *p;
	cout<<"---Vector---"<<endl;
	cout<<"dim:"<<dim<<endl;
	for(i=0,p=element;i<dim;i++){
		cout<<"v_"<<i<<":"<<*p++<<endl;
	}
}
double Vector::get_inner(Vector *v2){
	int i;
	if(dim!=v2->dim){
		cout<<"Vector::inner->dim error"<<endl;
		exit(1);
	}
	double *p,*q,value=0.0;
	for(i=0,p=element,q=v2->element;i<dim;i++){
		value+=(*p++)*(*q++);
	}
	return value;
}
double Vector::get_norm2(Vector *v2){
	double *p,*q,dif,sum=0.0;
	int i;
	for(i=0,p=element,q=v2->element;i<dim;i++){
		dif=(*p++)-(*q++);
		sum+=dif*dif;
	}
	return sqrt(sum);
}
void operator*(double d,Vector v){
	double *p;
	int i,dim=v.dim;
	for(i=0,p=v.element;i<dim;i++){
		(*p++)*=d;
	}
}
int main(){
	double a[3]={3.0,4.0,5.0};
	double b[3]={1,2,3};
	double m[6]={1,2,3,4,5,6};
	Matrix m1(m,2,3);
	m1.print();
	Vector v1(a,3),v2(b,3);
	// cout<<"inner:"<<v1*v2<<endl;
	// cout<<"norm2:"<<(v1||v2)<<endl;
	// 4.0*v1;
	Vector v3=m1*v1;
	v3.print();
	return 0;
}