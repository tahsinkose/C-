#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <queue>
#include <chrono>

using namespace std;
using  ns = chrono::nanoseconds;
using get_time = chrono::steady_clock ;

typedef unsigned long long int ull;

ull constructST_sum(vector<int>& arr,int start_segment,int end_segment,vector<ull>& st,int segment_index){
	//cout<<"In ("<<start_segment<<","<<end_segment<<") range with index: "<<segment_index<<endl;
	if(start_segment==end_segment){
		st[segment_index] = arr[start_segment];
		return st[segment_index];
	}
	int mid = start_segment + (end_segment - start_segment)/2; // To prevent possible overflows.
	st[segment_index] = constructST_sum(arr,start_segment,mid,st,2*segment_index+1) + 
						constructST_sum(arr,mid+1,end_segment,st,2*segment_index+2);
	return st[segment_index];
}


ull getSum(vector<ull>& st,int start_segment,int end_segment,int start_query,int end_query,int segment_index){
	if(start_query<=start_segment && end_query>=end_segment)
		return st[segment_index];
	if(start_query > end_segment || end_query < start_segment)
		return 0;
	//cout<<"ss: "<<start_segment<<", se: "<<end_segment<<", qs: "<<start_query<<", qe: "<<end_query<<endl;
	int mid = start_segment + (end_segment - start_segment)/2; // To prevent possible overflows.
	//cout<<"mid: "<<mid<<endl;
	return getSum(st,start_segment,mid,start_query,end_query,2*segment_index+1) +
			getSum(st,mid+1,end_segment,start_query,end_query,2*segment_index+2);
}


void updateRange(vector<ull>& st,int start_segment,int end_segment,int start_query,int end_query,int segment_index,int op,int x){
	if(start_query > end_segment || end_query < start_segment)
		return ;
	if(start_segment == end_segment){
		if(op)
			st[segment_index] |= (1<<(x-1));
		else
			st[segment_index] &= ~(1<<(x-1));
		return ;
	}
	cout<<"At range ["<<start_segment<<"-"<<end_segment<<"] "<<endl;
	int mid = start_segment + (end_segment - start_segment)/2; // To prevent possible overflows.
	updateRange(st,start_segment,mid,start_query,end_query,2*segment_index+1,op,x);
	updateRange(st,mid+1,end_segment,start_query,end_query,2*segment_index+2,op,x);

	st[segment_index] = st[2*segment_index+1] + st[2*segment_index+2];
}


int main(){
	auto start = get_time::now();
	int n,q;
	cin>>n;//size of array
	vector<int> arr(n,0);	
	for(int i=0;i<n;i++)
		cin>>arr[i];
	cin>>q;
	int height = (int)(ceil(log2(n)));
	int max_size = 2*(int)pow(2,height) - 1; // 2* 2^(height) - 1
	vector<ull> segment_tree(max_size,0);
	constructST_sum(arr,0,n-1,segment_tree,0); // Construct segment tree starting with the range [0..n-1]
	for(int i=0;i<q;i++){
		int comm,l,r,x;
		cin>>comm;
		if(comm==1){
			cin>>l>>r;
			cout<<getSum(segment_tree,0,n-1,l-1,r-1,0)<<endl;
		}
		else if(comm==2){
			cin>>l>>r>>x;
			updateRange(segment_tree,0,n-1,l-1,r-1,0,1,x);
		}
		else{
			cin>>l>>r>>x;
			updateRange(segment_tree,0,n-1,l-1,r-1,0,0,x);
		}
	}
	auto end = get_time::now();
	auto differ = end - start;
	cout<<"Elapsed time is :  "<< chrono::duration_cast<ns>(differ).count()<<" ns "<<endl;	
	return 0;
}
