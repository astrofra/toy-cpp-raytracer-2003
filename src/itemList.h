// itemList.h

struct item
{
	void *pointer;
	item *next;
};

class	itemList
{
	public:
		itemList();
		~itemList();
		item	*addItem(void *);
		item	*getNextItem(item *);
		item	*getFirstItem();
		void	*getItemPointer(item *);
		void	removeItem(item *);

	private:
		item *first;
		item *temp_pointer;

};