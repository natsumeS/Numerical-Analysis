#include <iostream>
#include <fstream>
using namespace std;

/*
argument
1:ファイル名
*/
void createNetwork(char* filename){
	int v_num,i,j,to,e_num;
	double w;
	//入力
	ofstream ofs(filename);
	if(!ofs){
		cout<<"Error:file error!"<<endl;
		exit(1);
	}
	cout<<"fill out:(Vertex num)"<<endl;
	cin>>v_num;
	ofs<<"v_num,"<<v_num<<endl;
	cout<<"v_num="<<v_num<<endl;
	for(i=0;i<v_num;i++){
		cout<<"----vid="<<i<<"----"<<endl;
		cout<<"fill out:(edge num)"<<endl;
		cin>>e_num;
		cout<<"e_num="<<e_num<<endl;
		ofs<<"e_num,"<<e_num<<endl;
		cout<<"fill out Edge info:(to vid) (weight), (to vid)=-1 -> end"<<endl;
		for(j=0;j<e_num;j++){
			cout<<"->";
			cin>>to>>w;
			ofs<<to<<","<<w<<endl;
		}
	}
}
int main(int argc,char* argv[]){
	if(argc!=2){
		cout<<"Error:This command needs csv-filename"<<endl;
		exit(1);
	}
	createNetwork(argv[1]);
	return 0;


}