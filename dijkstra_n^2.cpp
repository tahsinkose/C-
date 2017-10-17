#include <iostream>
#include <set>
#include <cstdio>
#include <climits>
#include <vector>
#include <algorithm>
#include <iomanip>
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
        os << " " << *ii;
    }
    os << "]";
    return os;
}
 
class Graph
{
	private:
		int V;
		
	public:
		Graph(int V){
			this->V=V;
			adj.clear();
			adj.resize(V);
		}
		void addEdge(int u,int v,int d);
		vector< vector<pair<int,int> > > adj;
};

void Graph::addEdge(int u,int v,int d){
	adj[u-1].push_back(make_pair(v-1,d));
	adj[v-1].push_back(make_pair(u-1,d));

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

int main(){
	auto start = get_time::now();
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        int n;
        int m;
        cin >> n >> m;
        Graph g(n);
		//cout<<"Create graph"<<endl;
        for(int a1 = 0; a1 < m; a1++){
            int x;
            int y;
            int r;
            cin >> x >> y >> r;
            g.addEdge(x,y,r);
			//cout<<"Added edge ("<<x<<"-"<<y<<")"<<endl;
        }
        int s;
        cin >> s;
		s--;
        set<int> sptSet;
	    vector<int> distances(n,INT_MAX);
        distances[s]=0;
        vector<bool> visited(n,false);
        while(sptSet.size()<n){
            auto v_ = Min_element(distances.begin(),distances.end(),visited);
            int v = distance(distances.begin(),v_);
			if(v<0)
				break;
            int weight_v = *v_;
            visited[v]=true;
            sptSet.insert(v);
            for(int i=0;i<g.adj[v].size();i++){
                int u=g.adj[v][i].first;
                int weight_u =g.adj[v][i].second;
                if(distances[u]>weight_u+weight_v)
                    distances[u] =  weight_u+weight_v;
				
 		    }
	   }
       for(int i=0;i<n;i++){
           if(i==s)
               continue;
           if(distances[i]==INT_MAX)
               cout<<"-1 ";
           else
               cout<<distances[i]<<" ";
       }
       cout<<endl;
    }
	auto end = get_time::now();
	auto differ = end - start;
	cout<<"Elapsed time is :  "<< chrono::duration_cast<ns>(differ).count()<<" ns "<<endl;
    return 0;
}
