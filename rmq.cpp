#include <iostream>
#include <vector>
#include <climits>
#define getMin(a,b) a<b?a:b 
using namespace std;

class SegmentTree{
	private:
		vector<int> tree;
		int constructSegmentTree(vector<int>& arr,int start, int end, int index);
		int RMQUtil(int index,int segment_start, int segment_end, int update_start, int update_end);
	public:
		SegmentTree(vector<int>& arr){
			int n = arr.size();
			tree.resize(4*n);
			constructSegmentTree(arr,0,n-1,0);
		}
		int RMQ(int n,int start, int end);
};

int SegmentTree::constructSegmentTree(vector<int>& arr,int start,int end,int index){
	
	if(start == end){
		tree[index] = arr[start];
		return tree[index];
	}

	int mid = (start + end) / 2;
	
	tree[index] = getMin(constructSegmentTree(arr,start,mid,2*index+1),
						  constructSegmentTree(arr,mid+1,end,2*index+2));
	return tree[index];
}	





int SegmentTree::RMQUtil(int index,int segment_start, int segment_end, int query_start, int query_end){
	if(segment_start > query_end || segment_end < query_start)
		return INT_MAX;

	if(query_start <= segment_start && query_end >= segment_end)
		return tree[index];

	int mid = (segment_start + segment_end) / 2;
	return getMin(RMQUtil(2*index + 1,segment_start, mid, query_start, query_end),
				  RMQUtil(2*index + 2,mid+1, segment_end, query_start, query_end));

}

int SegmentTree::RMQ(int n,int start, int end){
	return RMQUtil(0,0,n-1,start,end);
}



int main(){
	int n;
	cin>>n;
	vector<int> arr(n);
	for(int i=0;i<n;i++)
		cin>>arr[i];
	SegmentTree* st = new SegmentTree(arr);
	cout<<"Minimum of values in range : "<<st->RMQ(n,2,5)<<endl;
	delete st;
}