#include <bits/stdc++.h>
#include <stack>
#include <chrono>
#include <algorithm>
using namespace std;
using  ns = chrono::nanoseconds;
using get_time = chrono::steady_clock ;


template <typename T>
std::ostream& operator<< (ostream& out, const vector<T>& v) {
  if ( !v.empty() ) {
    out << '[';
    copy (v.begin(), v.end(), ostream_iterator<T>(out, ", "));
    out << "\b\b]";
  }
  return out;
}

int main() {
	auto start = get_time::now();
    int n;
    cin >> n;
	
	vector<int> colors(n);
	vector<vector<int>> edges;
	vector<int> parents(n,-1);
	edges.resize(n);
    for(int c_i = 0; c_i < n; c_i++){
	   int color;
       cin >> color;
	   colors[c_i] = (color*2)-1;
    }
    for(int a0 = 0; a0 < n-1; a0++){
        int x;
        int y;
        cin >> x >> y;
		edges[x-1].push_back(y-1);
		edges[y-1].push_back(x-1);
    }
	vector<int> minima = colors;
	vector<int> maxima = colors;
	
	vector<bool> children_done(n,false);
	
	stack<int> todo;
	todo.push(0);
	todo.push(0);
	while(!todo.empty()){
		int node = todo.top();
		todo.pop();
		if(children_done[node]==false){
			for(int i=0;i<edges[node].size();i++){
				int child = edges[node][i];
				if(child!=parents[node]){
					parents[child] = node;
					todo.push(child);
					todo.push(child);
				}
			}
			children_done[node]=true;
		}	
		else{
			for(int i=0;i<edges[node].size();i++){
				int child = edges[node][i];
				
				if(child!=parents[node]){
					minima[node] += minima[child];
					maxima[node] += maxima[child];
				}
			}
			if(minima[node] > 0)
            	minima[node] = 0;
        	if(maxima[node] < 0)
            	maxima[node] = 0;
		}
	}
	int bestroot = 0;
	int best;
	auto max_result = max_element(maxima.begin(),maxima.end());
	auto min_result = min_element(minima.begin(),minima.end());
	if(*max_result >= abs(*min_result)){
		bestroot = distance(maxima.begin(),max_result);
		best = *max_result;
	}
	else{
		bestroot = distance(minima.begin(),min_result);
		best = abs(*min_result);
	}
	vector<int> subtree;
	todo.push(bestroot);
	if(abs(minima[bestroot]) > maxima[bestroot]){
		while(!todo.empty()){
			int node = todo.top();
			todo.pop();
			subtree.push_back(node+1);
			for(int i=0;i<edges[node].size();i++){
				int child = edges[node][i];
				if(child!=parents[node] && minima[child] < 0)
					todo.push(child);
			}
		}
	}
	else{
		while(!todo.empty()){
			int node = todo.top();
			todo.pop();
			subtree.push_back(node+1);
			for(int i=0;i<edges[node].size();i++){
				int child = edges[node][i];
				if(child!=parents[node] && maxima[child] > 0)
					todo.push(child);
			}
		}
	}
	cout<<best<<endl;
	cout<<subtree.size()<<endl;
	for(int i=0;i<subtree.size();i++)
		cout<<subtree[i]<<" ";
	cout<<endl;
	auto end = get_time::now();
	auto differ = end - start;
	long long int elapsed = chrono::duration_cast<ns>(differ).count();
	double inSecond = elapsed/1000000000.0;
	//cout<<"Elapsed time is : "<<fixed<<setprecision(3)<<inSecond<<" s"<<endl;
	
	
	
    return 0;
}
