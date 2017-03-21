#ifndef _STACK_H_
#define _STACK_H_

#include <iostream>
#include <cstddef>
#include <stdexcept>

using namespace std;

template <class T> 
class Stack {

    private:
        /* array keeping the items of the stack */
        T* items;
        /* number of items in the stack */
        size_t size;
        /* capacity of the stack */
        size_t capacity;

        /*** You can add other private members ***/

    public:
        /*** Do not modify the interface ***/

        /* Creates a stack of given "capacity" 
           defult is 8 items
           */
        Stack(int capacity=8);

        /* Copy constructor, Assignment operator, Destructor*/
        Stack(const Stack<T>& stack);
        Stack<T>& operator=(const Stack<T>& stack);
        ~Stack();

        /* pushes the "item" to the top of the stack 
           increases the capacity as needed
           doubles the capacity when full
           */
        void push(const T& item);
        /* pops the item at the top of the stack and returns 
           decreases the capacity when needed
           halves the capacity when less then 1/3 full
           */
        T pop();
        /* returns the item at the top of the stack witout modifiying the stack 
           (take a look at the top item) 
           */
        const T& top() const;
        /* clears the contents of the stack */
        void clear();
        /* returns true if the stack is empty, false otherwise */
        bool isEmpty() const;
        /* returns the number of items in the stack */
        size_t getSize() const;
        /* returns the capacity the stack */
        size_t getCapacity() const;
        /* prints the contents of the stack 
           from top to bottom, one item per line
           assumes the objects in the stack have operator<< overloaded 
           */
        void print() const;
        /* prints the contents of the stack 
           from bottom to top, one item per line
           assumes the objects in the stack have operator<< overloaded 
           */
        void printReversed() const;

        /*** Do not modify the interface ***/
};


/* TO-DO: method implementations here */
template <class T>
Stack<T>::Stack(int cp)
{
    if(cp<=0)
        throw string("Exception:Stack's capacity must be positive");
    else
    {
        items = new T[cp];
        size = 0;
        capacity = cp;
    }
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& stack)
{
  if(this == &stack) return *this;
    capacity = stack.getCapacity();
    items = new T[capacity];
    size=0;
    while(size<stack.getSize())
    {
      push(stack.items[size]);
    }
    
    return *this;
}
template <class T>
Stack<T>::Stack(const Stack<T>& stack)
{
  *this = stack;
}
template <class T>
Stack<T>::~Stack<T>()
{
  if(!isEmpty())
    clear();
  delete[] items;
}

template <class T>
bool Stack<T>::isEmpty() const
{
  if(getSize()<=0)
    return true;
  else
    return false;
}

template <class T>
void Stack<T>::clear()
{
  //delete [] items;
  items = new T[8];
  capacity = 8;
  size = 0;
  
}

template <class T>
size_t Stack<T>::getSize() const
{
  return size;
}

template <class T>
size_t Stack<T>::getCapacity() const
{
  return capacity;
}

template <class T>
void Stack<T>::print() const
{
  if(!isEmpty())
  {
    for(size_t tmp=getSize();tmp>0;tmp--)
    {
      cout<<items[tmp-1]<<endl;
    }
  }
}

template <class T>
void Stack<T>::printReversed() const
{
    if(!isEmpty())
    {
        for(size_t i=0;i<getSize();i++)
        {
            cout<<items[i]<<endl;
        }
    }
}

template <class T>
void Stack<T>::push(const T& item)
{
  
  if(size==capacity)
  {
    T* newItems;
    
    newItems = new T[capacity*2];
    size_t i=0;
    
    for(;i<size;i++)
      newItems[i]=items[i];
    
    capacity=capacity*2;
    delete[] items;
    items = new T[capacity];
        for(size_t j=0;j<size;j++)
            items[j]=newItems[j];
        items[size]=item;
        size++;
    delete[] newItems;
  }
  else
  {
    items[size++]=item;
  }
  
}
template <class T>
T Stack<T>::pop()
{
  if(!isEmpty())
  {
	if((size*3) < capacity)
  	{
  	  if(capacity/2 >= 8) 
  	    capacity/=2;
  	}
  	T* newItems;
  	newItems = new T[capacity];
  	size_t i=0;
  	for(;i<size;i++)
  	  newItems[i]=items[i];
  	delete [] items;
  	items = new T[capacity];
    for(size_t j=0;j<size;j++)
  	  items[j]=newItems[j];
  	delete[] newItems;  
  	size_t hold = size-1;
  	size--;
  	return items[hold];
  } 
  else
	throw "stack is empty";
}

template <class T>
const T& Stack<T>::top() const
{
	if(!isEmpty())
  		return items[size-1];
}
#endif
