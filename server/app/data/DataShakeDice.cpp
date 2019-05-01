#include "DataShakeDice.h"

int CDataShakeDice::Get(DataShakeDice &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(version);
	DBCREQ_NEED(curmap);
	DBCREQ_NEED(map1_status);
	DBCREQ_NEED(map2_status);
	DBCREQ_NEED(map3_status);
	DBCREQ_NEED(dice_times);
	DBCREQ_NEED(reset_times);
	DBCREQ_NEED(steps);
	DBCREQ_NEED(operate_ts);
	DBCREQ_NEED(extra_reward_status);
	DBCREQ_NEED(map1_rewards);
	DBCREQ_NEED(map2_rewards);
	DBCREQ_NEED(map3_rewards);
	DBCREQ_NEED(curpos);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, version);
	DBCREQ_GET_INT(data, curmap);
	DBCREQ_GET_INT(data, map1_status);
	DBCREQ_GET_INT(data, map2_status);
	DBCREQ_GET_INT(data, map3_status);
	DBCREQ_GET_INT(data, dice_times);
	DBCREQ_GET_INT(data, reset_times);
	DBCREQ_GET_INT(data, steps);
	DBCREQ_GET_INT(data, operate_ts);
	DBCREQ_GET_INT(data, extra_reward_status);
	DBCREQ_GET_INT(data, map1_rewards);
	DBCREQ_GET_INT(data, map2_rewards);
	DBCREQ_GET_INT(data, map3_rewards);
	DBCREQ_GET_INT(data, curpos);

	return 0;
}

int CDataShakeDice::Add(DataShakeDice &data)
{
	DBCREQ_DECLARE(DBC::ReplaceRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, version);
	DBCREQ_SET_INT(data, curmap);
	DBCREQ_SET_INT(data, map1_status);
	DBCREQ_SET_INT(data, map2_status);
	DBCREQ_SET_INT(data, map3_status);
	DBCREQ_SET_INT(data, dice_times);
	DBCREQ_SET_INT(data, reset_times);
	DBCREQ_SET_INT(data, steps);
	DBCREQ_SET_INT(data, operate_ts);
	DBCREQ_SET_INT(data, extra_reward_status);
	DBCREQ_SET_INT(data, map1_rewards);
	DBCREQ_SET_INT(data, map2_rewards);
	DBCREQ_SET_INT(data, map3_rewards);
	DBCREQ_SET_INT(data, curpos);

	DBCREQ_EXEC;

	return 0;
}

int CDataShakeDice::Set(DataShakeDice &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, version);
	DBCREQ_SET_INT(data, curmap);
	DBCREQ_SET_INT(data, map1_status);
	DBCREQ_SET_INT(data, map2_status);
	DBCREQ_SET_INT(data, map3_status);
	DBCREQ_SET_INT(data, dice_times);
	DBCREQ_SET_INT(data, reset_times);
	DBCREQ_SET_INT(data, steps);
	DBCREQ_SET_INT(data, operate_ts);
	DBCREQ_SET_INT(data, extra_reward_status);
	DBCREQ_SET_INT(data, map1_rewards);
	DBCREQ_SET_INT(data, map2_rewards);
	DBCREQ_SET_INT(data, map3_rewards);
	DBCREQ_SET_INT(data, curpos);

	DBCREQ_EXEC;

	return 0;
}

int CDataShakeDice::Del(DataShakeDice &data)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_EXEC;

	return 0;
}
