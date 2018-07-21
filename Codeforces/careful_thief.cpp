#include <iostream>
#include <algorithm>
using namespace std;

typedef long long int ll;

struct node{
	int l,r,v;
	node(){}
	node(int l,int r,int v) : l(l), r(r), v(v) {}
	bool operator  < (const node& n) const {
		return l < n.l;
	} 
};
int const MAXN = 1e5 + 5;
int main(){
	node arr[MAXN];
	ll dp[MAXN];
	int t;
	scanf("%d",&t);
	while(t--!=0){
		int m,k;
		scanf("%d %d",&m,&k);
		for(int j=1;j<=m;j++)
			scanf("%d %d %d",&arr[j].l,&arr[j].r,&arr[j].v);
		++m;
		arr[m] = node(-1,-1,0);
		sort(arr+1,arr+m+1);
		for(int j=1;j<=m;j++)
			dp[j] = 1ll* (arr[j].r - arr[j].l + 1) * arr[j].v + dp[j-1];
		ll max_ = 0;
		for(int j=1,above_limit;j<=m;j++){
			above_limit = arr[j].l + k - 1;
			int index = upper_bound(arr+1,arr+m+1,node(above_limit,2e9,2e9)) - arr;
			--index;
			if(above_limit >= arr[index].r)
				max_ = max(max_, dp[index] - dp[j-1]);
			else
				max_ = max(max_, dp[index-1] - dp[j-1] + 1ll * (above_limit - arr[index].l + 1) * arr[index].v );
		}
		
		for(int j=m,below_limit;j>0;j--){
			below_limit = max(0,arr[j].r - k + 1);
			int index = upper_bound(arr + 1, arr+m+1, node(below_limit,2e9,2e9)) - arr;
			--index;
			if(below_limit <= arr[index].l)
				max_ = max(max_,dp[j] - dp[index-1]);
			else
				max_ = max(max_,dp[j] - dp[index] + 1ll * (arr[index].r - below_limit + 1) * arr[index].v);
		}
		
		cout<<max_<<endl;
	}
	
	return 0;
}