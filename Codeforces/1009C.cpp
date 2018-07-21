#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip> 
using namespace std;


ostream& operator<<(ostream& o, vector<int>& v){
	o<<"[";
	for(auto i : v)
		o<<i<<",";
	o<<"]";
	return o;
}

int main(){
	int n,m;
	cin>>n>>m;

	// Always choose 0 as the index when d>=0 and choose middle point as the index when d<0.
	long long result = 0;
	for(int i=0;i<m;i++){
		long double tmp = 0;
		int x,d;
		cin>>x>>d;
		if(d>=0)
			result += (((long long)(n-1)*n)/2)*d + ((long long)n*x);
		else{
			double s;
			if(n%2==0){
				long long k=(n-2)/2;
				s = (k+1)*(k+1);
			}
			else{
				long long k = (n-1)/2;
				s = k*(k+1);
			}
			result += (s*d) + (n*x);
		}
	}
	

	cout<<setprecision(8)<<fixed<<(double)result/n*1.0<<endl;

	return 0;
}