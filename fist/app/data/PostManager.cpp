/*
 * PostManager.cpp
 *
 *  Created on: 2018年9月13日
 *      Author: colin
 */

#include "PostManager.h"


int PostManager::OnInit()
{
	for(int i = 0; i < e_Post_max; ++i)
	{
		for(unsigned j = 0; j < MAX_SIZE; ++j)
		{
			if(i == e_Post_inviteUser)
			{
				if(m_data->item2[j].uid != 0)
					m_map[i][m_data->item2[j].uid][m_data->item2[j].id] = j;
				else
					m_freeIndex[i].insert(j);
			}
			else if(i == e_post_martialBattle)
			{
				if(m_data->item3[j].uid != 0)
					m_map[i][m_data->item3[j].uid][m_data->item3[j].id] = j;
				else
					m_freeIndex[i].insert(j);
			}
		}
	}

	return 0;
}


