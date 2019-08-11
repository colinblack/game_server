

#include "DataCopy.h"

CDataCopy::CDataCopy()
{
	m_init = false;
}


bool CDataCopy::Init(const string &path)
{
	if(m_init)
	{
		return true;
	}
	if(!m_init)
	{
		if(!m_sh.CreateOrOpen(path.c_str(), sizeof(DataCopy)))
		{
			error_log("[init_data_fail][path=%s]", path.c_str());
			return false;
		}
		if(!m_sh.HasInit())
		{
			DataCopy * pdata = (DataCopy *)m_sh.GetAddress();
			if(pdata == NULL){
				return false;
			}
			for(uint32_t i=0; i<TYPE_COPYBOSS_COUNT; i++){
				for(uint32_t j=0;j<BOSS_COUNT;j++){
					for(uint32_t k=0;k<COPY_PLAYER_RANK_MAX_COUNT;k++){
						pdata->bossInfo[i][j].playerRank[k].rank=k+1;

					}
				}
			}
			m_sh.SetInitDone();
		}
		m_init = true;
	}
	return true;
}


bool CDataCopy::getBossIndex(uint32_t type,uint32_t bossId,uint32_t & index1,uint32_t & index2){
	if(bossId==0) return false;
	DataCopy* pData = (DataCopy*)m_sh.GetAddress();
	if(pData == NULL){
		return false;
	}
	switch(type){
	case TYPE_COPY_TASKBOSS:
		index1=0;
		break;
	case TYPE_COPY_WORLDBOSS:
		index1=1;
		break;
	case TYPE_COPY_GODPLANET:
		index1=2;
		break;
	}
	for(uint32_t i=0;i<BOSS_COUNT;i++){
		if(bossId == pData->bossInfo[index1][i].bossId){
			index2 =i;
			return true;
		}
	}
	return false;
}


bool CDataCopy::getBossRank(uint32_t type,uint32_t bossId,vector<BossPlayerRank>& vector){
	vector.clear();
	DataCopy* pData = (DataCopy*)m_sh.GetAddress();
	if(pData == NULL){
		return false;
	}
	uint32_t index1=0;
	uint32_t index2=0;
	if(!getBossIndex(type,bossId,index1,index2)){
		return false;
	}
	for(uint32_t i=0;i<COPY_PLAYER_RANK_MAX_COUNT;i++){
		BossPlayerRank tmp;
		tmp.uid = pData->bossInfo[index1][index2].playerRank[i].uid;
		tmp.value = pData->bossInfo[index1][index2].playerRank[i].value;
		tmp.rank =pData->bossInfo[index1][index2].playerRank[i].rank;
		vector.push_back(tmp);
	}
	return true;
}



bool CDataCopy::setBossRank(uint32_t type,uint32_t bossId,uint32_t uid,uint32_t value){
	DataCopy* pData = (DataCopy*)m_sh.GetAddress();
	if(pData == NULL){
		return false;
	}
	uint32_t index1=0;
	uint32_t index2=0;
	if(!getBossIndex(type,bossId,index1,index2)){
		return false;
	}

	uint32_t i=0;
	uint32_t j=0;
	for(i=0;i<COPY_PLAYER_RANK_MAX_COUNT;i++){
		if(uid ==pData->bossInfo[index1][index2].playerRank[i].uid){
			break;
		}
	}
	if(i<COPY_PLAYER_RANK_MAX_COUNT){
		pData->bossInfo[index1][index2].playerRank[i].value+=value;
		for(j=0;j<i;j++){
			if(pData->bossInfo[index1][index2].playerRank[i].value>pData->bossInfo[index1][index2].playerRank[j].value){
				break;
			}
		}
		BossPlayerRank tmp;
		tmp.uid =pData->bossInfo[index1][index2].playerRank[i].uid;
		tmp.value =pData->bossInfo[index1][index2].playerRank[i].value;
		memmove(&(pData->bossInfo[index1][index2].playerRank[j+1]), &(pData->bossInfo[index1][index2].playerRank[j]), (i-j)*sizeof(BossPlayerRank));
		pData->bossInfo[index1][index2].playerRank[j].uid= tmp.uid;
		pData->bossInfo[index1][index2].playerRank[j].value= tmp.value;
	}else{
		for(j=0;j<COPY_PLAYER_RANK_MAX_COUNT;j++){
			if(value>pData->bossInfo[index1][index2].playerRank[j].value){
				break;
			}
		}
		if(j<COPY_PLAYER_RANK_MAX_COUNT){
			memmove(&(pData->bossInfo[index1][index2].playerRank[j+1]), &(pData->bossInfo[index1][index2].playerRank[j]), (COPY_PLAYER_RANK_MAX_COUNT-1-j)*sizeof(BossPlayerRank));
			pData->bossInfo[index1][index2].playerRank[j].uid= uid;
			pData->bossInfo[index1][index2].playerRank[j].value= value;
		}
	}
	for(int i=0; i<COPY_PLAYER_RANK_MAX_COUNT; i++){
		pData->bossInfo[index1][index2].playerRank[i].rank = i+1;
	}
	return true;
}



DataCopy * CDataCopy::getDataCopy(){
	DataCopy* pData = (DataCopy*)m_sh.GetAddress();
	return pData;
}
