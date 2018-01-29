#include <iostream>
#include <map>
#include <vector>
#include <chrono>

#define mod 1000000007

using namespace std;
using  ns = chrono::nanoseconds;
using get_time = chrono::steady_clock ;

map<pair<int,int>, unsigned long long int> memos;

unsigned long long int trees(int nodes,int height){
	if((height==0 && nodes==0) ||(height==0 && nodes==1) || (height>0 && nodes==0)){
		memos[{height,nodes}] = 1;
		//cout<<"Returning 1 At ("<<height<<","<<nodes<<") "<<endl;
		return 1;
	}
	else if(height==0 && nodes>0){
		//cout<<"Returning 0 At ("<<height<<","<<nodes<<") "<<endl;
		memos[{height,nodes}] = 0;
		return 0;
	}

	
	unsigned long long int result = 0;
	for(int i=1;i<=nodes;i++){
		unsigned long long int val1,val2;
		if(memos.find({height-1,i-1})!=memos.end())
			val1 = memos[{height-1,i-1}] % mod;
		else{
			if((height-1>0 && i-1==0) || (height-1==0 && i-1==0) || (height-1==0 && i-1==1))
				val1=1;
			else if(height-1==0)
				val1=0;
			else
				val1 = trees(i-1,height-1) % mod;
		}
		if(memos.find({height-1,nodes-i})!=memos.end())
			val2 = memos[{height-1,nodes-i}] % mod;
		else{
			if((height-1>0 && nodes-i==0) || (height-1==0 && nodes-i==0)||(height-1==0 && nodes-i==1))
				val2=1;
			else if(height-1==0)
				val2=0;	
			else
				val2 = trees(nodes-i,height-1) % mod;
		}
		result += (val1 * val2) %mod;
		
	}
	memos[{height,nodes}] = result%mod;
	//cout<<"Returning ("<<height<<","<<nodes<<")"<<endl;
	return result;
}


void bottom_top_trees(vector<vector<long long int> >& dp,int N,int H){
	dp[0][0] = 1;
	dp[0][1] = 1;
	for(int i=0;i<=H;i++)
		dp[i][0] = 1;
	for(int i=2;i<=N;i++)
		dp[0][i] = 0;
	
	for(int i=1;i<=H;i++){
		for(int j=1;j<=N;j++){
			int limit = j/2;
			for(int k=0;k<limit;k++)
				dp[i][j] = (dp[i][j] + (2*dp[i-1][k]*dp[i-1][j-1-k])%mod)%mod;
			if(j%2)
				dp[i][j] = (dp[i][j] + (dp[i-1][limit]*dp[i-1][limit])%mod)%mod;
		}
	}

}

int main(){
	auto start = get_time::now();
	int N,A,B;
	cin>>N>>A>>B;
	vector<vector<long long int> > dp (B+1,vector<long long int>(N+1,0));
	bottom_top_trees(dp,N,B);
	int low_bound = A-2;
	if(A-2<0)
		low_bound = 0;
	long long int result= dp[B-1][N] - dp[low_bound][N];
	if(result<0)
		cout<<result+mod<<endl;
	else
		cout<<result<<endl;
	auto end = get_time::now();
	auto differ = end - start;
	//cout<<"Elapsed time is :  "<< chrono::duration_cast<ns>(differ).count()<<" ns "<<endl;
	return 0;
}
