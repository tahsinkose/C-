#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        string s[n];
        for(int i=0;i<n;i++)cin>>s[i];
        int g[n][n];
		
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(s[i][j]=='X')g[i][j]=-1;
                else{
                    set<int> x;
                    if(i>0){
						x.insert(g[i-1][j]);
					}
                    if(j>0){
						x.insert(g[i][j-1]);
					}
                    if(i>0 && j>0){
						x.insert(g[i-1][j-1]);
					}                    
                    g[i][j]=0;
                    while(x.find(g[i][j])!=x.end()){
						g[i][j]++;
					}
                }
            }
        }
     	int ans=0;
        
        for(int i=0;i<n;i++){for(int j=0;j<n;j++){if(s[i][j]=='K')ans^=g[i][j];}}
        if(ans==0)cout<<"LOSE"<<endl;
        else{
            int count=0;
            for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(s[i][j]=='K'){
                    if(i>0 && g[i-1][j]!=-1 && (g[i][j]^g[i-1][j])==ans)count++;
                    if(j>0 && g[i][j-1]!=-1 && (g[i][j]^g[i][j-1])==ans)count++;
                    if(i>0 && j>0 && g[i-1][j-1]!=-1 && (g[i][j]^g[i-1][j-1])==ans)count++;
                }
            }}
            cout<<"WIN "<<count<<endl;
        }
    }
    return 0;
}
