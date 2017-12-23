#include "heap.h"
#include "network.h"

Edge **Kruskal(Network *net){
	int *selectVlist,i,j,*p;
	Edge **q,*r,**s,**edgelist,**output;
	selectVlist=(int *)malloc(net->v_num*sizeof(int));
	edgelist=(Edge **)malloc(net->e_num*sizeof(Edge *));
	output=(Edge**) malloc((net->v_num-1)*sizeof(Edge *));
	p=selectVlist;
	for(i=0;i<net->v_num;i++){
		*p++=0;
	}
	p=net->enum_list;
	q=net->elist;
	s=edgelist;
	for(i=0;i<net->v_num;i++){
		r=*q++;
		for(j=0;j<*p;j++){
			*s++=r++;
		}
		p++;
	}
	Heap<Edge> heap(net->e_num,net->e_num,edgelist,[](Edge *e)->double {return e->w;});
	//
	i=1;
	q=output;
	while(i<net->v_num){
		r=heap.pull();
		if(selectVlist[r->from]==1&&selectVlist[r->to]==1){
			continue;
		}
		selectVlist[r->from]=1;
		selectVlist[r->to]=1;
		*q++=r;
		i++;
	}
	free(selectVlist);
	return output;
}

int main(int argc,char* argv[]){
	if(argc!=2){
		cout<<"Error:This command needs csv-filename"<<endl;
		exit(1);
	}
	Network n;
	n.load(argv[1]);
	n.print();
	Edge **outcome=Kruskal(&n);
	int i=0;
	Edge **e=outcome;
	for(i<0;i<n.v_num-1;i++){
		cout<<(*e)->from<<"->"<<(*e)->to<<" w="<<(*e)->w<<endl;
		e++;
	}
	return 0;
}