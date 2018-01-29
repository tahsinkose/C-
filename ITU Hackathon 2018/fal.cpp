#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <set>
#include <numeric>
#include <map>

using namespace std;
using  ns = chrono::nanoseconds;
using get_time = chrono::steady_clock ;


template < class T >
std::ostream& operator << (ostream& os, const vector<T>& v) 
{
    os << "[";
    for (typename vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        	os << " " << *ii;
    }
    os << "]";
    return os;
}

vector<int> mix(vector<int>& m,vector<int>& P){
	vector<int> out(m.size());
	for(int i=0;i<m.size();i++)
		out[P[i]-1]=m[i];
	
	return out;
}

void find_period(vector<int>& P,vector<int>& blv,vector<int>& lv,int& period,int& second_period,bool& is_lv,int & lv_ind){
	vector<int> m = P;
	sort(m.begin(),m.end());
	
	map<int,int> locations;
	for(int j=0;j<P.size();j++)
		locations[m[j]] = j;
	int before_least_ind = P.size()-2;
	blv.push_back(m[before_least_ind]);
	vector<int> n = mix(m,P);
	while(true){
			period++;
			blv.push_back(n[before_least_ind]);
			before_least_ind = locations[n[before_least_ind]];
			if(n[before_least_ind]==blv[0])
				break;
	}
	period++;
	int least_ind = P.size()-1;
	vector<int>::iterator it = find(blv.begin(),blv.end(),m[least_ind]);
	if(it==blv.end()){
		//cout<<"Create lv "<<endl;
		lv.push_back(m[least_ind]);
		while(true){
			second_period++;
			lv.push_back(n[least_ind]);
			least_ind = locations[n[least_ind]];
			if(n[least_ind]==lv[0])
				break;
		}
		is_lv = true;
		second_period++;
		//cout<<"second period: "<<second_period<<endl;
	}
	else
		lv_ind = distance(blv.begin(),it);
	//cout<<"period: "<<period<<endl;
	//cout<<blv<<endl;
}

int main(){
	auto start = get_time::now();
	unsigned long long int Q,N,K;
	cin>>Q>>N>>K;
	if(N==1){
		cout<<"NO"<<endl;
		return 0;
	}
	vector<int> P(N); //mix array
	for(int i=0;i<N;i++)
		cin>>P[i];
	int period=0,second_period=0;
	bool is_lv = false;
	vector<int> before_least_cycle,least_cycle;
	int lv_ind;
	find_period(P,before_least_cycle,least_cycle,period,second_period,is_lv,lv_ind);
	for(int i=0;i<Q;i++){
		vector<int> S(N);
		for(int j=0;j<N;j++)
			cin>>S[j];
		int l_ind,bl_ind;
		if(is_lv){
			l_ind = K%second_period;
			bl_ind = K%period;
			
			if(S[least_cycle[l_ind]-1]>S[before_least_cycle[bl_ind]-1])
				cout<<"NO"<<endl;
			else
				cout<<"YES"<<endl;
		}
		else{
			bl_ind = K%period;
			l_ind = (lv_ind+K)%period;
			/*cout<<"bl_ind: "<<bl_ind<<", l_ind: "<<l_ind<<endl;
			cout<<"S["<<before_least_cycle[l_ind]-1<<"]: "<<S[before_least_cycle[l_ind]-1]<<endl;
			cout<<"S["<<before_least_cycle[bl_ind]-1<<"]: "<<S[before_least_cycle[bl_ind]-1]<<endl;*/
			
			if(S[before_least_cycle[l_ind]-1]>S[before_least_cycle[bl_ind]-1])
				cout<<"NO"<<endl;
			else
				cout<<"YES"<<endl;
		}
		
		
	}
	auto end = get_time::now();
	auto differ = end - start;
	//cout<<"Elapsed time is :  "<< chrono::duration_cast<ns>(differ).count()<<" ns "<<endl;
	return 0;

}
