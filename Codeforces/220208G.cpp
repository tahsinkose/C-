//This is an intensely compact code. It basically considers all possible moves in the pile in an accumulated manner, i.e if there are 4 stones in a particular pile, then moves that remove 1 and 2 piles are considered valid. As a result, their nim sum (XOR) is calculated.
#include <iostream>

using namespace std;

typedef unsigned long long int ull;

int mex[100]; //minimal excluded array
int main(){
	int n,ind=0;
	ull result=0;
	mex[0]=0;
	for(int i=1;i<=10;i++)
		for(int j=1;j<=i+1;j++)
			mex[++ind] = i;
	cin>>n;
	for(int i=0;i<n;i++){
		int num;
		cin>>num;
		result ^= mex[num];
	}
	if(result)//That means first player wins. In our case LOSS
		cout<<"NO"<<endl;
	else
		cout<<"YES"<<endl;
	
	return 0;
}
