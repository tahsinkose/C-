#include <iostream>
#include "Stack.h"

using namespace std;

int main()
{

	Stack<char> myStack(100);

	char c;

	cout<<"Start entering text: ";

	cin >> c;

	while (c != '.'){ 
		 myStack.push(c);
		 cin >> c;
		}

	cout<<"Reverse: ";

	while(!myStack.isEmpty()){
		cout << myStack.getTop();
		myStack.pop();
	}

	cout<<endl;

	return 0;
}

