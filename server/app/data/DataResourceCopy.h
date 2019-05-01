#ifndef DATA_RESOURCE_COPY_H_
#define DATA_RESOURCE_COPY_H_

#include "Kernel.h"

struct DataResourceCopy
{
	uint8_t buytimes;
    uint32_t uid;
    uint32_t id;

    DataResourceCopy():
    	buytimes(0),
    	uid(0),
    	id(0)
	{

	}

	void SetMessage(ProtoResourceCopy::ResourceCopyCPP * msg)
	{
		msg->set_id(id);
		msg->set_buytimes(buytimes);
	}
};

class CDataResourceCopy :public DBCBase<DataResourceCopy, DB_RESOURCE_COPY>
{
public:
	virtual int Get(DataResourceCopy &data);
	virtual int Get(vector<DataResourceCopy> &data);
	virtual int Add(DataResourceCopy &data);
	virtual int Set(DataResourceCopy &data);
	virtual int Del(DataResourceCopy &data);
};

#endif //DATA_RESOURCE_COPY_H_
