#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>
using namespace std;
typedef long long int ll;
int main(){
	int voters,parties;
	cin>>voters>>parties;
	vector<vector<ll> > vote_prices(parties+1);
	for(int i=0;i<voters;i++){
		ll party,price;
		cin>>party>>price;
		vote_prices[party].push_back(price);
	}
	
	for(int k=1;k<vote_prices.size();k++)
		sort(vote_prices[k].begin(),vote_prices[k].end());
	
	
	ll result = LLONG_MAX;
	for(int i=0;i<=voters;i++){
		ll min_ = 0;
		int united_party_voters = vote_prices[1].size();
		priority_queue<ll,vector<ll>,greater<ll> > queue_;
		for(int k=2;k<=parties;k++){
			int taken = 0;
			while(vote_prices[k].size() - taken > i){
				min_ += vote_prices[k][taken++];
				united_party_voters++;
			}
			while(taken < vote_prices[k].size())
				queue_.push(vote_prices[k][taken++]);
		}
		while(united_party_voters <= i && !queue_.empty()){
			min_ += queue_.top();
			united_party_voters++;
			queue_.pop();
		}
		result = min(min_,result);
	}
	cout<<result<<endl;
	return 0;
}