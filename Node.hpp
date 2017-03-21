/*This is a node implementation*/
template <class T>
class Node {
	public:
	Node(const T& e = T(), Node *n=NULL): element (e), next(n) {}
	
	T element;
	Node *next;
};
