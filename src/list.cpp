// list.cpp
#include <memory.h>
#include <stdio.h>

#include "list.h"

//-------- Rlist ------------------------

//------------------
Rlist::Rlist()
//------------------
{
	current = head = new item;
	head->next = 0;
	count	= 0;
}

//-------------------
Rlist::~Rlist()
//-------------------
{
// hem
}

//------------------------
int		Rlist::itemCount()
//------------------------
{
	return (count);
}

//--------------------------------
void	Rlist::insertItem(void *new_content)
//--------------------------------
{
	item	*new_item;

	new_item = new item;
	new_item->content = new_content;	
	new_item->next = current->next;
	current->next = new_item;

	count++;
}

//--------------------------------
void	Rlist::appendItem(void *new_content)
//--------------------------------
{
	item	*new_item,
			*temp;
	
	if (current->next != 0) // if we're not at the end of the list
	{
		temp = current; // if we're not yet : go there
		while (current->next != 0)
			temp = current->next;

	}

	new_item = new item;
	new_item->content = new_content;
	current->next = new_item;
	new_item->next = 0;
	current = new_item;

	count++;
}

//----------------------------------
void	Rlist::removeItem()
//----------------------------------
// Remove item next to current
{
	item *temp;

	if (current != head)
	{
		temp = current->next;
		current->next = temp->next;
		temp->next = 0;
		delete	temp->content; // ??
		delete	temp;

		count--;
	}

}

//------------------------------------
item	*Rlist::gotoNextItem()
//------------------------------------
{
	//printf("Rlist::gotoNextItem() : %i\n", current);
	return (current = current->next);
}

//-------------------------------
item	*Rlist::gotoPrevItem()
//-------------------------------
{
	item *temp;
	temp = head;

	//printf("Rlist::gotoPrevItem() : %i\n", current);
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
item	*Rlist::gotoFirstItem()
//-------------------------------
{
	return	(current = head->next);
}


//-------------------------------
item	*Rlist::gotoListHead()
//-------------------------------
{
	return	(current = head);
}


//-----------------------------------------------
void	*Rlist::getContent()
//-----------------------------------------------
{
	return	(current->content);
}