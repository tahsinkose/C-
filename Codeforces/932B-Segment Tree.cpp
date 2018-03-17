#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <map>

using namespace std;
using  ns = chrono::nanoseconds;
using get_time = chrono::steady_clock ;

#define LEFT(i) (i<<1) + 1
#define RIGHT(i) (i<<1) + 2
//Childrens are at 2*i+1 and 2*i+2  
using namespace std;
int getMid(int s, int e) {  return s + (e -s)/2;  }
// Recursively builds the segment tree.
int build(vector<int>& arr,vector<int>& st,int ss,int se,int si,int k){
	if(ss==se){
		st[si] = (arr[ss] == k ? 1:0);
		return st[si];
	}
	int mid = getMid(ss,se);
	st[si] = build(arr,st,ss,mid,LEFT(si),k) + build(arr,st,mid+1,se,RIGHT(si),k);
	return st[si];
}

// Current_node_index in segment tree. Represented by css - cse
int query(vector<int>& st,int css,int cse,int qss,int qse,int si){
	
	if(qss <= css && qse >= cse)
		return st[si];
	if(cse < qss || qse < css)
		return 0;
	int mid = getMid(css,cse);
	return query(st,css,mid,qss,qse,LEFT(si))
		+ query(st,mid+1,cse,qss,qse,RIGHT(si));
}

int f(int n){
	int result = 1;
	while(n){
		if(n%10)
			result *= n%10;
		n/=10;
	}
	return result;
}
int g(int n){
	if(n<10)
		return n;
	else{
		int prod = f(n);
		return g(prod);
	}
}
int main(){
	auto start = get_time::now();
	int q;
	cin >> q;
	int n=1000000;
	vector<int> arr(n+1);
	int height = (int)(ceil(log2(n))); 
	int max_size = 2*(int)pow(2,height) - 1;
	for(int i=1;i<=n;i++){
		arr[i] = g(i);
	}
	vector<vector<int> > st(9,vector<int>(max_size));//Segment tree for each k
	for(int i=0;i<9;i++)
		build(arr,st[i],1,n,0,i+1);//build the segment tree.
	
	for(int i=0;i<q;i++){
		int l,r,k;
		cin>>l>>r>>k;
		cout<<query(st[k-1],1,n,l,r,0)<<endl;
	}
	auto end = get_time::now();
	auto differ = end - start;
	//cout<<"Elapsed time is :  "<< chrono::duration_cast<ns>(differ).count()<<" ns "<<endl;
	return 0;
}