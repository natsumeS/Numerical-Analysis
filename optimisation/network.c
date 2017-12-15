#include "network.h"

Network *Network_create(int v_num){
	Network *n=(Network*)malloc(sizeof(Network));
	n->from=(Edge**)malloc(v_num*sizeof(Edge*));
	n->edgenumlist=(int *)malloc(v_num*sizeof(int));
	n->vnum=v_num;
	return n;
}
void Network_setVertex(Network *net,int *tolist,double *wlist,int edgenum,int vid){
	int *p;
	double *q;
	Edge *r;
	int i;
	Edge *elist=(Edge*)malloc(edgenum*sizeof(Edge));
	p=tolist;
	q=wlist;
	r=elist;
	for(i=0;i<edgenum;i++){
		r->to=*p++;
		(r++)->w=*q++;
	}
	*(net->from+vid)=elist;
	*(net->edgenumlist+vid)=edgenum;
}
void Network_print(Network *net){
	int i,j,vnum=net->vnum,*p;
	Edge *e;
	p=net->edgenumlist;
	for(i=0;i<vnum;i++){
		printf("%d->\n",i);
		for(j=0;j<*p;j++){
			e=*(net->from+i)+j;
			printf("->%d(%f)\n",e->to,e->w);
		}
		p++;
	}
}
int main(void){
	int N=4;
	int to1[2]={1,2};
	int to2[1]={2};
	int to3[2]={0,3};
	int to4[1]={1};
	double w1[2]={2.0,3.0};
	double w2[1]={4.0};
	double w3[2]={2.0,5.0};
	double w4[1]={1.0};
	//
	Network *net=Network_create(N);
	Network_setVertex(net,to1,w1,2,0);
	Network_setVertex(net,to2,w2,1,1);
	Network_setVertex(net,to3,w3,2,2);
	Network_setVertex(net,to4,w4,1,3);
	//
	Network_print(net);
	//



	return 0;
}
