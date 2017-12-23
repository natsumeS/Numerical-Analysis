template <class T>
class Heap{
public:
	T **heap;
	int heapsize;
	int size;
	double (*vfunc)(T*);
	void downheap(int size,int parentid,T **parent);
	void makeHeap();
	void sort();
	T* pull();
	void push(T *t);
	Heap(int heapsize,int size,T **heap,double (*vfunc)(T*));
};
template <class T> Heap<T>::Heap(int heapsize,int size,T**heap,double(*vfunc)(T*)){
	this->heapsize=heapsize;
	this->size=size;
	this->heap=heap;
	this->vfunc=vfunc;
	makeHeap();
}
template <class T> void Heap<T>::downheap(int size,int parentid,T **parent){
	T **child;
	int minindex=2*parentid+1;
	if(minindex>=size){
		return;
	}
	child=parent+parentid+1;
	double a,min=vfunc(*child);
	if(minindex+1<size&&min>(a=vfunc(*(child+1)))){
		minindex++;
		child++;
		min=a;
	}
	if(vfunc(*parent)>min){
		T *t=*parent;
		*parent=*child;
		*child=t;
		downheap(size,minindex,child);
	}
}
template <class T> void Heap<T>::makeHeap(){
	int i;
	for(i=(size-2)/2;i>=0;i--){
		downheap(size,i,heap+i);
	}
}
template <class T> void Heap<T>::sort(){
	int i;
	T **p,*q,**r;
	makeHeap();
	p=heap+size-1;
	for(i=size-1;i>0;i--){
		q=*heap;
		*heap=*p;
		*p--=q;
		r=heap;
		downheap(i,0,r);
	}
}
template <class T> T* Heap<T>::pull(){
	T **p,*q;
	p=heap+size-1;
	q=*heap;
	*heap=*p;
	*p--=q;
	size--;
	downheap(size,0,heap);
	return q;
}

