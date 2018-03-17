#include <iostream>
#include <string>
#include <cmath>
unsigned long long int find_max_cab(unsigned long long int ull);
using namespace std;

int main()
{
	int i,tests;
	unsigned long long int input,result;
	cin>>tests;
	for(i=0;i < tests;i++)
	{
		cin>>input;
		//cout<<input<<endl;
		result = find_max_cab(input);
		cout<<result<<endl;
	}
	return 0;
}

unsigned long long int find_max_cab(unsigned long long int ull)
{
	
	
	ull= ull - 7;
	if(ull%6==0)
		return ull/6;
	else
		return (ull/6)+1;
	
	
}


