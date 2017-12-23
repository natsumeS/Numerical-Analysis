#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

typedef struct{
	int from;
	int to;
	double w;
} Edge;
class Network{
public:
	int v_num;
	int e_num;
	int *enum_list;
	Edge **elist;
	void load(string filename);
	void print();
};
void Network::load(string filename){
	ifstream ifs(filename);
	if(!ifs){
		cout<<"file open error!"<<endl;
		exit(1);
	}
	string str,token;
	int eflag,e_num,wflag;
	int *p,vid;
	Edge **q;
	Edge *r;
	//
	getline(ifs,str);
	istringstream stream(str);
	getline(stream,token,',');
	if(token!="v_num"){
		cout<<"error:csv is invalid format";
		exit(1);
	}
	getline(stream,token,',');
	v_num=stoi(token);
	e_num=0;
	enum_list=new int[v_num];
	elist=(Edge**)malloc(v_num*sizeof(Edge*));
	p=enum_list;
	q=elist;
	vid=0;
	//
	while(getline(ifs,str)){
		istringstream stream(str);
		eflag=0;
		wflag=0;
		while(getline(stream,token,',')){
			if(token=="e_num"){
				eflag=1;
				continue;
			}else if(eflag){
				e_num=stoi(token);
				*p++=e_num;
				*q=(Edge*)malloc(e_num*sizeof(Edge));
				r=*q++;
				break;
			}else if(wflag){
				(r++)->w=stof(token);
				e_num++;
				vid++;
				break;
			}
			r->from=vid;
			r->to=stoi(token);
			wflag=1;
		}
	}
}
void Network::print(){
	int i,j,*p;
	Edge **q,*r;
	p=enum_list;
	q=elist;
	cout<<"---network---"<<endl;
	cout<<"v_num="<<v_num<<endl;
	cout<<"e_num="<<e_num<<endl;
	for(i=0;i<v_num;i++){
		cout<<"from "<<i<<endl;
		r=*q++;
		for(j=0;j<*p;j++){
			cout<<"to "<<r->to<<"("<<r->w<<")"<<endl;
			r++;
		}
		p++;
	}
}
Edge *Kruskal(Network *net){


}



int main(void){
	Network n;
	n.load("p.csv");
	n.print();
	return 0;
}