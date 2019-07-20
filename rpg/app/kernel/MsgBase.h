#ifndef _MSG_BASE_H_
#define _MSG_BASE_H_

#include "BufferReader.h"
#include "BufferWriter.h"

class Msg {
public:
	Msg() {
	}
	virtual ~Msg() {
	}
	virtual int32_t msgId() const {
		return -1;
	}
	virtual bool decode(CBufferReader &reader) {
		return true;
	}
	virtual bool encode(CBufferWriter &writer) const {
		return true;
	}
	virtual void clear() {
	}
	virtual Msg* New() const {
		return NULL;
	}
};

#endif /* _MSG_BASE_H_ */
