/*
 * ResourceManager.cpp
 *
 *  Created on: 2016-9-2
 *      Author: Ralf
 */

#include "ResourceManager.h"
#include "BaseManager.h"

unsigned OfflineResourceItem::CalcAddExplotBox(int exploit, int box_lvl, int add_exploit) const
{
	if (add_exploit <= 0)
	{
		return 0;
	}

	try
	{
		ExploitBoxCfgWrap cfg;
		unsigned old_stage = cfg.GetExploitBoxStage(box_lvl, exploit);
		unsigned new_exploit = exploit + add_exploit;
		unsigned new_stage = cfg.GetExploitBoxStage(box_lvl, new_exploit);

		unsigned nAddCnt = 0;
		for (unsigned stage = old_stage + 1; stage <= new_stage; ++stage)
		{
			nAddCnt += cfg.GetBoxCntByStage(box_lvl, stage);
		}

		return nAddCnt;
	}
	catch(const std::exception& e)
	{
		error_log("uid: %u, %s", uid, e.what());
	}

	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////

int ResourceManager::OnInit() {
	for(unsigned i=0;i<MEMORY_HERO_PROPERTY_NUM;++i)
	{
		if(m_data->item[i].uid != 0)
			m_map[m_data->item[i].uid] = i;
		else
			m_freeIndex.insert(i);
	}
	return 0;
}


