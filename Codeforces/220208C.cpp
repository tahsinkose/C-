#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

struct node {
	int difference;
	int index;
};

bool compareDiffs(const node &a, const node &b){
	return a.difference < b.difference;
}

int main(){
	int n,k;
	cin>>n>>k;
	vector<int> current_prices(n);
	vector<int> after_prices(n);
	for(int i=0;i<n;i++)
		cin>>current_prices[i];
	for(int i=0;i<n;i++)
		cin>>after_prices[i];
	
	vector<node> positive_differences;
	int bought_currently = 0;
	unsigned long long int total_paid = 0;
	for(int i=0;i<n;i++){
		if(current_prices[i] > after_prices[i]){
			node item;
			item.difference =  current_prices[i] - after_prices[i];
			item.index = i;
			positive_differences.push_back(item);
		}
		else{
			bought_currently++;
			total_paid += current_prices[i];
		}
	}
	//Choose minimumly differenced k items in a sorted array.
	if(bought_currently>=k){
		for(int i=0;i<positive_differences.size();i++)
			total_paid += after_prices[positive_differences[i].index];
	}
	else{
		sort(positive_differences.begin(),positive_differences.end(),compareDiffs);
		int ind = 0;
		for(int i = bought_currently;i<k;i++)
			total_paid += current_prices[positive_differences[ind++].index];
		for(;ind<positive_differences.size();ind++)
			total_paid += after_prices[positive_differences[ind].index];
	}
	cout<<total_paid<<endl;	
	return 0;
}