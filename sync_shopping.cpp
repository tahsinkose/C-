#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
#include <queue>
#include <map>
using namespace std;


enum CAT{BIG_CAT,LITTLE_CAT};
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

ostream& operator<<(ostream& out,CAT cat){
    if(cat == BIG_CAT)
        out << "BIG_CAT";
    else
        out << "LITTLE_CAT";
    return out;
}
ostream& operator<<(ostream& out,vector<bool>& v){
    for(int i=1;i<v.size();i++){
        if(v[i])
            out<<"Type "<<i<<": True"<<endl;
        else
            out<<"Type "<<i<<": False"<<endl;
    }
    return out;
}

void changeCat(CAT& cat,bool b,bool l){
    if(cat==BIG_CAT && !l)
        cat=LITTLE_CAT;
    else if(cat==LITTLE_CAT && !b)
        cat=BIG_CAT;
}

bool all_bought(vector<bool>& b){
    for(int i=1;i<b.size();i++)
        if(!b[i])
            return false;
    return true;
}

void BFS(vector<vector<pair<int,int> > >& graph,int source,int& val){
	int size = graph.size();
	vector<bool> visited(size,false);
    vector<int> distances(size+1,INT_MAX);	
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
			pair<int,int> v = graph[s][i];
			int new_node = v.first;
			int new_cost = v.second;
			if(distances[new_node] > cost+new_cost)
				distances[new_node] = cost + new_cost;
		}
	}
    
    val+=distances[size-1];
	return;
}

void SimultaneousBFS(vector<vector<pair<int,int> > >& graph,vector<vector<int> >& ss,int node,vector<bool>& bought,int &m,int& n){
    CAT cat = BIG_CAT;
    
    int Bfrontier,Lfrontier;
    int* fPtr;
    Bfrontier = node; //All adjacent nodes are pushed.
    Lfrontier = node;
    bool big_cat_done = false;
    bool little_cat_done = false;
    
    fPtr = &Bfrontier;
    // Recursion should be here.
    while(true){
        
        cout<<"Cat: "<<cat<<" at shopping_center: "<<*fPtr<<endl;
        for(int i=0;i<ss[*fPtr].size();i++){
            int fish_type = ss[*fPtr][i];
            bought[fish_type] = true;
        }
        cout<<"---------FISH STATUS---------------------"<<endl;
        cout<<bought<<endl;
        map<int,pair<int,int> > center_heuristics; // In fact, at most 2.
        cout<<"Adjacent shopping centers: "<<graph[*fPtr].size()<<endl;
        for(int i=0;i<graph[*fPtr].size();i++){
            int next_center = graph[*fPtr][i].first;
            int cost = graph[*fPtr][i].second;
            int cardinality = 0;
            for(int j=0;j<ss[next_center].size();j++){
                int fish_type = ss[next_center][j];
                if(!bought[fish_type])
                    cardinality++;
            }
            center_heuristics[next_center]={cardinality,cost};
        }
        for(auto it=center_heuristics.begin();it!=center_heuristics.end();it++)
            cout<<"Adjacent Shopping Center "<<it->first<<" have "<<it->second.first<<" new types of fish with "<<it->second.second<<" cost"<<endl;
        int cost;
        int which_center;
        int best_cardinality = INT_MIN;
        //Choose the most cardinality one.
        for(auto it=center_heuristics.begin();it!=center_heuristics.end();it++){
            if(it->second.first>best_cardinality){
                best_cardinality = it->second.first;
                cost = it->second.second;
                which_center = it->first;
            }
        }
        
        *fPtr = which_center;
        cout<<"Decided to go with center "<<*fPtr<<endl;
        for(int i=0;i<ss[*fPtr].size();i++){
            int fish_type = ss[*fPtr][i];
            bought[fish_type] = true;
        }
        if(cat==BIG_CAT)
            m+=cost;
        else
            n+=cost;
        // Ops for next iteration.
        if(all_bought(bought))
            break;
        changeCat(cat,big_cat_done,little_cat_done);
        if(cat==BIG_CAT)
            fPtr = &Bfrontier;
        else if(cat==LITTLE_CAT)
            fPtr = &Lfrontier;   
    }
    BFS(graph,Bfrontier,m);
    BFS(graph,Lfrontier,n);
}

int main() {
    int shopping_centers,roads,fish_types;
    cin>>shopping_centers>>roads>>fish_types;
    vector<vector<int> > ss(shopping_centers+1);
    for(int i=1;i<=shopping_centers;i++){
        int number_of_types;
        cin >> number_of_types;
        for(int j=1;j<=number_of_types;j++){
            int type;
            cin>>type;
            ss[i].push_back(type);
        }
    }
    vector<vector<pair<int,int> > > graph(shopping_centers+1,vector<pair<int,int> >());
    for(int i=0;i<roads;i++){
        int u,v,cost;
        cin>>u>>v>>cost;
        graph[u].push_back({v,cost});
        graph[v].push_back({u,cost});
    }
    vector<bool> bought(fish_types+1,false);
    int max_time_big_cat = 0,max_time_little_cat=0;
    SimultaneousBFS(graph,ss,1,bought,max_time_big_cat,max_time_little_cat);
    if(max_time_big_cat > max_time_little_cat)
        cout<<max_time_big_cat<<endl;
    else
        cout<<max_time_little_cat<<endl;
    return 0;
}

