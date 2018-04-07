#include "StackException.h"
const int MAX_STACK = 200; //can be anything, just declares the max_stack variable

template <class T>
class Stack {
	public:
		//Since this is a static array-based implementation of the Stack ADT; Copy constructor,Assignment Operator and Destructors are supplide by  the compiler
		Stack();
		bool isEmpty() const;
		void push(const T& newItem);
		void pop();
		void topAndPop(T& stackTop); //retrieves and removes the top of the stack.
		void getTop(T& stackTop) const;
	private:
		T items[MAX_STACK];
		int top;//index to top of the stack
};

template <class T>
Stack<T>::Stack(): top(-1){}//This is the default constructor

template <class T>
bool Stack<T>::isEmpty()
{
	return top<0;
}

template <class T>
void Stack<T>::push(const T& newItem){
	if(top >=MAX_STACK-1)
		throw StackException("StackException : stack full on push");
	else
		items[++top] = newItem; //newItem is added to the top and top is incremented
}

template <class T>
void Stack<T>::pop() {
	if(isEmpty())
		throw StackException("StackException: stack empty on pop");
	else
		--top;
}

template <class T>
void Stack<T>::topAndPop(T& stackTop) {
	if(isEmpty())
		throw StackException("StackException: stack empty on pop");
	else
		stackTop = items[top--];
}

template <class T>
void Stack<T>::getTop(T& stackTop)
{
	if(isEmpty())
		throw StackException("StackException: stack empty on getTop");
	else
		stackTop = items[top];
}
