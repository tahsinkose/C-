#ifndef _TAB_H_
#define _TAB_H_

#include <iostream>
#include <string>
#include "Stack.hpp"

using namespace std;

class Tab{

    private:
        string page;
        size_t page_size;

    public:
		Stack<string> prevPages;
		Stack<string> nextPages;
    	Tab();
    	Tab(string p);
    	/* GETTERS*/
    	string getPage() const;
    	size_t getSize() const;
    	/* SETTERS*/
    	void setPage(string p);
	
    	void add_prevPages(string link);
		void add_nextPages(string link);

};

#endif
