#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class SegmentTree{
	private:
		vector<int> tree;
		void constructSegmentTree(vector<int>& arr,int start, int end, int index,int op);
		int array_size;
		void updateUtil(int index,int segment_start, int segment_end, int update_index,int value,int op);
	public:
		SegmentTree(vector<int>& arr){
			array_size = arr.size();
			tree.resize(4*array_size);
			int height = (int) (ceil(log2(array_size)));
			int op = (height%2==0 ? 0 : 1);
			constructSegmentTree(arr,0,array_size-1,0,op);
		}
		
		int gcd(int s,int e);
		int get(int index) const;
		void update(int index,int val);
};

void SegmentTree::constructSegmentTree(vector<int>& arr,int start,int end,int index,int op){
	if(start > end)
		return ;

	if(start == end){
		tree[index] = arr[start];
		return ;
	}

	int mid = (start + end) / 2;
	constructSegmentTree(arr,start,mid,2*index + 1,!op);
	constructSegmentTree(arr,mid+1,end,2*index + 2,!op);
	int val = gcd(tree[2*index + 1],tree[2*index + 2]);
	if(op)
		tree[index] = val;	
	else
		tree[index] = (tree[2*index + 1] * tree[2*index + 2]) / val;
}	



int SegmentTree::gcd(int a,int b){
	if(a==0 || b==0)
		return 0;
	while(a!=b){
		if(a>b)
			a -= b;
		else
			b -= a;
	}
	return a;
}

int SegmentTree::get(int index)const{
	if(index>=tree.size()){
		cout<<"Invalid index"<<endl;return -1;
	}
	else
		return tree[index];
}

void SegmentTree::update(int index,int val){
	if(index<0 || index > array_size-1){
		cout<<"Invalid index"<<endl; return;
	}

	int height = (int) (ceil(log2(array_size)));
	int op = (height%2==0 ? 0 : 1);

	updateUtil(0,0,array_size-1,index,val,op);

}
void SegmentTree::updateUtil(int index,int segment_start, int segment_end, int update_index,int value,int op){
	if(update_index < segment_start || update_index > segment_end)
		return;

	if(segment_start==segment_end && segment_start == update_index){
		tree[index] = value;
		return;
	}

	int mid = (segment_start + segment_end) / 2;
	updateUtil(2*index + 1, segment_start, mid, update_index,value,!op);
	updateUtil(2*index + 2, mid+1,segment_end, update_index,value,!op);

	int val = gcd(tree[2*index + 1],tree[2*index + 2]);
	if(op)
		tree[index] = val;	
	else
		tree[index] = (tree[2*index + 1] * tree[2*index + 2]) / val;

}

int main(){
	int n;
	cin>>n;
	vector<int> arr(n);
	for(int i=0;i<n;i++)
		cin>>arr[i];
	SegmentTree* st = new SegmentTree(arr);
	cout<<"Root value: "<<st->get(0)<<endl;
	st->update(2,7);
	cout<<"New root value: "<<st->get(0)<<endl;
	delete st;
}

