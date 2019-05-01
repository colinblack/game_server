#include "membuf.h"

CMemBuf::CMemBuf(){
	m_memStart = NULL;
	m_dataPos = NULL;
	m_pReadPos = NULL;
	m_pWritePos = NULL;
	m_endPos = 0;
}

CMemBuf::~CMemBuf(){
	if(m_memStart){
		delete[] m_memStart;
		m_memStart = NULL;
	}
}


bool CMemBuf::init(uint32_t size){
	m_memStart = new char[size];
	if(!m_memStart){
		return false;
	}
	
	memset(m_memStart,0,size);
	
	char* start = m_memStart ;
	if(((uint64_t)m_memStart) % 8){
		start += (8 - ((uint64_t)m_memStart) % 8);
	}

	m_pReadPos = (uint32_t*) start;
	m_pWritePos = (uint32_t*)(start+4);
	m_endPos = size - (start - m_memStart) - 8;
	m_dataPos = start + 8;
	
	*m_pReadPos = 0;
	*m_pWritePos = 0;
	
	return true;
}

char* CMemBuf::getWriteMem(uint32_t size){
	if(*m_pWritePos >= *m_pReadPos){
		
		if(*m_pWritePos + size > m_endPos){
			if(*m_pReadPos == 0) return NULL;
			memset(m_dataPos + *m_pWritePos,0,m_endPos - *m_pWritePos);
			*m_pWritePos = 0;
		}
		else{
			return m_dataPos + *m_pWritePos;
		}	
	}
	
	if(*m_pWritePos < *m_pReadPos){
		if(*m_pWritePos + size >= *m_pReadPos){
			return NULL;
		}
		
		return m_dataPos + *m_pWritePos;
	}
	
	return NULL;
}

char* CMemBuf::getReadMem(){
	
	if(*m_pReadPos > *m_pWritePos){
		if(*((short*)(m_dataPos + *m_pReadPos)) == 0){
			*m_pReadPos = 0;
		}
		else{
			return m_dataPos + *m_pReadPos;
		}
	}
	
	if(*m_pReadPos < *m_pWritePos){
		return m_dataPos + *m_pReadPos;
	}
	
	return NULL;
}

