// itemList.cpp
#include <memory.h>

#include "itemList.h"
#include "gfxBuffer.h"

//------------------
itemList::itemList()
//------------------
{
	first = 0;
}

//-------------------
itemList::~itemList()
//-------------------
{
	//if (this->getNextItem(first->next) != 0)
	//	delete(this->getNextItem(first->next));

	//delete (this->tmp);
}


//--------------------------------
void	itemList::insertItem(void *new_content)
//--------------------------------
{
	item	*new_item, *tmp;
	new_item = new item;
	
	new_item->content = new_content;

	tmp = first;
	first = new_item;
	new_item->next = tmp;
}

//----------------------------------
void	itemList::removeItem(item *)
//----------------------------------
{
}

//------------------------------------
item	*itemList::getNextItem(item *req_item)
//------------------------------------
{
	if (first == 0) return 0;

	return (req_item->next);
}


//-------------------------------
item	*itemList::getFirstItem()
//-------------------------------
{
	return	(first->next);
}


//-----------------------------------------------
void	*itemList::getContent(item *req_item)
//-----------------------------------------------
{
	return	(req_item->content);
}