/*!
 * \file sqltpl.cpp
 * \author FelitHuang
 * \version 1.0.0.1
 * \date    2005/12/20
*/

/************************************************************************/

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "sqltpl.h"


/*!
 * CSqlTpl-Member-Function-Definition
*/

CSqlTpl::CSqlTpl(const std::string& sSQL, const std::string& sToken)
	: m_sSQLSrc(sSQL), m_sToken(sToken)
{
	m_vValue.reserve(32);
}

CSqlTpl::~CSqlTpl()
{
}

const std::string& CSqlTpl::GetSQL()
{
	m_sSQLDst.erase();

	std::string::size_type nPosBegin = 0;
	std::string::size_type nPosEnd = 0;

	std::vector<std::string>::size_type nTokenNum = m_vValue.size();
	std::vector<std::string>::size_type nTokenPos = 0;

	// find_and_replace_the_TOKENs_by_VALUEs
	while (nTokenPos<nTokenNum && m_sSQLSrc[nPosEnd] && (nPosEnd=m_sSQLSrc.find(m_sToken, nPosEnd))!=std::string::npos)
	{
		m_sSQLDst.append(m_sSQLSrc, nPosBegin, nPosEnd-nPosBegin);
		m_sSQLDst.append(m_vValue[nTokenPos]);
		nPosBegin = nPosEnd += m_sToken.size();
		
		++nTokenPos;
	}
	
	// append_the_template_left
	m_sSQLDst.append(m_sSQLSrc, nPosBegin, m_sSQLSrc.size()-nPosBegin);

	return m_sSQLDst;
}


CSqlTpl& CSqlTpl::SetSQL(const std::string& sSQL, const std::string& sToken)
{
	m_sSQLSrc = sSQL;
	m_sToken = sToken;

	return *this;
}

CSqlTpl& CSqlTpl::AppSQL(const std::string& sSQL)
{
	m_sSQLSrc += sSQL;

	return *this;
}

CSqlTpl& CSqlTpl::NewValue(const CStrSqlValue& stValue)
{
	m_vValue.push_back(stValue.Data());

	return *this;
}

CSqlTpl& CSqlTpl::ClnValue()
{
	m_vValue.clear();

	return *this;
}

CSqlTpl& CSqlTpl::operator << (const CStrSqlValue& stValue)
{
	m_vValue.push_back(stValue.Data());

	return *this;
}

/************************************************************************/
