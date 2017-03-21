#include "StackL.hpp"


int main()
{
	Stack<int> s;
	
	
	for(int i = 0; i<10;i++)
		s.push(i);
	
		Stack<int> s2 = s;// test copy constructor also tests assignment
	std::cout<<"Printing s1:"<<std::endl;
	while(!s.isEmpty()) 
	{
		int value;
		s.topAndPop(value);
		std::cout <<value <<std::endl;
	}	

		std::cout << "Printing s2:"<<std::endl;
	while(!s2.isEmpty())
	{
		int value;
		s2.topAndPop(value);
		std::cout<<value<<std::endl;
	}
	
	
	return 0;
}

