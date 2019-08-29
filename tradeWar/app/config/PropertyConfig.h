/*
 * PropertyConfig.h
 *
 *  Created on: 2015-9-2
 *      Author: Administrator
 */

#ifndef PROPERTYCONFIG_H_
#define PROPERTYCONFIG_H_

#include "Kernel.h"
#include "CommData.h"

#define DT_INT 1
#define DT_FLOAT 2
#define DT_UNSIGNED_INT 3

class PropertyConfig
{
private:
	~PropertyConfig();
public:
	static PropertyConfig * getInstance();
	static bool attrMapInit();
	static int getDataType(int type);
	static bool setAttr(Json::Value& value, int ap, Property& prop);
	static bool accumulateByRateProps(PropertySets & rateProps, PropertySets & props);
	static bool accumulateByRate(double rate, PropertySets & props, PropertySets & nextProps);
	static bool accumulateProps(PropertySets & newProps, PropertySets & baseProps);
	static bool accumulateByLevel(PropertySets & minProps, PropertySets & baseProps, PropertySets & curProps);
	static bool accumulateByBaseRate(PropertySets & base, double rate, PropertySets & props);
	static int attrRateToAdd(int rateAttr);
public:
	static map<string,uint32_t> m_attr2Idx;
	static map<uint32_t,string> m_idx2Attr;
	static bool m_bInit ;

};


#endif /* PROPERTYCONFIG_H_ */
