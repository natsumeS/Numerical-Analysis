#include <iostream>
#include "heap.h"
using namespace std;

double getv(int* x){
	return *x;
}
int main(void){
	int a[8]={3,1,4,5,8,2,42,6};
	int *b[8]={a,a+1,a+2,a+3,a+4,a+5,a+6,a+7};
	Heap<int> heap(8,8,b,getv);
	int i=0;
	for(i=0;i<9;i++){
		cout<<*heap.pull()<<endl;
	}
	cout<<"size="<<heap.size<<endl;
} 