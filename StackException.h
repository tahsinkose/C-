#include <string>
class StackException {
	public:
		StackException(const std::string& err) : error(err) {}
		std::string error;
};
