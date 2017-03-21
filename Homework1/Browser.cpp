#include "Browser.hpp"
#include <iostream>

using namespace std;
Browser::Browser()
{
	selected = NULL;
	selected_tab_index=0;
}

void Browser::handleTask(string task)
{
	string delimiter=" ";
	size_t location = task.find(delimiter);
	string op_token;
	string link_token;
	string param_tokens[2];
	if(location!=std::string::npos)
	{
		op_token = task.substr(0,location);
		link_token = task.substr(location+1,task.length());
		size_t param_location = link_token.find(delimiter);
		if(param_location!=std::string::npos)
		{
			param_tokens[0] = link_token.substr(0,param_location);
			param_tokens[1] = link_token.substr(param_location+1,link_token.length());
		}
	}
	else
	{
		op_token=task;
	}
	/*----------------------------OPERATIONS--------------------------------*/
	if(op_token=="open_new_page")
	{
		open_new_page(link_token);
	}
	else if(op_token=="open_link")
	{
		open_link(link_token);
	}
	else if(op_token=="display")
	{
	    display();
	}
	else if(op_token=="open_link_in_new_tab")
	{
		open_link_in_new_tab(link_token);
	}
	else if(op_token=="close_tab")
	{
		size_t index = string_to_size_t(link_token);
		close_tab(index);
	}
	else if(op_token=="reopen_closed_tab")
	{
		reopen_closed_tab();
		
	}
	else if(op_token=="move_tab")
	{
		size_t arg1 = string_to_size_t(param_tokens[0]);
		size_t arg2 = string_to_size_t(param_tokens[1]);
		move_tab(arg1,arg2);
	}
	else if(op_token=="select_tab")
	{
		size_t index = string_to_size_t(link_token);
		select_tab(index);
	}
	else if(op_token=="close_selected_tab")
	{
		close_selected_tab();
	}
	else if(op_token=="display_tab_details")
	{
		display_tab_details();
	}
	else if(op_token=="back")
	{
		try {
		back();
		} catch(const char* msg){
		cerr<<msg<<endl;
		}
	}
	else if(op_token=="forward")
	{
		try {
		forward();
		}catch (const char* msg){
		cerr<<msg<<endl;
		}
	}
}

void Browser::open_new_page(string link)
{
	Tab* new_page=new Tab(link);
	pages.insert(&pages.getBack(),*new_page);
	selected = new_page;
	if(pages.getSize()<=1)
		selected_tab_index = 0;
	else
		selected_tab_index = pages.getSize() - 1;
}

void Browser::open_link(string link)
{
	//take the previous page information before
	string previousPage = selected->getPage();
	selected->prevPages.push(previousPage);
	selected->setPage(link);
	pages.insertAt(selected_tab_index,*selected);
	pages.eraseFrom(selected_tab_index+1);

	
	
		
}

void Browser::open_link_in_new_tab(string link)
{
	Tab* new_page = new Tab(link);
	pages.insertAt(selected_tab_index+1,*new_page);
	if(pages.getSize()>1)
		selected_tab_index++;
	selected = new_page;
}

void Browser::close_tab(size_t index){
        size_t tmp = pages.getSize();
        if(pages.getNodePtrAt(index)!=NULL)
        {
            Tab data = pages.getNodeAt(index).getData();
            pages.eraseFrom(index);
            /*-------below two operation handles the tab data and index saving ----------------*/
            closedPages.push(data);
            saveIndex(index);//in order to save present position of closed tab.
            /*---------------------------------------------------------------------------------*/
           if(index == selected_tab_index){
                 if(index == tmp-1)
                 {
                     selected_tab_index = index - 1;
                     Tab * selected_tab = pages.getNodeAt(index-1).getDataPtr();
                     selected = selected_tab;
                 }
                 else                
                 {      
                     selected_tab_index = index;
                     Tab * selected_tab = pages.getNodeAt(index).getDataPtr();
                     selected = selected_tab;
                 }
           }    
           else
                selected_tab_index--;
        }
}

void Browser::saveIndex(size_t pos)
{
	closedIndex.push(pos);
}

void Browser::reopen_closed_tab()
{
	size_t pos = closedIndex.pop();
	pages.insertAt(pos,closedPages.pop());
	selected_tab_index = pos;
	selected = pages.getNodeAt(selected_tab_index).getDataPtr();
}


void Browser::move_tab(size_t from,size_t to)
{
  	if(to>from)
    {	pages.insertAt(to+1,pages.getNodeAt(from).getData());
		selected_tab_index = to;
		size_t new_tab_index = to+1;
		Tab * selected_tab = pages.getNodeAt(new_tab_index).getDataPtr();
		selected = selected_tab;
		pages.eraseFrom(from);
	}
	else if(from>to)
	{
		pages.insertAt(to,pages.getNodeAt(from).getData());
		selected_tab_index = to;
		Tab * selected_tab = pages.getNodeAt(selected_tab_index).getDataPtr();
		selected= selected_tab;
		pages.eraseFrom(from+1);
	}
}

void Browser::select_tab(size_t index)
{
	selected_tab_index = index;
	selected = pages.getNodeAt(selected_tab_index).getDataPtr();
}

void Browser::close_selected_tab()
{
	close_tab(selected_tab_index);
}

void Browser::display_tab_details()
{
	if(selected->nextPages.getSize()>0)
	{
		selected->nextPages.printReversed();
	}
	cout<<"> "<<selected->getPage()<<endl;
	if(selected->prevPages.getSize()>0)
	{
		selected->prevPages.print();
	}
}

void Browser::back()
{
	if(!selected->prevPages.isEmpty())
	{
		string previous_page = selected->prevPages.pop();
		selected->add_nextPages(selected->getPage());
		selected->setPage(previous_page);
		pages.eraseFrom(selected_tab_index);
		pages.insertAt(selected_tab_index,*selected);
	}
	else
		throw "no page to go back";
}

void Browser::forward()
{
	if(!selected->nextPages.isEmpty())
	{
		string next_page = selected->nextPages.pop();
		selected->add_prevPages(selected->getPage());
		selected->setPage(next_page);
		pages.eraseFrom(selected_tab_index);
		pages.insertAt(selected_tab_index,*selected);
	}
	else
		throw "no page to go forward";
}



size_t Browser::string_to_size_t(string link)
{
	stringstream sstream(link);
	size_t index;
	sstream >> index;
	return index;
}

void Browser::display()
{
    cout<<"CURRENT TAB: "<<selected_tab_index<<endl;
    cout<<selected->getPage()<<endl;
    cout<<"OPEN TABS: "<<pages.getSize()<<endl;
    for(size_t i=0;i<pages.getSize();i++)
		cout<<pages.getNodeAt(i)<<endl;
	cout<<"CLOSED TABS: "<<closedPages.getSize()<<endl;
	if(closedPages.getSize()>0)
	{
	    Stack<Tab> tempStack = closedPages;
	    for(size_t tmp=tempStack.getSize();tmp>0;tmp--)
		{
			cout<<tempStack.pop().getPage()<<endl;
		}
	}
}

