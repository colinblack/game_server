#ifndef _AWARD_H_
#define _AWARD_H_

#include "Kernel.h"

class Award {
public:
	Award();
	~Award();
	void clear();
	int add(const AwardInfo& awardInfo);
	int sub(const AwardInfo& awardInfo);
	inline vector<AwardInfo>& get() {
		return m_vecAward;
	}
	inline const vector<AwardInfo>& get() const {
		return m_vecAward;
	}
	inline bool isEmpty() const {
		return m_vecAward.empty();
	}
	Award& operator=(const Award &other) {
		m_vecAward = other.m_vecAward;
		return *this;
	}

	void multiply(uint32_t times);
	bool Json2Award(const Json::Value &value);
	bool changeResRate(uint32_t r1, uint32_t r2);
	bool packetData(CBufferWriter &writer) const;

	static bool Json2Award(const Json::Value &value, vector<AwardInfo> &vecAward);
	static bool JsonItem2Award(const Json::Value &value, const string &name, AwardInfo &awardInfo);
	static const string& Award2String(const vector<AwardInfo> &vecAward);
	static Json::Value Award2Json(const vector<AwardInfo> &vecAward);
	static bool addAward(Json::Value &value, const string &key, uint32_t count);
	static bool mergeAward(const vector<AwardInfo> &in, vector<AwardInfo> &out);
private:
	vector<AwardInfo> m_vecAward;
};

#endif /* _AWARD_H_ */
