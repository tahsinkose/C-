#include <iostream>
#include <vector>
#include <tuple>
#include <chrono>
#include <climits>
#include <algorithm>
#include <map>

using namespace std;
using  ns = chrono::nanoseconds;
using get_time = chrono::steady_clock ;

typedef long long int ll;
int n,first_half,token[2000010],cnt;
struct hero_data{
	int process_order;
	int attitude;
}storage[2222222];

map<pair<ll,ll>,ll> f;
vector<int> L,M,W;
ll ind=0;
ll result = LLONG_MIN;
ll dfs1_pointer,dfs2_pointer;
void dfs1(int task,ll ax,ll ay,ll az,ll proc_order){
	
	if(task==first_half+1){//Final task
		ay-=ax;
		az-=ax;
		pair<ll,ll> key = make_pair(ay,az);
		if(f.count(key)){//
			ll i = f[key]; 
			if(storage[i].attitude < ax){//Check the found process unit's attitude with respect to older one with same features.
				storage[i].attitude = ax;
				storage[i].process_order = proc_order; 
			}
		}
		else{
			f[key] = ++ind;//Stores the position of the current process unit
			storage[ind].process_order = proc_order;
			storage[ind].attitude = ax;
		}
		return;
	}
	dfs1(task+1,ax+L[task],ay+M[task],az,3*proc_order);
	dfs1(task+1,ax,ay+M[task],az+W[task],3*proc_order+1);
	dfs1(task+1,ax+L[task],ay,az+W[task],3*proc_order+2);
	
	
}

void dfs2(int task,ll ax,ll ay,ll az,ll proc_order){
	
	if(task==first_half){
		ay-=ax;
		az-=ax;
		pair<ll,ll> key = make_pair(-ay,-az);
		if(f.count(key)){//
			ll i = f[key]; //Fetch the actual index
			if(storage[i].attitude + ax > result){
				result = storage[i].attitude + ax;
				dfs1_pointer = storage[i].process_order; //Pointer for first traversal
				dfs2_pointer = proc_order; // Pointer for second traversal
			}
		}
		return;
	}
	dfs2(task-1,ax+L[task],ay+M[task],az,3*proc_order);
	dfs2(task-1,ax,ay+M[task],az+W[task],3*proc_order+1);
	dfs2(task-1,ax+L[task],ay,az+W[task],3*proc_order+2);
	
}


void print_ordering()
{
    for (int i = 1; i <= first_half; i++)
    {
        token[++cnt] = dfs1_pointer % 3;
        dfs1_pointer /= 3;
    }
    for (int i = cnt; i >= 1; i--)
    {
        if (token[i] == 0)
            puts("LM");
        if (token[i] == 1)
            puts("MW");
        if (token[i] == 2)
            puts("LW");
    }
    cnt = 0;
    for (int i = first_half + 1; i <= n; i++)
    {
        token[++cnt] = dfs2_pointer % 3;
        dfs2_pointer /= 3;
    }
    for (int i = 1; i <= cnt; i++)
    {
        if (token[i] == 0)
            puts("LM");
        if (token[i] == 1)
            puts("MW");
        if (token[i] == 2)
            puts("LW");
    }
}

int main(){
	auto start = get_time::now();
	ios::sync_with_stdio( 0 );
	
	cin >> n;
	first_half = (int)ceil(n/2.0);
	L.resize(n+1);M.resize(n+1);W.resize(n+1);
	for(int i=1;i<=n;i++)
		cin>>L[i]>>M[i]>>W[i];
	dfs1(1,0,0,0,0);
	//Now need to meet in the middle. So process second part.
	dfs2(n,0,0,0,0);
	
	if(result==LLONG_MIN)
		cout<<"Impossible"<<endl;
	else
		print_ordering();
	auto end = get_time::now();
	auto differ = end - start;

	//cout<<"Elapsed time is :  "<< chrono::duration_cast<ns>(differ).count()<<" ns "<<endl;

	return 0;
}