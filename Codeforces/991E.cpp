#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
vector<vector<int> > memo;
typedef unsigned long long int ull;

ull factorial(int num){
	ull result = 1;
	for(int i=2;i<=num;i++)
		result *= i;
	return result;
}

ull recurse(map<char,int> c,map<char,int>& f){
	ull result = 0;
	int base_size = 0;
	for(auto it=c.begin();it!=c.end();it++)
		base_size += it->second;
	
	result = factorial(base_size);
	if(c['0'])
		result -= c['0']*factorial(base_size-1);
	
	for(auto it=c.begin();it!=c.end();it++)
		result /= factorial(it->second);
	
	for(auto it=c.begin();it!=c.end();it++){
		if(it->second < f[it->first]){
			map<char,int> m = c;
			m[it->first]++;
			vector<int> ind;
			for(auto itr=m.begin();itr!=m.end();itr++)
				ind.push_back(itr->second);
			bool in = any_of(memo.begin(),memo.end(),
                             [&ind](const std::vector<int>& x)
                             { return x == ind; });
			if(!in){
				memo.push_back(ind);
				result += recurse(m,f);
			}
		}
	}
	return result;
	
}


int main(){
	string num;
	cin>>num;
	map<char,int> freq,curr_freq;
	for(auto& n : num)
		freq[n] = 0;
	for(auto& n : num)
		freq[n]++;
	
	for(auto it=freq.begin();it!=freq.end();it++)
		curr_freq[it->first]=1;

	ull result = recurse(curr_freq,freq);
	cout<<result<<endl;

	return 0;
}