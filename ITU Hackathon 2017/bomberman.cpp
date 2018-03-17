#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
using namespace std;


int main() {
    int R,C,N;
    cin>>R>>C>>N;
    vector<string> grid(R);
	set<pair<int,int> > initial_bombs;
	set<pair<int,int> > bombs;
	set<pair<int,int> > complement_empties;
    for(int i=0;i<R;i++){
        cin>>grid[i];
		for(int j=0;j<C;j++){
			if(grid[i][j]==79)
				initial_bombs.insert({i,j});
			bombs.insert({i,j});
		}
	}
	if(N==1)
		for(int i=0;i<R;i++)
			cout<<grid[i]<<endl;
	for(auto bomb : initial_bombs){
		int i=bomb.first;
		int j=bomb.second;
		bombs.erase({i,j});
		if(j-1>=0)
			bombs.erase({i,j-1});
		if(j+1<C)
			bombs.erase({i,j+1});
		if(i-1>=0)
			bombs.erase({i-1,j});
		if(i+1<R)
			bombs.erase({i+1,j});
	}

	for(auto bomb : bombs){
		int i=bomb.first;
		int j=bomb.second;
		complement_empties.insert({i,j});
		if(j-1>=0)
			complement_empties.insert({i,j-1});
		if(j+1<C)
			complement_empties.insert({i,j+1});
		if(i-1>=0)
			complement_empties.insert({i-1,j});
		if(i+1<R)
			complement_empties.insert({i+1,j});
	}
	
	
	if(N%2==0){
		for(int i=0;i<R;i++){
			for(int j=0;j<C;j++)
				cout<<'O';
			cout<<endl;
		}
		return 0;
	}
	else{
		if((N-3)%4==0){
			for(int i=0;i<R;i++)
				for(int j=0;j<C;j++)
					grid[i][j]='.';
			for(auto bomb : bombs){
				int ii=bomb.first;
				int jj=bomb.second;
				grid[ii][jj]=79;
			}
		}
		else{
			for(int i=0;i<R;i++)
				for(int j=0;j<C;j++)
					grid[i][j]=79;
			for(auto empty : complement_empties){
				int ii=empty.first;
				int jj=empty.second;
				grid[ii][jj]='.';
			}
		}
	}
	for(int i=0;i<R;i++)
		cout<<grid[i]<<endl;
    return 0;
}

