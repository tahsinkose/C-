#include <fstream>

#include "List.hpp"
#include "pointerBasedQueue.hpp"
using namespace std;
int main(int argc, char *argv[]){    

    List<string> anEventList;
	Queue<string> bankQueue;
    ifstream data(argv[1]);
    for (string line; getline(data, line); ){    
		cout << ">>> " << line << endl;
		string delimiter="\t";
		size_t location = line.find(delimiter);
		
		if(location!=std::string::npos)
		{
			string arrivalEvent = line.substr(0,location);
			string rest = line.substr(location+1,line.length());
			arrivalEvent = "A "+arrivalEvent;
			cout<<"1: "<<arrivalEvent<<endl;
			anEventList.insert(arrivalEvent,anEventList.zeroth());
			string takenEvent = anEventList.first()->element;
			cout<<"2: "<<takenEvent<<endl;
			takenEvent = takenEvent.substr(2,takenEvent.length());
			cout<<"3: "<<takenEvent<<endl;
			bankQueue.enqueue(takenEvent);
		}
	}
    data.close();
    return 0;
}
