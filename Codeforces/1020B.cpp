#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main(){
	int n;
	cin>>n;
	vector<int> arr(n+1);
	for(int i=1;i<=n;i++)
		cin>>arr[i];
	for(int i=1;i<=n;i++){
		map<int,int> cycle_checker;
		int track = i;
		cycle_checker[track] = 1;
		while(cycle_checker[track]!=2){
			track = arr[track];
			cycle_checker[track]++;
		}
		cout<<track<<" ";
		cycle_checker.clear();
	}
	cout<<endl;
	return 0;
}