#include <iostream>
#include <cmath>
using namespace std;
typedef  long long int ll;
int main(){
	ll n;
	cin>>n;
	ll left = 1, right = n;
	while(left<right){
		ll tmp = n;
		ll vastya = 0;
		ll mid = (left+right)/2;
		while(tmp>0){
			vastya += (mid<tmp ? mid : tmp);
			if(vastya*2>=n)break;
			tmp -= mid;
			tmp -= (tmp/10);
		}
		if(vastya*2>=n)
			right = mid;
		else
			left = mid+1;
	}
	cout<<left<<endl;
	return 0;
}