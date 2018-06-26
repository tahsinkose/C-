#include <iostream>
#include <vector>


using namespace std;

class SegmentTree{
	private:
		vector<int> tree;
		void constructSegmentTree(vector<int>& arr,int start, int end, int index);
		int sumUtil(int segment_start,int segment_end,int query_start, int query_end, int index);	
		void rangeUtil(int index,int segment_start, int segment_end, int update_start, int update_end,int diff);
	public:
		SegmentTree(vector<int>& arr){
			int n = arr.size();
			tree.resize(4*n);
			constructSegmentTree(arr,0,n-1,0);
		}
		int getSum(int n, int start, int end);
		void updateRange(int n,int start, int end, int diff);
};

void SegmentTree::constructSegmentTree(vector<int>& arr,int start,int end,int index){
	if(start > end)
		return ;

	if(start == end){
		tree[index] = arr[start];
		return ;
	}

	int mid = (start + end) / 2;
	constructSegmentTree(arr,start,mid,2*index + 1);
	constructSegmentTree(arr,mid+1,end,2*index + 2);

	tree[index] = tree[2*index + 1] + tree[2*index + 2];
}	

int SegmentTree::getSum(int n, int start, int end){
	return sumUtil(0,n-1,start,end,0);
}

int SegmentTree::sumUtil(int segment_start,int segment_end,int query_start, int query_end, int index){
	if(query_start <= segment_start && query_end >= segment_end)
		return tree[index];

	if(segment_end < query_start || segment_start > query_end)
		return 0;

	int mid = segment_start + (segment_end - segment_start)/2;
	return sumUtil(segment_start,mid,query_start,query_end,2*index + 1) + 
		   sumUtil(mid+1,segment_end,query_start,query_end,2*index + 2);
}



void SegmentTree::rangeUtil(int index,int segment_start, int segment_end, int update_start, int update_end,int diff){
	if(segment_start>segment_end || segment_start > update_end || segment_end < update_start)
		return;

	if(segment_start==segment_end){
		tree[index] += diff;
		return;
	}

	int mid = (segment_start + segment_end) / 2;
	rangeUtil(2*index + 1, segment_start, mid, update_start, update_end,diff);
	rangeUtil(2*index + 2, mid+1,segment_end, update_start,update_end,diff);

	tree[index] = tree[2*index + 1] + tree[2*index + 2];

}

void SegmentTree::updateRange(int n,int start, int end, int diff){
	rangeUtil(0,0,n-1,start,end,diff);
}



int main(){
	int n;
	cin>>n;
	vector<int> arr(n);
	for(int i=0;i<n;i++)
		cin>>arr[i];
	SegmentTree* st = new SegmentTree(arr);
	cout<<"Sum of values in range : "<<st->getSum(n,2,5)<<endl;
	st->updateRange(n,2,5,6);
	cout<<"Updated sum of values in range : "<<st->getSum(n,2,5)<<endl;
	delete st;
}