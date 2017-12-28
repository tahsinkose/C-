/* Rabin-Karp Matcher */
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

bool equal(string& a,string& b,int s){
	for(int i=0;i<a.size();i++){
		if(a[i]!=b[s+i])
			return false;
	}
	return true;
}


int main(int argc,char* argv[]){

	if(argc!=3){
		cout<<"Usage "<<argv[0]<<" <file> <pattern> "<<endl;
		exit(1);
	} 

	ifstream f(argv[1]);
    stringstream buffer;
    buffer << f.rdbuf();
    
    string Text = buffer.str();
    string Pattern = argv[2];
	
	int d = 0;
	for(int i=0;i<Text.size();i++){
		if(Text[i] - '0' > d)
			d = Text[i] - '0';
	}
	d++;
	int q = d+3;	
	
	int n = Text.length();
	int m = Pattern.length();
	int h = (int)(pow(d,m-1)) % q;
	int p = 0;

	vector<int> t(n-m,0);
	for(int i=0;i<m;i++){
		p = (d*p + (Pattern[i]-'0')) % q;
		t[0] = (d*t[0] + (Text[i]-'0')) %q;
	}
	for(int s=0;s<n-m;s++){
		if(p==t[s] && equal(Pattern,Text,s))
			cout<<"Pattern occurs with shift "<<s<<endl;
		t[s+1] = (d*(t[s] - (Text[s] - '0')*h) + Text[s+m]-'0');
		t[s+1] %= q;
		if(t[s+1]<0)
			t[s+1] += q;		
	} 
	return 0;
}
