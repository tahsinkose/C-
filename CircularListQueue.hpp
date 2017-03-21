template <class T>
class Queue {	
	public:
		Queue();
		Queue(const Queue& rhs);
		~Queue();
		Queue& operator=(const Queue& rhs);

		bool isEmpty() const;
		void enqueue(const T& newItem);
		void dequeue();
		void dequeue(T& queueFront);
		void getFront(T& queueFront) const;

	private:
		//The queue is implemented as a linked list with one external pointer 
		//to the front of the queue and a second external pointer to the back 
		//of the queue.
		template<class S>
		struct QueueNode
		{
			S item;
			QueueNode *next;
		};
		QueueNode<T> *backPtr;
		
};

template<class T>
Queue<T>::Queue():backPtr(NULL) {}

template<class T>
Queue<T>::~Queue(){
	while(!isEmpty())
		dequeue();
}

template<class T>
bool Queue<T>::isEmpty() const{
	return backPtr == NULL;
}

template<class T>
void Queue<T>::enqueue(const T& newItem)
{
	//create a new node
	QueueNode *newPtr = new QueueNode; 
	
	//set data portion of new node
	newPtr->item = newItem;
	

	//insert the new node
	if(isEmpty())//insertion into empty queue
	{
		backPtr = newPtr;
		backPtr->next = backPtr;
	}
	else //insertion into nonempty queue
	{
		newPtr->next = backPtr->next;//set newNode's next to backPtr's next(which is to the front of the queue actually)
		backPtr->next = newPtr; // set former backPtr's next to newNode.
		backPtr = newPtr;
	}
}

template<class T>
void Queue<T>::dequeue()
{
	if(isEmpty())
		throw ("QueueException: empty queue,cannot dequeue");
	else 
	{ //queue is not empty;remove front
		QueueNode *tempPtr = backPtr->next;
		if(backPtr == backPtr->next) { //one node in queue
			backPtr = NULL;
		}
		else
			backPtr->next = backPtr->next->next;
		tempPtr->next = NULL; //optional defensive strategy
		delete tempPtr;
	}
}

template<class T>
void Queue<T>::dequeue(T& queueFront)
{
	if(isEmpty())
		throw("QueueException: empty queue,cannot dequeue");
	else
	{
		queueFront = backPtr->next->item;
		dequeue(); //delete front
	}
}

template<class T>
void Queue<T>::getFront(T& queueFront)
{
	if(isEmpty())
		throw("QueueException: empty queue,cannot dequeue");
	else
		queueFront = backPtr->next->item;
}
