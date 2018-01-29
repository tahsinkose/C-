/* This source code solves a special type of Segment Tree + Lazy Propagation problem. For further information refer prob-Cab.pdf. Briefly, it is asked to apply bit manipulation operations in a given range and keep the array up-to-date in order to response to query operations appropriately. 

 The solution exploits the given information in the problem text. Since the bit numbers cannot exceed 20, we can store a distinct segment tree for each bit count. In order to keep things consistent, a simple struct is created and applied bit operation is recorded in a FIFO manner. At each pending update , whether in getSum or updateRange, the propagation only applies to 1 level deeper. At those propagations, first pop the latest bit operation from applied bit queue of current node and then regulate the applied bit queue of left and right children by pushing current bit op. */


#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <chrono>
#include <queue>

using namespace std;
using  ns = chrono::nanoseconds;
using get_time = chrono::steady_clock ;


typedef unsigned long long int ull;
struct lazy_node{
	int val;
	queue<int> bit;
	queue<int> ops;
} ;



ull constructST_sum(vector<int>& arr,int start_segment,int end_segment,vector<ull>& st,vector<vector<ull> >& bct,int segment_index){

	if(start_segment==end_segment){
		st[segment_index] = arr[start_segment];
		for(int i=0;i<20;i++)
			bct[i][segment_index] = (arr[start_segment] & (1<<i) ? 1 : 0);

		return st[segment_index];
	}
	int mid = start_segment + (end_segment - start_segment)/2; // To prevent possible overflows.
	st[segment_index] = constructST_sum(arr,start_segment,mid,st,bct,2*segment_index+1) + 
						constructST_sum(arr,mid+1,end_segment,st,bct,2*segment_index+2);
	for(int i=0;i<20;i++)
		bct[i][segment_index] = bct[i][2*segment_index+1] + bct[i][2*segment_index+2];

	return st[segment_index];
}

void apply_pending_update(vector<ull>& st,vector<vector<ull> >& bct,vector<lazy_node>& lazy,int start_segment,int end_segment,int segment_index){

	if(lazy[segment_index].val!=0){//Apply pending updates in the lazy segment tree.
		st[segment_index] += lazy[segment_index].val;
		if(start_segment!=end_segment){
			int left_child = 2*segment_index+1;
			int right_child = 2*segment_index+2;
			while(!lazy[segment_index].bit.empty()){
				int x = lazy[segment_index].bit.front();
				lazy[segment_index].bit.pop();
				int op = lazy[segment_index].ops.front();
				lazy[segment_index].ops.pop();
				if(!op){
					lazy[left_child].val -= bct[x-1][left_child]*(1<<(x-1));
				
					lazy[right_child].val -= bct[x-1][right_child]*(1<<(x-1));
					bct[x-1][left_child] = 0;
					bct[x-1][right_child] = 0;
				}
				else{
					int mid = start_segment + (end_segment - start_segment)/2; // To prevent possible overflows.
					int left_range = mid-start_segment+1;
					int right_range = end_segment - mid;
					lazy[left_child].val += (left_range - bct[x-1][left_child])*(1<<(x-1));
					bct[x-1][left_child] = left_range;
					lazy[right_child].val += (right_range - bct[x-1][right_child])*(1<<(x-1));
					bct[x-1][right_child] = right_range;
				}
				lazy[left_child].bit.push(x);
				lazy[right_child].bit.push(x);

				lazy[left_child].ops.push(op);
				lazy[right_child].ops.push(op);
			}
		}
		lazy[segment_index].val = 0;
	}
}

ull getSum(vector<ull>& st,vector<vector<ull> >& bct,vector<lazy_node>& lazy,int start_segment,int end_segment,int start_query,int end_query,int segment_index){
	apply_pending_update(st,bct,lazy,start_segment,end_segment,segment_index);

	if(start_query <= start_segment && end_query >= end_segment)
		return st[segment_index];
	if(start_query > end_segment || end_query < start_segment)
		return 0;
	int mid = start_segment + (end_segment - start_segment)/2; // To prevent possible overflows.

	return getSum(st,bct,lazy,start_segment,mid,start_query,end_query,2*segment_index+1) +
			getSum(st,bct,lazy,mid+1,end_segment,start_query,end_query,2*segment_index+2);
}



void updateRange(vector<ull>& st,vector<vector<ull> >& bct,vector<lazy_node>& lazy,int start_segment,int end_segment,int start_query,int end_query,int segment_index,int op,int x){
	
	apply_pending_update(st,bct,lazy,start_segment,end_segment,segment_index);
	if(start_segment > end_segment || start_query > end_segment || end_query < start_segment)
		return ;
	if(start_segment >= start_query && end_segment <=end_query){
		
		if(!op){
			st[segment_index] -= bct[x-1][segment_index]*(1<<(x-1));
			bct[x-1][segment_index] = 0;
			if(start_segment!=end_segment){//Check whether it is leaf node.
				int mid = start_segment + (end_segment - start_segment)/2; // To prevent possible overflows.
				int left_child = 2*segment_index+1;
				int right_child = 2*segment_index+2;
				lazy[left_child].val -=bct[x-1][left_child]*(1<<(x-1));
				lazy[right_child].val -=bct[x-1][right_child]*(1<<(x-1));
				bct[x-1][left_child] = 0;
				bct[x-1][right_child] = 0;

				lazy[left_child].bit.push(x);
				lazy[right_child].bit.push(x);

				lazy[left_child].ops.push(op);
				lazy[right_child].ops.push(op);
			}
		}
		else{
			int range = end_segment - start_segment + 1;
			st[segment_index] += (range-bct[x-1][segment_index]) * (1<<(x-1));
			bct[x-1][segment_index] = range;
			if(start_segment!=end_segment){//Check whether it is leaf node
				int mid = start_segment + (end_segment - start_segment)/2; // To prevent possible overflows.
				int left_child = 2*segment_index+1;
				int right_child = 2*segment_index+2;
				int left_range = mid-start_segment+1;
				int right_range = end_segment - mid;
				
				lazy[left_child].val += (left_range - bct[x-1][left_child])*(1<<(x-1));
				lazy[right_child].val += (right_range - bct[x-1][right_child])*(1<<(x-1));

				bct[x-1][left_child] = left_range;
				bct[x-1][right_child] = right_range;

				lazy[left_child].bit.push(x);
				lazy[right_child].bit.push(x);
				lazy[left_child].ops.push(op);
				lazy[right_child].ops.push(op);
			}

		}
		
		return ;
	}
	int mid = start_segment + (end_segment - start_segment)/2; // To prevent possible overflows.
	updateRange(st,bct,lazy,start_segment,mid,start_query,end_query,2*segment_index+1,op,x);
	updateRange(st,bct,lazy,mid+1,end_segment,start_query,end_query,2*segment_index+2,op,x);

	st[segment_index] = st[2*segment_index+1] + st[2*segment_index+2];
	for(int k=0;k<20;k++)
		bct[k][segment_index] = bct[k][2*segment_index+1] + bct[k][2*segment_index+2];
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
	vector<vector<ull> > bit_counts_tree(20,vector<ull>(max_size,0));
	vector<lazy_node> lazy_tree(max_size); //Used in lazy propagation.
	for(int i=0;i<max_size;i++)
		lazy_tree[i].val = 0;
	
	constructST_sum(arr,0,n-1,segment_tree,bit_counts_tree,0); // Construct segment tree starting with the range [0..n-1]
	for(int i=0;i<q;i++){
		int comm,l,r,x;
		cin>>comm;
		if(comm==1){
			cin>>l>>r;
			cout<<getSum(segment_tree,bit_counts_tree,lazy_tree,0,n-1,l-1,r-1,0)<<endl;
		}
		else if(comm==2){
			cin>>l>>r>>x;
			updateRange(segment_tree,bit_counts_tree,lazy_tree,0,n-1,l-1,r-1,0,1,x);
		}
		else{
			cin>>l>>r>>x;
			updateRange(segment_tree,bit_counts_tree,lazy_tree,0,n-1,l-1,r-1,0,0,x);
		}
	}
	auto end = get_time::now();
	auto differ = end - start;
	cout<<"Elapsed time is :  "<< chrono::duration_cast<ns>(differ).count()<<" ns "<<endl;
		
	return 0;
}
