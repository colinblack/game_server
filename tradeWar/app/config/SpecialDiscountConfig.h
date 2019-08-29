/*
 * SpecialDiscountConfig.h
 *
 *  Created on: 2018年11月9日
 *      Author: Administrator
 */

#ifndef SPECIAL_DISCOUNT_CONFIG_H_
#define SPECIAL_DISCOUNT_CONFIG_H_

#include "Kernel.h"
#include "Award.h"

struct SpecialDiscountItem {
	uint32_t id;
	uint32_t lv;
	Award reward;

	SpecialDiscountItem() {
		id = 0;
		lv = 0;
	}
};
class SpecialDiscountConfig {
	SINGLETON_CLASS(SpecialDiscountConfig);
	bool init();
	const SpecialDiscountItem* getItem(uint32_t id) const;
	uint32_t getSize() const;
private:
	map<uint32_t, SpecialDiscountItem> m_data;
};

#endif /* SPECIAL_DISCOUNT_CONFIG_H_ */
