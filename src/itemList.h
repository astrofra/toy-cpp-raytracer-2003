// itemList.h

#include "gfxBuffer.h"

#ifndef	ITEM_LIST
#define ITEM_LIST

struct item
{
	void	*content;
	item	*next;
};

class	itemList
{
public:
	itemList();
	~itemList();
	void	insertItem(void *);
	item	*getNextItem(item *);
	item	*getFirstItem();
	void	*getContent(item *);
	void	removeItem(item *);

private:
	item	*first;

};

#endif
