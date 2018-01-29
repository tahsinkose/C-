#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <set>
#include <numeric>
#include <map>

using namespace std;
using  ns = chrono::nanoseconds;
using get_time = chrono::steady_clock ;

typedef  long long int ll;

template < class T >
std::ostream& operator << (ostream& os, const vector<T>& v) 
{
    os << "[";
    for (typename vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << " " << *ii;
    }
    os << "]";
    return os;
}


map<pair<int,int>, ll> memos;

ll max_element( vector<ll>& arr, int start, int end){
	if (start > end)
		return 0;
	if(start+1==end){
		ll val = max(arr[start],arr[end]);
		memos[{start,end}] = val;
		return val;
	}
	if(start == end){
		memos[{start,end}] =  arr[start];
		return arr[start];
	}
	ll al,ah,bl,bh;
	if(memos.find({start+2,end})!=memos.end())
		al = memos[{start+2,end}];
	else{
		if(start+2>end)
			al = 0;
		else
			al = max_element( arr,start+2,end);
	}

	if(memos.find({start+1,end-1})!=memos.end())
		ah = memos[{start+1,end-1}];
	else{
		if(start+1>end-1)
			ah = 0;
		else
			ah = max_element(arr,start+1,end-1);
	}
	bl = ah;

	if(memos.find({start,end-2})!=memos.end())
		bh = memos[{start,end-2}];
	else{
		if(start>end-2)
			bh = 0;
		else
			bh = max_element( arr,start,end-2);
	}
	ll a = min(al,ah);
	ll b = min(bl,bh);
	
	ll val = max(a,b);
	memos[{start,end}] = val;
	return val;
}


ll dp_max_element(vector<ll>& arr,int N){

	vector<vector<ll> > dp(N+1,vector<ll>(N+1,0));
	for(int i=0;i<=N;i++){
		dp[i][i] = arr[i]; //Only diagonal parts should have non-zero value, at the beginning.
		if(i>0 && i<N)
			dp[i][i+1] = max(arr[i],arr[i+1]);
	}
	// Since dp is a map and we will use DP, memory requirement reduced hugely.
	for(int stride=2;stride<=N;stride++){
		for(int i=0;i<=N/2;i++){
			int j=i+stride;
			if(j<=N){
				ll val = dp[i+1][j-1];
				dp[i][j] = max(min(dp[i+2][j],val) , min(val, dp[i][j-2]));
			}
			j++;
			if(j<=N){
				ll val = dp[i+1][j-1];
				dp[i][j] = max(min(dp[i+2][j],val) , min(val, dp[i][j-2]));
			}
		}
	}
	return dp[0][N];
} 
int main(){
	auto start = get_time::now();
	int N;
	cin>>N;
	vector<ll> arr(N);
	for(int i=0;i<N;i++)
		cin>>arr[i];
	//cout<<dp_max_element(arr,N-1)<<endl;
	if(N%2)//Odd element
		cout<<arr[N/2]<<endl;
	else
		cout<<max(arr[N/2],arr[N/2-1])<<endl;
	auto end = get_time::now();
	auto differ = end - start;
	//cout<<"Elapsed time is :  "<< chrono::duration_cast<ns>(differ).count()<<" ns "<<endl;
	
	return 0;
}
