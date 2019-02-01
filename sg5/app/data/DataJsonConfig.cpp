/*
 * DataJsonConfig.cpp
 *
 *  Created on: 2017-5-17
 *      Author: dawx62fac
 */

#include "DataJsonConfig.h"

JsonFeedbackItem::JsonFeedbackItem(const Json::Value& jsonData)
{
	amount_ = jsonData["need"].asInt();
	for (Json::UInt i = 0; i < jsonData["id"].size(); i++)
	{
		int  id = jsonData["id"][i].asInt();
		v_equips_id_.push_back(id);

		if (0 == id)
		{
			throw std::runtime_error("config_soul_feedback_id_error");
		}
	}

	for(Json::UInt i = 0; i < jsonData["count"].size(); i++)
	{
		int cnt = jsonData["count"][i].asInt();
		v_equips_cnt_.push_back(cnt);

		if (cnt == 0)
		{
			throw std::runtime_error("config_soul_feedback_cnt_error");
		}
	}

	if (v_equips_id_.size() != v_equips_cnt_.size())
	{
		throw std::runtime_error("config_soul_feedback_id_and_cnt_size_error");
	}

	/*if (amount_ == 0)
	{
		throw std::runtime_error("config_soul_feedback_need_error");
	}*/
}

int JsonFeedbackItem::EquipId(int idx) const
{
	if (idx < 0 || idx > v_equips_id_.size())
	{
		throw std::runtime_error("equps_index_error");
	}

	return v_equips_id_[idx];
}

int JsonFeedbackItem::EquipCnt(int idx) const
{
	if (idx < 0 || idx > v_equips_id_.size())
	{
		throw std::runtime_error("equps_index_error");
	}

	return v_equips_cnt_[idx];
}
