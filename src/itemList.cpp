// itemList.cpp
#include <memory.h>

#include "itemList.h"

//------------------
itemList::itemList()
//------------------
{
	memset(this, 0, sizeof(itemList));
}

//-------------------
itemList::~itemList()
//-------------------
{
	if (this->getNextItem(first->next) != 0)
		delete(this->getNextItem(first->next));

	delete (this->temp_pointer);
}


//--------------------------------
item	*itemList::addItem(void *)
//--------------------------------
{
	return 0;
}

//----------------------------------
void	itemList::removeItem(item *)
//----------------------------------
{
}

//------------------------------------
item	*itemList::getNextItem(item *)
//------------------------------------
{
	return 0;
}


//-------------------------------
item	*itemList::getFirstItem()
//-------------------------------
{
	return	(first->next);
}


//-----------------------------------------------
void	*itemList::getItemPointer(item *req_item)
//-----------------------------------------------
{
	return	(req_item->pointer);
}