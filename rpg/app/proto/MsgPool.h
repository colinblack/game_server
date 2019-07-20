#ifndef MSG_POOL_H_
#define MSG_POOL_H_

#include "Kernel.h"
#include "MsgBase.h"

typedef Msg* (*CreateFun)();

class MsgPool: public CSingleton<MsgPool> {
private:
	friend class CSingleton<MsgPool>;
	MsgPool();
	map<uint32_t, CreateFun> pool_;
	vector<Msg*> del_;
public:
	~MsgPool();
	bool Init();
	template<typename T>
	T* GetMsg() {
		map<uint32_t, CreateFun>::iterator itr = pool_.find(T::MsgId());
		if (itr == pool_.end()) {
			return NULL;
		}
		CreateFun fun = itr->second;
		Msg *nptr = fun();
		if (nptr != NULL) {
			del_.push_back(nptr);
		}
		return dynamic_cast<T*>(nptr);
	}
	Msg* DecodeMsg(CBufferReader &reader);
	bool EncodeMsg(CBufferWriter &writer, Msg* ptr);
	void Recycle();
};

#endif /* MSG_POOL_H_ */
