#include "Tab.hpp"
Tab::Tab()
{
	page=string();
	page_size=0;
}	
Tab::Tab(string p)
{
	page = string(p);
	page_size = 1;
}

string Tab::getPage() const
{
	return page;
}

size_t Tab::getSize() const
{
	return page_size;
}

void Tab::add_prevPages(string page)
{
	prevPages.push(page);
	page_size++;
}
void Tab::add_nextPages(string page)
{
	nextPages.push(page);
}
void Tab::setPage(string p)
{
	page = p;
}
