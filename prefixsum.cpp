#include <iostream>
#include <vector>
#include <climits>
using namespace std;
#define MAX 100

ostream& operator << (ostream& os,const vector<int>& v){
	for(int i=0;i<v.size();i++)
		os << v[i]<<" ";
	return os;
}

long long int compute(int x){
	double x_ = (double)x;
	double y  = x_ / 2.0;
	double result = y*(x_+1);
	return (int) result;
}

int main(){
	int N,K,result=0;
	cin>>N;
	vector<int> arr(N),prefix_array(N,0);
	int min = INT_MAX;
	for(int i=0;i<N;i++){
		cin>>arr[i];
		if(arr[i]<min)
			min = arr[i];
	}

	cin>>K;
	if(min<0){
		for(int i=0;i<N;i++)
			arr[i] += -min;

		K+=N*-min;
	}
	prefix_array[0] = arr[0];
	int fully_covers=0;
	int ends=-1;
	for(int i=1;i<N;i++){
		prefix_array[i] = prefix_array[i-1] + arr[i];
		if(arr[i]>K){
			ends = i;
			continue;
		}
		if(prefix_array[i]<K)
			fully_covers = i;
	}
	fully_covers++;
	result = compute(fully_covers);
	cout<<"fully_covers: "<<fully_covers<<endl;
	for(int j=fully_covers;j<N;j++){
		int k = j;
		while(true){
			if(k==0 || k==j)
				break;
			if(prefix_array[j] - prefix_array[k/2] < K)
				k/=2;
			else
				k=(k/2)+1;
		}
		cout<<"Found k: "<<k<<" for j: "<<j<<endl;
		result += compute(j+1) - compute(fully_covers) - compute(k+1);
		cout<<"Result: "<<result<<" at j: "<<j<<endl;
	}
	cout<<"result: "<<result<<endl;
	cout<<prefix_array<<endl;
	return 0;
}