const int MAX_QUEUE = 10;
template <class T>
class Queue {
	public:	
		Queue(); //default constructor
		bool isEmpty() const;
		void enqueue(QueueItemType newItem);
		void dequeue();
		void dequeue(QueueItemType& queueFront);
		void getFront(QueueItemType& queueFront);
	private:
		T items[MAX_QUEUE];
		int front;
		int back;
		bool isFull;
};

template <class T>
Queue<T>::Queue():front(0),back(MAX_QUEUE-1),isFull(false) {}

template <class T>
bool Queue<T>::isEmpty() const {
	return isFull==false && ((back+1) % MAX_QUEUE) == front; 
	//check for it is not full and does not contain any item. 
	//if front is one bigger than the back, 
	//it means queue does not contain any item
}

template <class T>
void Queue<T>::enqueue(QueueItemType newItem){
	if(isFull)
		throw "QueueException: queue full on enqueue";
	else { //queue is not full;insert item
		back = (back+1) % MAX_QUEUE;
		items[back] = newItem;
		if((back+1) % MAX_QUEUE == front) isFull = true;
	}
}

template<class T>
void Queue<T>::dequeue(){
	if(isEmpty())
		throw "QueueException: empty queue cannot dequeue";
	else {
		front = (front+1) % MAX_QUEUE;
		isFull = false;
	}
}

template<class T>
void Queue<T>::dequeue(T& queueFront){
	if(isEmpty())
		throw "QueueException: empty queue, cannot dequeue";
	else //	queue is not empty; retrieve and remove front
	{
		queueFront = items[front];
		front = (front+1) % MAX_QUEUE;
		isFull = false;
	}	
}	

template <class T>
void Queue<T>::getFront(T& queueFront) const{
	if(isEmpty())
		throw "QueueException: empty queue,cannot getFront";
	else //queue is not empty;retrieve front
	{
		queueFront = items[front];
		isFull = false;
}	
