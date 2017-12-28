#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <stack>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;
using  ns = chrono::nanoseconds;
using get_time = chrono::steady_clock ;
typedef struct tea_fun {
	int net;
	vector<int> friends;
} Fun;

bool not_duplicate(vector<int> f,int not_friend){
	for(int i=0;i<f.size();i++)
		if(f[i]==not_friend)
			return false;
	return true;
}

int main(){
	int funs,friendships,max_result=0;
	cin>>funs;
	cin>>friendships;
	vector<Fun> party(funs+1);
	vector<bool> visited(funs + 1, false);
	for(int i=1;i<=funs;i++)
	{
		int brings,drinks;
		cin>>brings;
		cin>>drinks;
		party[i].net = brings-drinks;
		party[i].friends.clear();
	}
	
	for(int i=1;i<=friendships;i++){
		int fun1,fun2;
		cin>>fun1;
		cin>>fun2;
		if(not_duplicate(party[fun1].friends,fun2))
			party[fun1].friends.push_back(fun2);
		if(not_duplicate(party[fun2].friends,fun1))
			party[fun2].friends.push_back(fun1);
	}
	
	auto start = get_time::now();
	// First, need to discover friendless funs.
	for(int i=1;i<=funs;i++){
			if(party[i].friends.empty() && party[i].net > 0)
				max_result+=party[i].net;
	}
	
	// Then, need to check friendly funs.
	for(int i=1;i<=funs;i++){
			if(!visited[i] && !party[i].friends.empty()){
				//cout<<"STARTING WITH fun"<<i<<endl;
				int check_sum=0;
				queue<int> q;
				q.push(i);
				visited[i] = true;
				while(!q.empty()){
						int fun = q.front();
						q.pop();
						//cout<<"fun"<<fun<<"->net = "<<party[fun].net<<endl;
						check_sum+=party[fun].net;
						int friends=party[fun].friends.size();
						for(int j=0;j<friends;j++){
							int who = party[fun].friends[j];
							//cout<<"fun"<<who<<" is a friend of fun"<<fun<<endl;
							if(!visited[who]){
								//cout<<"pushing fun"<<who<<" to the stack."<<endl;
								q.push(who);
								visited[who]=true;
							}
						}
							
				}
				if(check_sum>0)
					max_result+=check_sum;
				
			}
	}
	
	auto end = get_time::now();
	auto differ = end - start;

	//cout << "Elapsed time is :  "<< chrono::duration_cast<ns>(differ).count()<<" ns "<<endl;
	cout << max_result<<endl;
	return 0;
}
