#include <iostream>
#include <climits>
#include <vector>
#include <chrono>
#include <cstdlib>

#define parent(i) i>>1
#define left(i) i<<1
#define right(i) (i<<1) + 1
using namespace std;
using  ns = chrono::nanoseconds;
using get_time = chrono::steady_clock ;

void swap(int *x,int *y);
class MinHeap
{
	int *harr;
	int capacity;
	int heap_size;
public:
	MinHeap(int capacity);
	MinHeap(vector<int>& v);
	void MinHeapify(int );
	int extractMin();
	void decreaseKey(int i,int new_val);
	int getMin(){ return harr[0];}
	void deleteKey(int i);
	void insertKey(int k);
	void printHeap();
};

MinHeap::MinHeap(int n){
	harr = new int[n];
	heap_size=0;
	capacity = n;
}


MinHeap::MinHeap(vector<int> &v){
	harr = new int[v.size()];
	heap_size = 0;
	capacity = v.size();
	for(int i=0;i<v.size();i++)
		insertKey(v[i]);
}
void MinHeap::insertKey(int k){
	if(heap_size==capacity){
		cout<<"Overflow: Could not insert key"<<endl;
		return;
	}

	heap_size++;
	int i=heap_size - 1;
	harr[i]=k;

	while(i!=0 && harr[parent(i)] > harr[i]){
		swap(&harr[i],&harr[parent(i)]);
		i=parent(i);
	}
}

void MinHeap::decreaseKey(int i,int new_val){
	harr[i]=new_val;
	while(i != 0 && harr[parent(i)] > harr[i]){
		swap(&harr[i],&harr[parent(i)]);
		i = parent(i);
	}
}

int MinHeap::extractMin(){
	if(heap_size <= 0)
		return INT_MAX;
	if(heap_size==1){
		heap_size--;
		return harr[0];
	}

	// Store the min value, and remove it from heap
	int root = harr[0];
	harr[0] = harr[heap_size-1];
	heap_size--;
	MinHeapify(0);
	return root;
}


void MinHeap::deleteKey(int i){
	decreaseKey(i,INT_MIN); //Value reduced to minus infinite
	extractMin();
}

void MinHeap::MinHeapify(int i){
	int l=left(i);
	int r=right(i);
	int smallest = i;
	if(l < heap_size && harr[l] < harr[i])
		smallest = l;
	if(r < heap_size && harr[r] < harr[smallest])
		smallest = r;
	if(smallest != i){
		swap(&harr[i],&harr[smallest]);
		MinHeapify(smallest);
	}
}
void swap(int *x,int *y){
	int temp=*x;
	*x=*y;
	*y=temp;
}

void MinHeap::printHeap(){
	for(int i=0;i<heap_size;i++)
		cout<<"["<<harr[i]<<"]";
	cout<<endl;
}

int main(){
	auto start = get_time::now(); 
	int n;
	cin>>n;
	srand(time(NULL));
	vector<int> v(n);
	for(int i=0;i<n;i++){
		int val = rand() % 100;
		v[i] = val;
	}	
	MinHeap heap(v);
	//heap.printHeap();
	for(int i=0;i<n;i++)
		cout<<heap.extractMin()<<" ";
	cout<<endl;
	
	auto end = get_time::now();
	auto differ = end - start;
	cout<<"Elapsed time is :  "<< chrono::duration_cast<ns>(differ).count()<<" ns "<<endl;
	return 0;

}
