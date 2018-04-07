#include "StackException.h"

template <class T>
class Stack {
	public:
		//In this case we need to implement copy constructor, assignment operator and destructor
		Stack();
		Stack(const Stack& rhs);
		Stack& operator=(const Stack& rhs);
		bool isEmpty() const;
		void push(const T& newItem);
		void pop();
		void topAndPop(T& stackTop); //retrieves and removes the top of the stack.
		void getTop(T& stackTop) const;
		~Stack();
	private:
		T* items;
		int top;//index to top of the stack
};

template <class T>
Stack<T>::Stack(): top(-1){}//This is the default constructor

Stack<T>& Stack<T>::operator=(const Stack& rhs)
{
	if(this != rhs)
	{
		while(!isEmpty())
		{
			pop();
		}
		int tmp = rhs.top;
		while(top<=rhs.top)
		{
			push(rhs.items[tmp]);
			top++;
			tmp++;
		}
	}
	return *this;
}

Stack<T>::Stack(const Stack& rhs)
{
	newItems = new Stack<T>();
	*this = rhs;
}
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
void Stack<T>::~Stack()
{
	while(!isEmpty())
	{
		pop();
	}
}
