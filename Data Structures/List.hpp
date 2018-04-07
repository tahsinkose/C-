#ifndef _List_hpp_
#define _List_hpp_
#include <string>
#include "Node.hpp"
#include <iostream>
template <class T>
class List
{
        private: 
                Node<T> *dummyHead;
        public:
		 		List(){ dummyHead = new Node<T>(T(),NULL);}
			 	List& operator=(const List& rhs);
                List(const List& rhs);
                Node<T> *zeroth(){
						
                        return dummyHead;
                }
                Node<T>* first() const {
                        return dummyHead->next;
                }
                bool isEmpty() const {return first()==NULL;}
                /*Since isEmpty is a const function which does not evaluates
                /*the data in the called function, first must be a const too.
                */
				void insert(const T& data, Node<T>* p);
                Node<T>* find(const T& data);   
                Node<T>* findPrevious(const T& data);
                void remove(const T& data);
				void erase(Node<T>* node);
                void print() const;
                void makeEmpty();
                ~List();
                

};	

/*This newer method comprises a more optimized algorithm, however the linked
/*should have a dummy head*/
template <class T>
void List<T>::insert(const T& data, Node<T>* p)
{
	//Since p never be NULL, there is only 1 case.
		Node<T>* newNode = new Node<T>(data,p->next);
		p->next = newNode;
	
}



template <class T>
Node<T>* List<T>::find(const T& data)
{
	Node<T>* p = first();//is first contains the first node after dummy
	while(p)//not equal to null
	{
		if(p->element == data)
			return p;
		p= p->next;
	}
	return NULL;
}

template <class T>
Node<T>* List<T>::findPrevious(const T& data)
{
	Node<T>* p = zeroth();
	while(p->next)//while node pointed by p is not the last one
	{
		if(p->next->element==data)
			return p;
		p = p->next;
	}
	return NULL;
}

template <class T>
void List<T>::remove(const T& data)
{
	Node<T>* p = findPrevious(data);
	if(p) 
	{
		Node<T>* tmp = p->next; // address of the node to delete
		p->next = tmp->next; //bounds previous node with the next after the to-be-deleted one
		delete tmp;
	}
}

template <class T>
void List<T>::print() const
{
	const Node<T>* p= first();
	
	while(p)
	{
		std::cout <<p->element<< std::endl;
		p= p->next;
	}
}

template <class T>
void List<T>::makeEmpty()
{
		
	while(!isEmpty())
	{
		remove(first()->element);
	}
}
template <class T>
void List<T>::erase(Node<T> * node)
{
  if(node==NULL)
    throw exception();
  else
  {
    Node<T>* p=front;
    while(p!=node)
      p=p->getNext();// in order to find p
    Node<T>* tmp = p->getNext();
    /*if(tmp!=NULL)
    { */ tmp->setPrev(p->getPrev());
    /*if(p->getPrev()!=NULL)
    {*/  p->getPrev()->setNext(tmp);
    size--;
    delete p;
  }
}

template <class T>
List<T>::~List()
{
	makeEmpty();
	delete dummyHead;
}

//ASSIGNMENT OPERATOR OVERLOADING
template <class T>
List<T>& List<T>::operator=(const List& rhs){
	if(this != &rhs)
	{
		makeEmpty(); // clear the former content

		const Node<T>* r = rhs.first();// r = the zeroth of rhs
		
		Node<T>* p = zeroth();//p starts from the first of lhs
		
		while(r) {
			
			insert(r->element,p);
			r = r->next;
			p = p->next;
		}
	}
	return *this;
}

//COPY CONSTRUCTOR
template <class T>
List<T>::List(const List & rhs)
{
	dummyHead = new Node<T>(T(),NULL);//dummy is created
	*this = rhs; //Since we already overloaded to assignmoperator.
	 	     //It performs a deep copy, not a shallow o.
}
#endif
