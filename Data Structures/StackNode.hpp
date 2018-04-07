#include <stddef.h>
template <class Object>
class StackNode {
	public:
		StackNode(const Object& e = Object(), StackNode* n = NULL) : item(e),next(n) {}
		Object item;
		StackNode* next;
};
	
