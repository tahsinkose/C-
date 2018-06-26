#include <iostream>
#include <vector>


using namespace std;
typedef unsigned long long int ull;
class SegmentNode{
	private:
		int from,to;
		ull value,lazy;
		SegmentNode* left, *right;
		void extend();	
	public:
		SegmentNode(){
			from = 1;
			to = 1e5;
			value = 0;
			lazy = 0;
			left = NULL;
			right = NULL;
		}
		SegmentNode(int f,int t) : from(f), to(t) {
			value = 0;
			lazy = 0;
			left =NULL;
			right = NULL;
		};
		~SegmentNode(){
			delete left;
			delete right;
		}
		ull getVal(){return value;}
		void addLazy(ull l){lazy += l;}
		ull getSum(int start, int end);
		void updateRange(int start, int end, int val);
};

void SegmentNode::extend(){
	if(left==NULL){
		left = new SegmentNode(from,(from+to)/2);
		right = new SegmentNode((from+to)/2 + 1,to);
	}
}	

ull SegmentNode::getSum(int start, int end){
	if(from>to || from>end || to<start) return 0;
	if(lazy){
		value += (to-from+1)*lazy;
		extend();
		left->addLazy(lazy);
		right->addLazy(lazy);
		lazy = 0;
	}
	if(from>=start && to<=end) return value;
	extend();
	return left->getSum(start,end) + right->getSum(start,end);
}


void SegmentNode::updateRange(int start, int end, int val){
	if(lazy){
		value += (to-from+1)*lazy;
		if(from!=to){
			extend();
			left->addLazy(lazy);
			right->addLazy(lazy);
		}
		lazy = 0;
	}
	if(from>to || from>end || to<start)
		return;
	if(from>=start && to<=end){
		value+=(to-from+1)*val;
		if(from!=to){
			extend();
			left->addLazy(val);
			right->addLazy(val);
		} 
		return;
	}

	extend();
	left->updateRange(start,end,val);
	right->updateRange(start,end,val);

	value = left->getVal() + right->getVal(); 
}



int main(){
	int t;
	cin>>t;
	for(int i=0;i<t;i++){
		SegmentNode* root = new SegmentNode();
		int l,r,v;
		cin>>l>>r>>v;
		root->updateRange(l,r,v);
		cout<<"Sum of values in range : "<<root->getSum(1,11)<<endl;
		delete root;	
	}
	return 0;
}