#include <iostream>
#include <climits>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
//#include <functional>
// Implements shortest reach trees for all nodes.

using namespace std;

ostream& operator<<(ostream& out,vector<int>& v){
    for(int i=0;i<v.size();i++)
        out << v[i]<<",";
    out << endl;
    return out;
}
vector<int>::iterator Min_element(vector<int>::iterator it1,vector<int>::iterator it2,vector<bool>& v){
	int min=INT_MAX;
	size_t ind=0;
	vector<int>::iterator result;
	for(;it1!=it2;it1++,ind++){
		if(*it1<min && v[ind]==false){
			
			min=*it1;
			result=it1;
		}
	}
	return result;
}

pair<int,int> kth_shortest_vertex(int k,int source,vector<int>& distances){
    
    vector<bool> v(distances.size(),false);
    for(int i=1;i<k;i++){
        auto min = Min_element(distances.begin(),distances.end(),v);
        int s = distance(distances.begin(),min);
        v[s]=true;
    } 
    auto kth_min = Min_element(distances.begin(),distances.end(),v);
    return {distance(distances.begin(),kth_min),*kth_min};
}





void BFS(vector<vector<pair<int,int> > >& graph,int source,vector<int>& parents,vector<int>& distances){
    int size = graph.size();
	vector<bool> visited(size,false);
	int processed = 0;
    distances[source] = 0; // distances = { 0, INF,INF, ...}
    while(processed < graph.size()){
		auto v_ = Min_element(distances.begin(),distances.end(),visited); // O(n)
		int s = distance(distances.begin(),v_);
		if(s<0)
			break;
		int cost = *v_;
		visited[s] = true;
		processed++;
		for(int i=0;i<graph[s].size();i++){
			pair<int,int> v = graph[s][i];
			int new_node = v.first;
			int new_cost = v.second;
			if(distances[new_node] > cost+new_cost){
				distances[new_node] = cost + new_cost;
                parents[new_node] = s;
            }
		}
	}
	return;
}












void ShortestPaths(vector<vector<pair<int,int> > >& graph){
    int nodes = graph.size()-1;
    for(int source=1;source<=nodes;source++){
        vector<int> parents(nodes+1,-1);
        vector<int> distances(nodes+1,INT_MAX);

	    BFS(graph,source,parents,distances);

        vector<vector<int> > paths(nodes+1,vector<int>());
        for(int i=1;i<=nodes;i++){
            if(i==source)
                continue;
            int j=i;
            paths[i].push_back(j);
            while(j!=source){
                paths[i].push_back(parents[j]);
                j = parents[j];
            }
        }
        cout<<"Source "<<source<<":"<<endl;
        for(int i=1;i<=nodes;i++){
            if(i==source)
                continue;
            for(int j=paths[i].size()-1;j>=0;j--)
                cout<<paths[i][j]<<" ";
            cout<<endl;
        }
        cout<<endl;
    }
    return;
}

void FindKth_Element(vector<vector<pair<int,int> > >& graph){
    int nodes = graph.size()-1;
    for(int source=1;source<=nodes;source++){
        vector<int> parents(nodes+1,-1);
        vector<int> distances(nodes+1,INT_MAX);
        BFS(graph,source,parents,distances);
        for(int i=1;i<=nodes;i++){
            pair<int,int> kth_min = kth_shortest_vertex(i,source,distances);
            
            cout<<"Closest vertex ("<<i<<") from source("<<source<<")= "<<kth_min.first<<" at distance "<<kth_min.second<<endl;
        }
    }
    return;
}



int main(){
    int nodes,edges;
    cin>>nodes>>edges;
    vector<vector<pair<int,int> > > graph(nodes+1,vector<pair<int,int> >());
    for(int a1 = 0; a1 < edges; a1++){
        int x;
        int y;
        int cost;
        cin >> x >> y >> cost;
        graph[x].push_back({y,cost});
    	graph[y].push_back({x,cost});
	    	
    }
   
    ShortestPaths(graph);
    FindKth_Element(graph);
    //NonOverlappingMaxElement(graph);

    return 0;
}
