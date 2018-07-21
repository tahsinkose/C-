#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;
using  ns = chrono::nanoseconds;
using get_time = chrono::steady_clock ;

int main(){
	string s;
	cin>>s;
	auto start = get_time::now();
	if(s.find('2')==string::npos){
		sort(s.begin(),s.end());
		cout<<s<<endl;
		return 0;
	}
	// Init logic
	int point;
	for(int i=0;i<s.size();i++){
		if(s[i]!='2')continue;
		else{
			string init = s.substr(0,i);
			sort(init.begin(),init.end());
			s.replace(0,i,init);
			point = i;
			break;
		}
	}
	auto it = s.begin(), itr = s.begin();
	advance(it,point);
	int ones = 0;
	for(;it!=s.end();it++){
		if(*it=='1'){
			ones++;
			s.erase(it);
			it--;
		}
	}
	s.insert(point,ones,'1');
	cout<<s<<endl;
	auto end = get_time::now();
	auto differ = end - start;
	//cout<<"Elapsed time is :  "<< chrono::duration_cast<ns>(differ).count()<<" ns "<<endl;
	return 0;
}
