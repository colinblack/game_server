/*
 * AsynManager.cpp
 *
 *  Created on: 2016-10-9
 *      Author: Ralf
 */


#include "AsynManager.h"


int AsynManager::OnInit() {
	for(unsigned i=0;i<MEMORY_HERO_PROPERTY_NUM*SG17_HERO_NUM;++i)
	{
		if(m_data->item[i].uid != 0)
			m_map[m_data->item[i].uid][m_data->item[i].id] = i;
		else
			m_freeIndex.insert(i);
	}
	return 0;
}
