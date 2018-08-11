/*	
	Solution to https://www.hackerrank.com/challenges/journey-to-the-moon/problem
*/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;


ostream& operator<<(ostream& out,vector<int>& arr){
	for(auto i : arr)
		out<<i<<" ";
	return out;
}

int main(){
    int n,p;
    cin>>n>>p;
    vector<vector<int> > graph(n);
    vector<bool> visited(n,false);
    for(int i=0;i<p;i++){
        int a,b;
        cin>>a>>b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    vector<vector<int> > all_connected_components;
    stack<int> active_vertices;
    for(int i=0;i<n;i++){
    	if(!visited[i]){
    		visited[i] = true;
    		active_vertices.push(i);
    		vector<int> connected_component;
    		while(!active_vertices.empty()){
    			
    			int v = active_vertices.top();
    			connected_component.push_back(v);
    			active_vertices.pop();
    			for(auto n : graph[v])
    				if(!visited[n]){
    					visited[n] = true;
    					active_vertices.push(n);
    				}
    		}
    		all_connected_components.push_back(connected_component);
    	}
    }
    unsigned long long int left_num_astronauts = n;
    unsigned long long int num_of_ways = 0;
    for(int i=0;i<all_connected_components.size();i++){
    	left_num_astronauts -= all_connected_components[i].size();
    	num_of_ways += left_num_astronauts * all_connected_components[i].size();
    }
    cout<<num_of_ways<<endl;
    return 0;
}