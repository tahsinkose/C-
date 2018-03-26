#include <bits/stdc++.h>
using namespace std;
int n;
long recurse(long c_sum,int from,vector < long >& c){
    if(c_sum==n)
        return 1;
    if(c_sum>n)
        return 0;
    long result = 0;
    for(int i=from;i<c.size();i++){
        result+=recurse(c_sum+c[i],i,c);
    }
    return result;
}

long getWays(long n, vector < long >& c){
    sort(c.begin(),c.end());
    long result = 0;
    for(int i=0;i<c.size();i++)
        result+=recurse(c[i],i,c);
    return result;
}




long dp[251];
int main() {
    
    int m;
    cin >> n >> m;
    vector<long> c(m);
    for(int c_i = 0; c_i < m; c_i++){
       cin >> c[c_i];
    }
    // Print the number of ways of making change for 'n' units using coins having the values given by 'c'
    //long ways = getWays(n, c);
    dp[0] = 1;
    sort(c.begin(),c.end());
    for(int i=0;i<c.size();i++){
        for(int j=c[i];j<=n;j++)
            dp[j] += dp[j-c[i]];
    }

    cout<<dp[n]<<endl;
    return 0;
}
