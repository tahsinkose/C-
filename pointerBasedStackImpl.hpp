#ifndef _PointerStackImpl_hpp_
#define _PointerStackImpl_hpp_

#include "StackNode.hpp"
#include "StackException.h"
#include <iostream>
template <class T>
class Stack {
	public:
		Stack();
		Stack(const Stack& rhs);
		~Stack();
		Stack& operator=(const Stack& rhs);
		bool isEmpty() const;
		void push(const T& newItem);
		void pop();
		void topAndPop(T& stackTop);
		void getTop(T& stackTop) const;
	private:
		StackNode<T> *topPtr;
};

template <class T>
Stack<T>::Stack():	topPtr(NULL) {} // default constructor

template <class T>
bool Stack<T>::isEmpty() const {
	return topPtr == NULL;
}

template <class T>
void Stack<T>::push(const T& newItem)
{
	StackNode<T> *newPtr = new StackNode<T>();
	newPtr->item = newItem;
	newPtr->next = topPtr;
	topPtr = newPtr;
}

template <class T>
void Stack<T>::pop()
{
	
	if(isEmpty())
		throw StackException("StackException: stack empty on pop");
	else
	{
		StackNode<T> *tmp = topPtr;
		topPtr = topPtr->next;
		delete tmp;
	}
		
	
}

template <class T>
void Stack<T>::topAndPop(T& stackTop)
{
	if(isEmpty())
		throw StackException("StackException: stack empty on topAndpop");
	else
	{
		stackTop = topPtr->item; // value to give back
		StackNode<T> *tmp = topPtr;
		topPtr = topPtr->next;// update the stack top
		delete tmp;
	}
}

template <class T>
void Stack<T>::getTop(T& stackTop) const
{
	if(isEmpty())
		throw StackException("StackException: stack empty on getTop");
	else
		stackTop = topPtr->item; // value to give back
}

template <class T>
Stack<T>::~Stack()
{
	while(!isEmpty())
		pop();
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack& rhs)
{
	if(this != &rhs)
	{
		if(!rhs.topPtr)
		{	topPtr = NULL;
			std::cout<<"right hand side stack seems empty"<<std::endl;}
		else {
			std::cout<<"rhs stack is not empty"<<std::endl;
				topPtr = new StackNode<T>();
				topPtr->item = rhs.topPtr->item;
				StackNode<T>* q = rhs.topPtr->next;
				StackNode<T>* p = topPtr;
				while(q) {
					p->next = new StackNode<T>();
					p->next->item = q->item;
					p = p->next;
					q = q->next;
				}
				p->next = NULL;
		}
	}
	return *this;
}

template <class T>
Stack<T>::Stack(const Stack& rhs)
{
	*this = rhs;
}

#endif
