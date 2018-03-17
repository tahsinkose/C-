#include <iostream>
#include <vector>
#include <climits>

using namespace std;


int main(){
	int n;
	cin>>n;
	vector<int> time_to_solve(n);
	int max_time_needed = 0;
	for(int i=0;i<n;i++){
		cin>>time_to_solve[i];
		max_time_needed += time_to_solve[i];
	}
	
	int m;
	cin>>m;
	vector<int> start(m);
	vector<int> end(m);

	int max_possible_time=0;	
	bool found = false;
	for(int i=0;i<m;i++){
		cin>>start[i]>>end[i];
		if(!found){
			if(max_time_needed > start[i] && max_time_needed > end[i])
				continue;
			else if(start[i] <= max_time_needed && end[i] >= max_time_needed){
				max_possible_time = max_time_needed;
				found = true;
			}
			else if(start[i] > max_time_needed){
				max_possible_time = start[i];
				found = true;
			}
		}
	}		
	
	if(max_time_needed > end[m-1] || max_possible_time==0)
		cout<<-1<<endl;
	else
		cout<<max_possible_time<<endl;
	
	return 0;
}