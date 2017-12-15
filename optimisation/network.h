#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int to;
	double w;
}Edge;
typedef struct{
	int vnum;
	int *edgenumlist;
	Edge **from;
}Network;

Network *Network_create(int v_num);
void Network_setVertex(Network *net,int *tolist,double *wlist,int edgenum,int vid);
void Network_print(Network *net);