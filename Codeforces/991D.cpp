#include <iostream>
#include <string>

using namespace std;

int main(){
	string a,b;
	cin>>a;
	cin>>b;
	int count = 0;
	for(int i=0;i<a.size();i++){
		if(a[i]=='0' && b[i]=='0'){
			if(i-1>=0){
				if(a[i-1]=='0'){
					count++;
					a[i]='X', b[i]='X', a[i-1]='X';
					continue;	
				}
				else if(b[i-1]=='0'){
					count++;
					a[i]='X', b[i]='X', b[i-1]='X';
					continue;
				}
			}
			if(i+1<a.size()){
				if(a[i+1]=='0'){
					count++;
					a[i]='X', b[i]='X', a[i+1]='X';
				}
				else if(b[i+1]=='0'){
					count++;
					a[i]='X', b[i]='X', b[i+1]='X';
				}
			}
		}
	}
	cout<<count<<endl;
	return 0;
}