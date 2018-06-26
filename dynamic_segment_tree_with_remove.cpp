#include <iostream>
#include <chrono>
#include <tuple>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>


using namespace __gnu_pbds;
using namespace std;
using ns=chrono::nanoseconds;
using get_time=chrono::steady_clock;

typedef unsigned long long int ull;
typedef tree<tuple<int,int,int>,null_type,less<tuple<int,int,int> >,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
class SegmentNode{
	private:
		int from,to;
		ull value,lazy;
		SegmentNode* left, *right;
		void extend();	
	public:
		SegmentNode(){
			from = 1;
			to = 1e9;
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
		void compress(int start,int end);
};

void SegmentNode::extend(){
	if(left==NULL){
		left = new SegmentNode(from,(from+to)/2);
		right = new SegmentNode((from+to)/2 + 1,to);
	}
}	

void SegmentNode::compress(int start,int end){
	if(from>=start && to<=end){
		if(left)
			delete left;
		if(right)
			delete right;
		left = NULL;
		right = NULL;
		return;
	}
	if(left)
		left->compress(start,end);
	if(right)
		right->compress(start,end);	
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
		ordered_set o_set;
		int m,k;
		cin>>m>>k;
		for(int j=0;j<m;j++){
			int l,r,v;
			cin>>l>>r>>v;
			root->updateRange(l,r,v);
			o_set.insert(make_tuple(l,r,v));
		}
		ull max = 0;
		auto start = get_time::now();
		for(int j=0;j<=m;j++){
			auto itr = o_set.find_by_order(j);
			int begin = get<0>(*itr);
			int end = get<1>(*itr);
			ull prev = 0;
			int z=begin;
			for(;z<=end;z++){
				int above_limit = min(z+k-1,(int)1e9);
				ull sum = root->getSum(z,above_limit);
				//cout<<"At "<<z<<", sum: "<<sum<<endl;
				if(sum>max) max = sum;
				if(sum>prev) prev = sum;
				else break;
			}
			if(z<end){
				int tmp = z;
				z = end;
				
				prev = 0;
				for(;z>tmp;z--){
					int above_limit = min(z+k-1,(int)1e9);
					ull sum = root->getSum(z,above_limit);
					//cout<<"At "<<z<<", sum: "<<sum<<endl;
					if(sum>max) max = sum;
					if(sum>prev) prev = sum;
					else break;		
				}
			}
			root->compress(begin,end);
		}
		auto end = get_time::now();
		auto differ = end - start;
		cout<<"Elapsed time is :  "<< chrono::duration_cast<ns>(differ).count()<<" ns "<<endl;
	
		cout<<max<<endl;
		delete root;	
	}
	return 0;
}