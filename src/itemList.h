// itemList.h

#include "gfxBuffer.h"

#ifndef	ITEM_LIST
#define ITEM_LIST

//-------- item ------------------------

class item
{
	void	*content;
	item	*next;
	
	friend class itemList;
};

//-------- itemList ------------------------

class	itemList
{
public:
	itemList();
	~itemList();
	void	insertItem(void *);
	item	*gotoListHead();
	item	*gotoNextItem();
	item	*gotoPrevItem();
	item	*gotoFirstItem();
	void	*getContent();
	void	removeItem();

private:
	item	*head;
	item	*current;

};

#endif
