#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
bool isPalindrome(string& s){
	string reverted = s;
	reverse(reverted.begin(),reverted.end());
	return s==reverted;
}

int main(){
	string s;
	cin>>s;
	if(isPalindrome(s))
		cout<<s<<endl;
	else{
		string reverted = s;
		reverse(reverted.begin(),reverted.end());
		s.append(reverted);
		cout<<s<<endl;
	}
	