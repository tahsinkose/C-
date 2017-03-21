#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include "Node.hpp"

using namespace std;

template <class T> 
class LinkedList {
    private:
        
        /* pointer to the first node */
        Node<T>* front;
        /* pointer to the last node */
        Node<T>* back;

        size_t size;//in order to count the size of the linked list.

    public:
        /*** Do not modify the interface ***/

        LinkedList();
        LinkedList(const LinkedList<T>& ll);
        LinkedList<T>& operator=(const LinkedList<T>& ll);
        ~LinkedList();

        /* returns the first node of the linked list */
        Node<T>& getFront() const;
        /* returns the last node of the linked list */
        Node<T>& getBack() const;
        /* returns the node in given "pos"ition of the linked list */
        Node<T>& getNodeAt(int pos) const;
        /* returns the pointer of the node in given 
           "pos"ition of the linked list */
        Node<T>* getNodePtrAt(int pos) const;
        
        /* inserts a new node containing "data" 
           after the node "prev" 
           */
        void insert(Node<T>* prev, const T& data);
        /* inserts a new node containing "data" 
           at "pos"ition in the linked list 
           */
        void insertAt(int pos, const T& data);
        /* erases the given "node" from the linked list */
        void erase(Node<T>* node);
        /* erases the node in given "pos"ition from the linked list */
        void eraseFrom(int pos);
        /* clears the contents of the linked list */
        void clear();

        /* inserts a new node containing "data" 
           to the front of the linked list 
           */
        void pushFront(const T& data);
        /* inserts a new node containing "data" 
           to the back of the linked list
           */
        void pushBack(const T& data);

        /* removes the first node */
        void popFront();
        /* removes the last node */
        void popBack();

        /* returns true if the list is empty, false otherwise */
        bool isEmpty() const;
        /* returns the number of items in the list */
        size_t getSize() const;
        /* prints the contents of the linked list 
           one node data per line
           assumes the objects in the node have operator<< overloaded 
           */
        void print() const;
		void printReverse(Node<T>* head);
		void foo(Node<T>* head);
        /*** Do not modify the interface ***/
};

/* TO-DO: method implementations here */
template <class T>
LinkedList<T>::LinkedList()
{
  front = NULL;
  back = NULL;
  size=0;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& ll)
{
  if(this!=&ll)
  {

    clear();
    const Node<T>* p = &ll.getFront();
    insert(NULL,p->getData());
    Node<T>* r = front;
    p=p->getNext();
    while(p)
    {
      insert(r,p->getData());
      r = r->getNext();
      p = p->getNext();
    }
  }//end if
  return *this;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& ll) 
{
  front = NULL;
  back = NULL;
  size=0;
  *this = ll;//use overloaded assignment operator
}



template<class T>
size_t LinkedList<T>::getSize() const
{
  return size; 
}

template<class T>
bool LinkedList<T>::isEmpty() const
{
  return front==NULL;
}

template<class T>
Node<T>& LinkedList<T>::getFront() const
{
  if(front!=NULL)
    return *front;
  else
    throw "front node is NULL";
}

template<class T>
Node<T>& LinkedList<T>::getBack() const
{
    return *back;
}

template<class T>
Node<T>& LinkedList<T>::getNodeAt(int pos) const
{
  Node<T>* p = front;
  if(pos>=0 && pos<size)
  {
    size_t i= (size_t) pos;
    size_t j=0;
    while(j<i)
    {  
      p = p->getNext();
      j++;
    }
    return *p;
  }
  else
    throw "invalid index";
}

template<class T>
Node<T>* LinkedList<T>::getNodePtrAt(int pos) const
{
  Node<T>* p = front;
  if(pos>=0 && pos<size)
  {
    size_t i =(size_t) pos;
    size_t j=0;
    while(j<i)
    {
      p = p->getNext();
      j++;
    }
    return p;
  }
  else
    throw "invalid index";
}
template<class T>
void LinkedList<T>::print() const
{
  const Node<T>* p = front;
  size_t i=0;
  while(i<getSize())
  {
    cout<<p->getData()<<endl;
    p=p->getNext();
    i++;
  }
}

template <class T>
void LinkedList<T>::clear()
{
  while(!isEmpty())
  {
    popFront();
  }
  
}

template <class T>
void LinkedList<T>::popFront()
{
  //front will be deleted
  if(front!=NULL)
  {
    if(size==1)
    {
      Node<T>* tmp = front->getNext();
      front = tmp;
      back = NULL;
    }//end if
    else
    {
      Node<T>* tmp = front->getNext();
      tmp->setPrev(NULL);
      front = tmp;  
    }
    size--;
  }
  else
    throw "no front not to be popped";
}

template<class T>
void LinkedList<T>::popBack()
{
  if(front!=NULL && back!= NULL)
  {
    if(back->getPrev()==NULL)
    {
      Node<T>* tmp = back;
      back = tmp->getPrev();
      front = NULL;
      delete tmp;
    }
    else
    {
      Node<T>* tmp = back;
      back = tmp->getPrev();
      back->setNext(NULL);
      delete tmp;
    }
    size--;
  }//end if
  else
    throw "no back node to be popped";
}//end popback

template<class T>
void LinkedList<T>::eraseFrom(int pos)
{
    if(pos<0)
      throw "invalid index";
    else if(pos>=0 && pos<size)
    {
      Node<T>* p = front;
      size_t i = (size_t) pos;
      size_t j = 0;
      while(j<i)
      {  p = p->getNext(); j++;}
      Node<T>* tmp = p->getNext();
 if(tmp!=NULL)
      {
        tmp->setPrev(p->getPrev());
        if(pos==0)
                front = tmp;
      }
      if(p->getPrev()!=NULL)
      {
        p->getPrev()->setNext(tmp);
        if(pos==size-1)
                back = p->getPrev();
      }
      size--;
      delete p;
    }
    else
      throw "invalid index";
}

template <class T>
void LinkedList<T>::erase(Node<T> * node)
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

template<class T>
void LinkedList<T>::pushBack(const T& data)
{
    insert(back,data);
}

template<class T>
void LinkedList<T>::pushFront(const T& data)
{
    insertAt(0,data);
}


template<class T>
void LinkedList<T>::insert(Node<T>* prev, const T& data)
{
    if(getSize()==0)
    {
      
      front = new Node<T>(data);
      back = front;
    }
    else
    {
       Node<T>* newNode = new Node<T>(data);
      if(prev->getNext()==NULL && prev->getPrev()==NULL)//this means there is only one node
      {
       prev->setPrev(NULL);
       prev->setNext(newNode);
       newNode->setPrev(prev);
       newNode->setNext(NULL);
       back = newNode;
      }
      else if(prev->getNext()==NULL && prev->getPrev()!=NULL) // back case
      {
       prev->setNext(newNode);
       newNode->setPrev(prev);
       newNode->setNext(NULL);
       back = newNode;
      }
      else if(prev->getPrev()==NULL && prev->getNext()!=NULL)// front case
      {
         Node<T>* tmp_next = prev->getNext();
         prev->setNext(newNode);
         tmp_next->setPrev(newNode);
         newNode->setNext(tmp_next);
         newNode->setPrev(prev);
      }
      else // middle case
      {
          Node<T>* tmp_next = prev->getNext();
          prev->setNext(newNode);
          tmp_next->setPrev(newNode);
          newNode->setNext(tmp_next);
          newNode->setPrev(prev);
      }
    }
    size++;
}
template<class T>
void LinkedList<T>::foo(Node<T>* head)
{
	Node<T> * p = head;
	if(p)
	{
		if(p->getNext())
			foo(p->getNext());
		cout<<p->getData()<<"->";
	}
	else
	{
		cout<<endl;
	}	
}
template<class T>
void LinkedList<T>::printReverse(Node<T>* head)
{
	foo(head);
	cout<<endl;
}
template<class T>
void LinkedList<T>::insertAt( int pos, const T& data)
{
  if(pos<0)
    throw "invalid index";
  else if(pos>=0 && pos<=size)//if it is equal to the size, then it becomes a last node
  {
    Node<T>* p = front;
    size_t i =(size_t) pos;
    size_t j=0;
    if(i==0)
    {
      if(getSize()==0)
      {
        //cout<<"There is no node : "<<data<<endl;
        front = new Node<T>(data);
        back = front;
        size++; 
      }
      else
      {
        //cout<<"I'm here on data entry : "<<data<<endl;
        
        Node<T>* tmp = new Node<T>();
        //cout<<"The former front value is : "<<p->getData()<<endl;
        tmp->setPrev(NULL);
        tmp->setNext(p);
        tmp->setData(data);
        p->setPrev(tmp);
        front = tmp;
        size++;
        //cout<<"The new front value is : "<<front->getData()<<endl;
      }//end else
    }
    else
    {
     while(j<i-1)
      {
        p = p->getNext();
        j++;
      }
      insert(p,data);
    }
  }
  else
    throw "invalid index";
  
  
}
template<class T>
LinkedList<T>::~LinkedList()
{
  //cout<<"Destructor in action"<<endl;
  clear();
  delete front;
  delete back;
}
#endif
