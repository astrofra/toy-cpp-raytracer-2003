// itemList.h

// C++ (ugly) code by http://fra.dozign.com
// In no event shall the author be liable for any indirect or
// consequential damages or loss of data resulting from use
// or performance of this software.

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
