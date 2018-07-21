#include <iostream>
#include <vector>

using namespace std;

int main(){
	int n,m;
	cin>>n>>m;
	vector<int> games(n),bills(m);
	for(int i=0;i<n;i++)
		cin>>games[i];

	for(int i=0;i<m;i++)
		cin>>bills[i];

	int bought = 0;
	int cnt = 0;
	for(int i=0;i<n;i++){
		if(bills[cnt]>=games[i]){
			bought++;
			cnt++;
		}
		if(cnt==m)
			break;
	}
	cout<<bought<<endl;
	return 0;
}