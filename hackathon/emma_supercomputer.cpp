#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <climits>
#include <chrono>

#define VALID_CELL(i,j,c,N,M) (i-c>=0 && i+c<N && j-c>=0 && j+c<M)
 
using namespace std;
using  ns = chrono::nanoseconds;
using get_time = chrono::steady_clock ;


int main() {
	
	auto start = get_time::now();
	int N,M;
	cin>>N>>M;
	vector<string> grid(N);
	set< pair<int,int> > goods;
	set< pair<int, set< pair<int,int> > > > pluses;
	for(int i=0;i<N;i++){
		cin>>grid[i];
		for(int j=0;j<M;j++){
			if(grid[i][j]=='G' && i!=0 && i!=N && j!=0 && j!=M)
				goods.insert({i,j});
		}
	}
	for(auto it=goods.begin();it!=goods.end();it++){
		int i=(*it).first;
		int j=(*it).second;
		
		int change_factor=1;
		int max_area=5;
		while(true){
			if(VALID_CELL(i,j,change_factor,N,M) && grid[i-change_factor][j]=='G' && grid[i+change_factor][j]=='G' && grid[i][j-change_factor]=='G' &&  grid[i][j+change_factor]=='G'){
				set< pair<int,int> > tmp;
				for(int k=1;k<=change_factor;k++){
					tmp.insert({i-k,j});
					tmp.insert({i+k,j});
					tmp.insert({i,j-k});
					tmp.insert({i,j+k});
				}
				tmp.insert({i,j});
				pluses.insert({max_area,tmp});
				max_area+=4;
				change_factor++;
			}
			else
				break;
		}
	}
	vector< vector<int> > non_overlappings;
	non_overlappings.resize(pluses.size());

	for(auto it=pluses.begin();it!=pluses.end();it++){
		int i=distance(pluses.begin(),it);
		for(auto jit=pluses.begin();jit!=pluses.end();jit++){
			if(jit==it)
				continue;
			set< pair<int,int> > current_cells = (*it).second;
			set< pair<int,int> > old_cells = (*jit).second;
			vector<pair<int,int> > intersection;
			set_intersection(current_cells.begin(),current_cells.end(),old_cells.begin(),old_cells.end(),
						back_inserter(intersection));
			if(intersection.size()==0){
				int j=distance(pluses.begin(),jit);
				non_overlappings[i].push_back(j);
			}
		}
	}

	int max_area=INT_MIN;
	for(int i=0;i<non_overlappings.size();i++){
		
		auto k = pluses.begin();
		advance(k,i);
		int result=(*k).first;
		if(result>max_area)
			max_area=result;		
		for(auto j: non_overlappings[i]){
		   //cout<<"Non_overlappings of "<<i<<": "<<j<<endl;
			auto it=pluses.begin();
			advance(it,j);
			int check_result = result * (*it).first;
			if(check_result>max_area)
				max_area=check_result;	
		}
	}

	if(max_area>0)
		cout<<max_area<<endl;
	else
		cout<<1<<endl;
	
	auto end = get_time::now();
	auto differ = end - start;
	//cout<<"Elapsed time is :  "<< chrono::duration_cast<ns>(differ).count()<<" ns "<<endl;
    return 0;
}

