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
		QueueNode<T> *frontPtr;
};

template<class T>
Queue<T>::Queue():backPtr(NULL), frontPtr(NULL) {}

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
	QueueNode<T> *newPtr = new QueueNode<T>(); 
	
	//set data portion of new node
	newPtr->item = newItem;
	newPtr->next = NULL;

	//insert the new node
	if(isEmpty())//insertion into empty queue
		frontPtr= newPtr;
	else //insertion into nonempty queue
		backPtr->next = newPtr;

	backPtr = newPtr; //new node is at back.
}

template<class T>
void Queue<T>::dequeue()
{
	if(isEmpty())
		throw ("QueueException: empty queue,cannot dequeue");
	else 
	{ //queue is not empty;remove front
		QueueNode<T> *tempPtr = frontPtr;
		if(frontPtr == backPtr) { //one node in queue
			frontPtr =NULL;
			backPtr = NULL;
		}
		else
			frontPtr = frontPtr->next;
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
		queueFront = frontPtr->item;
		dequeue(); //delete front
	}
}

template<class T>
void Queue<T>::getFront(T& queueFront) const
{
	if(isEmpty())
		throw("QueueException: empty queue,cannot dequeue");
	else
		queueFront = frontPtr->item;
}
