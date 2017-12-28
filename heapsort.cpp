#include <iostream>
#include <vector>
#include <cmath>

#define PARENT(i) i>>1
#define LEFT(i) i<<1
#define RIGHT(i) (i<<1) + 1
int heap_size;
using namespace std;

ostream& operator<<(ostream& o,vector<int>& A){
	for(int i=0;i<A.size();i++)
		o<<A[i]<<" ";

	return o;
}
void MaxHeapify(vector<int>& arr,int i){
	
	int largest = i;
	while(i<heap_size){
		int l=LEFT(i);
		int r=RIGHT(i);
		if(l>=heap_size)
			break;
		if(l<heap_size && arr[l] > arr[i])
			largest = l;
		if(r<heap_size && arr[r] > arr[largest])
			largest = r;
		if(largest!=i){
			swap(arr[largest],arr[i]);
			i = largest;
		}
		else
			break;
	}

}
void build_max_heap(vector<int>& arr){
	int n = arr.size();
	for(int i=n/2;i>=0;i--)
		MaxHeapify(arr,i);
}
int main(){
	int n;
	cin>>n;
	heap_size = n;
	vector<int> v(n);
	for(int i=0;i<n;i++)
		cin>>v[i];
	
	build_max_heap(v);
	for(int i=n-1;i>=1;i--){
		swap(v[i],v[0]);
		heap_size--;
		MaxHeapify(v,0);
	}
    cout<<v<<endl;
	return 0;
}
	
