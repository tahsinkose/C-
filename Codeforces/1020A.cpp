#include <iostream>
#include <cmath>

typedef long long ll;
using namespace std;

int main(){
	int n,h,a,b,k;
	cin>>n>>h>>a>>b>>k;
	for(int i=0;i<k;i++){
		ll t1,f1,t2,f2;
		cin>>t1>>f1>>t2>>f2;
		if(t1==t2){

			ll result = abs(f2-f1);
			cout<<result<<endl;
		}
		else{
			if((f1>=a && f1<=b) || (f1>=b && f1<=a)){
				ll result = abs(t1-t2) + abs(f1-f2);
				cout<<result<<endl;
			}
			else{
				ll first = abs(f1-a) + abs(f2-a);
				ll second = abs(f1-b) + abs(f2-b);
				ll choose = first < second ? a: b;
				ll result = abs(t1-t2) + abs(f1-choose) + abs(f2-choose);
				cout<<result<<endl;
			}
		}
	}
	return 0;
}