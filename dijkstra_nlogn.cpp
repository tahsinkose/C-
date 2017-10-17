#include <iostream>
#include <set>
#include <vector>
#include <climits>
#include <stdlib.h>
#include <chrono>

using namespace std;
using  ns = chrono::nanoseconds;
using get_time = chrono::steady_clock ;

template < class T >
std::ostream& operator << (ostream& os, const vector<T>& v) 
{
    os << "[";
    for (typename vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
		if(*ii==INT_MAX)
			os<<" "<<-1;
		else
        	os << " " << *ii;
    }
    os << "]";
    return os;
}
 
struct edge{ int to,length;};

vector<int> dijkstra(const vector<vector<edge> > &graph, int source){
	vector<int> min_distance(graph.size(),INT_MAX);
	min_distance[ source ]=0;
	set< pair<int,int> > active_vertices;
	active_vertices.insert({0,source});
	
	while(!active_vertices.empty()){
		int where = active_vertices.begin()->second;
		active_vertices.erase(active_vertices.begin());
		for(auto ed: graph[where]){
			if( min_distance[ed.to] > min_distance[where] + ed.length){
				active_vertices.erase( {min_distance[ed.to],ed.to});
				min_distance[ed.to]=min_distance[where] + ed.length;
				active_vertices.insert( {min_distance[ed.to],ed.to});
			}
		}
	}
	return min_distance;
}

int main(){	
	auto start = get_time::now();
	int t;
    cin >> t;
	for(int a0=0;a0<t;a0++){
		int vertices,edges,source;
		cin>>vertices>>edges;
		vector< vector<edge> > graph(vertices);
	
		for(int i=0;i<edges;i++){
			int u,v,dist;
			cin>>u>>v>>dist;
			struct edge* e1 = (struct edge*) malloc(sizeof(struct edge));
			struct edge* e2 = (struct edge*) malloc(sizeof(struct edge));
			e1->to=--v;
			e1->length=dist;
			e2->to=--u;
			e2->length=dist;
			graph[u].push_back(*e1);
			graph[v].push_back(*e2);
		}
		cin>>source;

		vector<int> min_distances = dijkstra(graph,--source);
		cout<<min_distances<<endl;
	}
	auto end = get_time::now();
	auto differ = end - start;
	cout<<"Elapsed time is :  "<< chrono::duration_cast<ns>(differ).count()<<" ns "<<endl;
	return 0;
}
