// itemList.cpp
#include <memory.h>
#include <stdio.h>

#include "itemList.h"
#include "gfxBuffer.h"

//-------- itemList ------------------------

//------------------
itemList::itemList()
//------------------
{
	current = head = new item;
	head->next = 0;
}

//-------------------
itemList::~itemList()
//-------------------
{
//
}


//--------------------------------
void	itemList::insertItem(void *new_content)
//--------------------------------
{
	item	*new_item;
	new_item = new item;
	
	new_item->content = new_content;	
	new_item->next = current->next;
	current->next = new_item;
}

//----------------------------------
void	itemList::removeItem()
//----------------------------------
// Remove item next to current
{
	item *temp;

	if (current != head)
	{
		temp = current->next;
		current->next = temp->next;
		temp->next = 0;
		delete	temp->content; // problem?
		delete	temp;
	}

}

//------------------------------------
item	*itemList::gotoNextItem()
//------------------------------------
{
	printf("itemList::gotoNextItem() : %i\n", current);
	return (current = current->next);
}

//-------------------------------
item	*itemList::gotoPrevItem()
//-------------------------------
{
	item *temp;
	temp = head;

	printf("itemList::gotoPrevItem() : %i\n", current);
	if (current != head->next)
	{
		while((temp != 0) && (temp->next != current))
		{
			temp = temp->next;
		}
		current = temp;
		return (current);
	}
	else
	{
		return (0);
	}

}

//-------------------------------
item	*itemList::gotoFirstItem()
//-------------------------------
{
	return	(current = head->next);
}


//-------------------------------
item	*itemList::gotoListHead()
//-------------------------------
{
	return	(current = head);
}


//-----------------------------------------------
void	*itemList::getContent()
//-----------------------------------------------
{
	return	(current->content);
}