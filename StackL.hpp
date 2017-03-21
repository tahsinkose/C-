#include "StackException.h"
#include "List.hpp"

template <class T>
class Stack{
	public:
		Stack(int l);
		bool isEmpty() const;
		void push(const T& newItem);
		void pop();
		void getTop(T& stackTop) const;
		void topAndPop(T& stackTop);
	
	private:
		List<T> stackList;
};

template<class T>
Stack<T>::Stack(int l)
{
}
template<class T>
void Stack<T>::push(const T& data)
{	
	stackList.insert(data, stackList.zeroth());
}

template<class T>
void Stack<T>::topAndPop(T& stackTop)
{
	if(isEmpty())
		throw  "Exception:Stack is empty";
	else	
	{
		stackTop = stackList.first()->element;
		stackList.remove(stackList.first()->element);		
	}
}
template<class T>
void Stack<T>::getTop(T& stackTop) const
{
	if (isEmpty())
		throw "Exception:Stack is empty";
	stackTop = stackList.first()->element;
}

template<class T>	
void Stack<T>::pop()
{
	if (isEmpty())
		throw "Exception:Stack is empty";
	stackList.remove((stackList.first())->element);
}
template<class T>
bool Stack<T>::isEmpty() const
{
	return stackList.isEmpty();
}
