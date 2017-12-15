#include "matrix.h"

int main(void){
	int i;
	// double a[4]={1.0,2.0,3.0,2.0};
	// double x[4]={1.0,1.0,1.0,1.0};
	// double N[16]={3.0,2.0,1.0,0.0,3.0,5.0,-3.0,-2.0,0.0,-1.0,6.0,9.0,4.0,3.0,-2.0,1.0};
	// createVector(&v1,a,4);
	// createSQMatrix(&m1,N,4);
	// createVector(&v2,x,4);
	double a[2]={1.0,3.0};
	double x[2]={1.0,5.0};
	double N[4]={1.0,2.0,-1.0,4.0};	
	// GaussianEliminate(&m1,&v1);
	// for(i=0;i<4;i++){
	// 	printf("x_%d:%f\n",i,v1.element[i]);
	// }
	GaussianEliminate(N,a,2);
	// Jacobi(N,a,x,2);
	// GS(N,a,x,2);
	for(i=0;i<2;i++){
		printf("x_%d:%f\n",i,a[i]);
	}

	return 0;
}