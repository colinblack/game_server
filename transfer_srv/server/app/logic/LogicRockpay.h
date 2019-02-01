#ifndef __LOGIC_ROCKPAY_H__
#define __LOGIC_ROCKPAY_H__

#include <string>
#include <vector>
using namespace std;

class CLogicRockpay
{
public:
	const string& GetErrMsg() const
	{
		return m_errMsg;
	}

	int GenerateOrderId(
			const string &openid,
			string &app,
			string &aoid,
			string &r_url,
			string &m1,
			string &m2,
			string &v_code);

	int PayCallback(
			const string &aoid,
			const string &m1,
			const string &m2,
			const string &tid,
			const string &v_code,
			int &cash);

private:
	string m_errMsg;
};

#endif
