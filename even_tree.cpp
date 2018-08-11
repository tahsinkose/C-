#include <iostream>
#include <vector>
#include <map>
using namespace std;

map< pair<int,int> , int> edge_storages;

int traverse(vector<vector<int> >& graph,int curr_node){
	int sum = 0;
	for(auto n : graph[curr_node]){
		int result = traverse(graph,n);
		edge_storages[{curr_node,n}] = result;
		sum += result;
	}
	return sum+1;
}

int main(){
	int n,e;
	cin>>n>>e;
	vector<vector<int> > graph(n+1);
	for(int i=0;i<e;i++){
		int x,y;
		cin>>x>>y;
		if(x<y)
			graph[x].push_back(y);
		else
			graph[y].push_back(x);
	}
	int curr_node = 1;
	traverse(graph,curr_node);
	int result = 0;
	for(auto it = edge_storages.begin();it!=edge_storages.end();it++){
		if(it->second %2 == 0)
			result++;
		//cout<<"Edge["<<it->first.first<<","<<it->first.second<<"] = "<<it->second<<endl;
	}
	cout<<result<<endl;
	
	return 0;
}