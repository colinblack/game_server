/**
desc:	hash table class
author:	manyin
*/

#include "list.h"

//template <class T> 
class ListHashTable
{
	public:
		ListHash(int32_t sz):size(sz)
		{
			init(sz);
		}

	public:
		void initHash(int sz)
		{
			bucket = new list_head[sz];
			for(int i=0;i<sz;i++)
			{
				INIT_LIST_HEAD( bucket + i );
			}
		}

		virtual int32_t hashFunc()
		{
			
		}

		void put()
		{
			int32_t index = hashFunc();
			list_del(&this->hash_item);
			list_add_head(&this->hash_item, bucket[index]);
			
		}

		list_head* get()
		{
			
		}

		

	private:
		static list_head *bucket;
		list_head hash_item;
		private size;
};





