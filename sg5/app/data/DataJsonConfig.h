/*
 * DataJsonConfig.h
 *
 *  Created on: 2017-5-12
 *      Author: dawx62fac
 */

#ifndef DATAJSONCONFIG_H_
#define DATAJSONCONFIG_H_

#include "Kernel.h"
#include <stdexcept>

/////////////////////////////////////////////////////////
//活动配置基类
//抽奖物品配置
class JsonProbUnitCfg
{
public:
	JsonProbUnitCfg() : prob_(1)
	{

	}

	JsonProbUnitCfg(const Json::Value& data)
	{
		if (data.isMember("prob"))
		{
			prob_ = data["prob"].asInt();
		}
		else
		{
			prob_ = 1;
		}
	}
	virtual ~JsonProbUnitCfg() {}

	int Prob() const { return prob_; }
protected:
	int prob_;  //概率权重
};

class JsonGoodItemCfg
{
public:
	JsonGoodItemCfg()
		: goods_id_(0)
		, goods_cnt_(0)
		, limit_(0)
	{

	}

	virtual ~JsonGoodItemCfg() {}

	JsonGoodItemCfg(const Json::Value& data)
		: goods_id_(0)
		, goods_cnt_(0)
		, limit_(0)
	{
		if (! data.isMember("eq_id") || ! data["eq_id"].isIntegral())
		{
			throw std::runtime_error("error_eq_id_field");
		}

		if (! data.isMember("eq_cnt") || ! data["eq_cnt"].isIntegral())
		{
			throw std::runtime_error("error_eq_cnt_field");
		}

		goods_id_ = data["eq_id"].asInt();
		goods_cnt_ = data["eq_cnt"].asInt();

		if (data.isMember("limit_cnt"))
		{
			limit_ = data["limit_cnt"].asInt();
		}
	}

	int GoodsId() const { return goods_id_; }
	int GoodsCnt() const { return goods_cnt_; }
	int LimitCnt() const { return limit_; }
	bool IsLimit() const { return limit_ > 0; }
private:
	int goods_id_;  //物品id
	int goods_cnt_; //物品数量，默认为1
	int limit_; 	//上限 0--无上限
};

class JsonLotteryItemCfg
	: public JsonProbUnitCfg
	, public JsonGoodItemCfg
{
public:
	JsonLotteryItemCfg() {}
	JsonLotteryItemCfg(const Json::Value& data)
		: JsonProbUnitCfg(data)
		, JsonGoodItemCfg(data)
	{

	}
};

///////////////////////////////////////////////////////////////////
//充值回馈,多选-;例如：武魂回馈
class JsonFeedbackItem
{
public:
	JsonFeedbackItem():amount_(0) {}
	JsonFeedbackItem(const Json::Value& jsonData);

	int Amount() const { return amount_; }
	int EquipId(int idx) const;
	int EquipCnt(int idx) const;
private:
	int amount_;
	std::vector<int> v_equips_id_;
	std::vector<int> v_equips_cnt_;
};

////////////////////////////////////////////////////////////////////////////////
template<class _ITEM>
class JsonItemsConfig
{
public:
	JsonItemsConfig() {}
	virtual ~JsonItemsConfig() {}

	JsonItemsConfig(const Json::Value& data)
	{
		if (! data.isArray())
		{
			error_log("not_array_type");
			throw std::runtime_error("need_array_json_data");
		}


		for (int i = 0; i < (int)data.size(); i++)
		{
			v_items_.push_back(data[i]);
		}
	}

	int size() const
	{
		return v_items_.size();
	}

	const _ITEM&  Item(int index) const
	{
		if (index < 0 || index >= (int)v_items_.size())
		{
			error_log("out index: %d", index);
			throw std::runtime_error("");
		}

		return v_items_[index];
	}

	/**
	 * 随即获取物品，排除已经达到上限的物品
	 */
	int RandomInLimits(const std::map<int, int>& status) const
	{
		std::vector<std::pair<int, int> > vProb;
		int total = 0;
		for(int i = 0; i < (int)v_items_.size(); i++)
		{
			const std::map<int, int>::const_iterator it = status.find(i);
			if (it != status.end()
					&& v_items_[i].IsLimit()
					&& it->second >= v_items_[i].LimitCnt())
			{
				continue;
			}

			vProb.push_back(std::make_pair<int, int>(i, v_items_[i].Prob()));
			total += v_items_[i].Prob();
		}

		if (vProb.empty())
		{
			throw std::runtime_error("all_items_reach_limit");
		}

		return RandomIndex(vProb, total);
	}

	/**
	 * 获得随机物品
	 */
	int Random() const
	{
		std::vector<std::pair<int, int> > vProb;
		int total = 0;
		for(size_t i = 0; i < v_items_.size(); i++)
		{
			vProb.push_back(std::make_pair<int, int>(i, v_items_[i].Prob()));
			total += v_items_[i].Prob();
		}

		return RandomIndex(vProb, total);
	}
private:
	int RandomIndex(const std::vector<std::pair<int, int> >& vProbs, int total) const
	{
		int nRandom = Math::GetRandomInt(total);
		for (size_t i = 0; i < vProbs.size(); i ++)
		{
			if (nRandom < vProbs[i].second)
			{
				return vProbs[i].first;
			}

			nRandom -= vProbs[i].second;
		}

		throw std::runtime_error("random_item_error");
	}
private:
	std::vector<_ITEM> v_items_;
};




#endif /* DATAJSONCONFIG_H_ */
