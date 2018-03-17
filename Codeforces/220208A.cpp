#include <iostream>
#include <vector>
#include <climits>

using namespace std;


int main(){
	int K;
	cin>>K;
	vector<int> r(K);
	int max = INT_MIN;
	for(int i=0;i<K;i++){
		cin>>r[i];
		if(max < r[i])
			max = r[i];
	}
	if(max<=25)
		cout<<0<<endl;
	else
		cout<<max-25<<endl;
	return 0;
}