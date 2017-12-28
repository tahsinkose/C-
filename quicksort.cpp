#include <iostream>
#include <vector>
#include <map>
#include <climits>
#include <chrono>

using namespace std;
using ns=chrono::nanoseconds;
using get_time=chrono::steady_clock;

ostream& operator<<(ostream& o,vector<int>& A){
	for(int i=0;i<A.size();i++)
		o<<A[i]<<" ";
	return o;
}
int e_partition(vector<int>& A,int low,int high){
	int pivot = A[high];
	int i=low-1;
	for(int j=low;j<high;j++){
		if(A[j]<=pivot){
			i++;
			swap(A[i],A[j]);
		}
	}
	swap(A[i+1],A[high]);
	return i+1;
}

int b_partition(vector<int>& A,int low,int high){
	int pivot = A[low];
	int i=low+1;
	for(int j=low+1;j<=high;j++){
		if(A[j]<=pivot){
			swap(A[i],A[j]);
			i++;
		}
	}
	A[low] = A[i-1];
	A[i-1] = pivot;
	return i-1;
}
void quicksort(vector<int>& A,int low,int high){
	if(low<high){
		int q=e_partition(A,low,high);
		quicksort(A,low,q-1);
		quicksort(A,q+1,high);
	}
}

int main(){
	int n;
	cin>>n;
	vector<int> arr(n);
	map<int,int> indices;
	for(int i=0;i<n;i++){
		cin>>arr[i];
		indices[arr[i]]=i;
	}
	map<int,int> indices1 = indices;
	map<int,int> indices2 = indices;
	vector<int> sorted_arr = arr;
	vector<int> arr2 = arr;

	auto start = get_time::now();
	quicksort(sorted_arr,0,n-1);
	int swaps = 0;
	for(int i=0;i<n;i++){
		int cv = arr[i];
		int scv = sorted_arr[i];
		if(scv != cv){
			
			swaps++;
			int csv = indices1[scv];
			swap(arr[i],arr[csv]);
			indices1[cv] = csv;
		}
	}
	
	
	
	int reverse_swaps = 0;
	for(int i=0;i<n;i++){
		int cv=arr2[i];
		int scv =sorted_arr[n-i-1];
		if(scv!= cv){
			reverse_swaps++;
			int csv = indices2[scv];
			swap(arr2[i],arr[csv]);
			indices2[cv] = indices2[scv];
		}
	}
	cout<<"swaps: "<<swaps<<", r_swaps: "<<reverse_swaps<<endl;
	cout<<((reverse_swaps < swaps) ? reverse_swaps : swaps)<<endl;
	
	auto end = get_time::now();
	auto differ = end - start;
	cout<<"Elapsed time is :  "<< chrono::duration_cast<ns>(differ).count()<<" ns "<<endl;
	return 0;
}


