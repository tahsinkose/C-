#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#define EPSILON 1e-8
using namespace std;

int main(){
	int n;
	cin>>n;
	vector<int> arr(n);
	int sum = 0;
	for(int i =0; i<n;i++){
		cin>>arr[i];
		sum += arr[i];
	}
	double mean = sum / (double) n;
	sort(arr.begin(),arr.end());
	if(mean>=4.5-EPSILON)
		cout<<0<<endl;
	else{
		int needed = ceil(n*4.5) - sum;
		int result = 0;
		for(int j=0;j<n;j++){
			needed -= 5-arr[j];
			result++;
			if(needed<=0)
				break;
		}
		cout<<result<<endl;
	}
	return 0;
}