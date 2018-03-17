#include <bits/stdc++.h>
#include <vector>
using namespace std;

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

void BFS(vector<vector<int> >& graph,int source,vector<int>& parents,vector<int>& distances){
	int size = graph.size();
	vector<bool> visited(size,false);
    
	int processed = 0;
	distances[source] = 0;
	while(processed < graph.size()){
		auto v_ = Min_element(distances.begin(),distances.end(),visited);
		int s = distance(distances.begin(),v_);
		if(s<0)
			break;
		int cost = *v_;
		visited[s] = true;
		processed++;
		for(int i=0;i<graph[s].size();i++){
			int new_node = graph[s][i];
			if(distances[new_node] > cost + 1){
				distances[new_node] = cost+1;
                parents[new_node] = s;
            }
		}
        
	}
   
	return;
}

int main() {
    int test_case;
    cin >> test_case;
    for(int a0 = 0; a0 < test_case; a0++){
        int nodes;//nodes
        int edges;//edges
        cin >> nodes >> edges;
        vector<vector<int> > graph(nodes+1,vector<int>());
        vector<int> distances(nodes+1,INT_MAX);
        vector<int> parents(nodes+1,-1);
        for(int a1 = 0; a1 < edges; a1++){
            int x;
            int y;
            cin >> x >> y;
            graph[x].push_back(y);
	    	graph[y].push_back(x);
	    	
        }
        int source;
        cin >> source;
		BFS(graph,source,parents,distances);	
        cout<<"PARENTS"<<endl;
        for(int i=1;i<parents.size();i++)
            cout<<"Node("<<i<<"): "<<parents[i]<<endl;
        //Print op.
		/*for(int i=1;i<=nodes;i++){
           if(i==source)
               continue;
           if(distances[i]==INT_MAX)
               cout<<"-1 ";
           else
               cout<<distances[i]<<" ";
        }
        cout<<endl;*/
    }
    return 0;
}
