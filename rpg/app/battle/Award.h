/*
 * Award.h
 *
 *  Created on: 2019年6月20日
 *      Author: Administrator
 */

#ifndef _AWARD_H_
#define _AWARD_H_

#include "Kernel.h"
#include "Msgs.h"
#include "CfgCommon.pb.h"

class Award {
public:
	Award();
	~Award();
	bool Add(uint32_t item, uint32_t num);
	bool Format(const string &v);
	bool Format(const CfgCommon::Reward&v, uint32_t multiple);
	bool Format(const ::google::protobuf::RepeatedPtrField< ::CfgCommon::Reward > &v, uint32_t multiple);
	bool Get(vector<msgs::SItemAmount> &v);
	const map<uint32_t, uint32_t>& Data() const;
	bool Random(const ::google::protobuf::RepeatedPtrField< ::CfgCommon::Reward > &v, uint32_t num);
	bool IsExist(uint32_t item) const;
	void Clear();
	Award& operator+=(const Award &v) {
		map<uint32_t, uint32_t>::const_iterator itr = v.Data().begin();
		for (; itr != v.Data().end(); ++itr) {
			Add(itr->first, itr->second);
		}
		return *this;
	}
private:
	map<uint32_t, uint32_t> m_data;
};

#endif /* _AWARD_H_ */
