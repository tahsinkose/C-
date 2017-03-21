#ifndef _BROWSER_H_
#define _BROWSER_H_

#include <string>
#include "LinkedList.hpp"
#include "Stack.hpp"
#include "Tab.hpp"
#include <sstream>
class Browser{

    private:
        Tab* selected;
        LinkedList<Tab> pages;
        Stack<Tab> closedPages;
        Stack<size_t> closedIndex;
        size_t selected_tab_index;
    public:

        Browser();
        void handleTask(string task);
        void open_new_page(string link);
        void open_link(string link);
        void open_link_in_new_tab(string link);
        void reopen_closed_tab();
        void close_tab(size_t index);
        void saveIndex(size_t pos);
        size_t string_to_size_t(string link);
        void move_tab(size_t from,size_t to);
        void select_tab(size_t index);
		void close_selected_tab();
		void display_tab_details();
		void back();
		void forward();
        void display();

};

#endif
