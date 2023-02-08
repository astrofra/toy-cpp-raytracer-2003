// Rlist.h

//#include "gfxBuffer.h"

#ifndef	ITEM_LIST
#define ITEM_LIST

//-------- item ------------------------

class item
{
private :
	void	*content;
	item	*next;
	
	friend class Rlist;
};

//-------- Rlist ------------------------

class	Rlist
{
public:
	Rlist();
	~Rlist();
	void	insertItem(void *);
	void	appendItem(void *);
	item	*gotoListHead();
	item	*gotoNextItem();
	item	*gotoPrevItem();
	item	*gotoFirstItem();
	void	*getContent();
	void	removeItem();
	int		itemCount();

private:
	item	*head;
	item	*current;
	int		count;		// the counter is not necessary to the linked list's mechanic : only req'd for table creation purpose

};

#endif
