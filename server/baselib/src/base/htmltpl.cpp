/*!
 * \file htmltpl.cpp
 * \author FelitHuang
 * \version 1.0.0.1
 * \date    2005-12-20
*/

/************************************************************************/

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "htmltpl.h"



/*! 
 * CHtmlTpl-Member-Function-Definition
*/

CHtmlTpl::CHtmlTpl(const std::string& sFileName, const std::string& sTokenHead, const std::string& sTokenTail)
	: m_sfName(sFileName), m_sTokenHead(sTokenHead), m_sTokenTail(sTokenTail)
{
	m_vtpl.reserve(32);
	m_vToken.reserve(32);
	m_vValue.reserve(32);
	NewHtml();
}

CHtmlTpl::~CHtmlTpl()
{
	ClnTpl();
	DelHtml();
}

int CHtmlTpl::CheckInit()
{
    return (m_vtpl.size()>0) ? 0 : -1;
}

int CHtmlTpl::SetFile(const std::string& sFileName, const std::string& sTokenHead, const std::string& sTokenTail)
{
	m_sfName = sFileName;
	m_sTokenHead = sTokenHead;
	m_sTokenTail = sTokenTail;
	return NewHtml();
}

int CHtmlTpl::NewHtml()
{
	DelHtml();
	return ReadFile();
}

int CHtmlTpl::DelHtml()
{
	m_vtpl.clear();
	return ECODE_SUCC;
}

int CHtmlTpl::NewTpl(const std::string& sBegin, const std::string& sEnd, int hTpl)
{
	if (hTpl<0 || hTpl>=(int)m_vtpl.size())
		return -1;

	std::string& sTpl = m_vtpl[hTpl];
	std::string::size_type nPosBegin = 0;
	std::string::size_type nPosEnd = 0;

	// get_begin_position
	if (!sBegin.empty())
	{
		if ((nPosBegin=sTpl.find(sBegin, nPosBegin))==std::string::npos)
			return -1;
		nPosBegin += sBegin.size();
	}

	// get_end_position
	if (!sEnd.empty())
	{
		if ((nPosEnd=sTpl.find(sEnd, nPosBegin))==std::string::npos)
			return -1;
	}
	else
	{
		nPosEnd = sTpl.size();
	}

	// get_return_index_and_template
	size_t nIndex = (size_t)m_vtpl.size();
	m_vtpl.push_back(std::string(sTpl, nPosBegin, nPosEnd-nPosBegin));

	return nIndex;
}

int CHtmlTpl::DelTpl(int hTpl)
{
	if (hTpl>=1 && hTpl<(int)m_vtpl.size())
	{
		m_vtpl[hTpl].erase();
	}
	return ECODE_SUCC;
}

int CHtmlTpl::FillTpl(int hTpl, std::ostream& ostm, const std::string& sBegin, const std::string& sEnd)
{
	if (hTpl<0 || hTpl>=(int)m_vtpl.size())
		return ECODE_NOTPL;

	std::string& sTpl = m_vtpl[hTpl];
	std::string::size_type nPosBegin = 0;
	std::string::size_type nPosEnd = 0;

	// get_begin_position
	if (!sBegin.empty())
	{
		if ((nPosBegin=sTpl.find(sBegin, nPosBegin))==std::string::npos)
			return ECODE_FAIL;
		nPosBegin += sBegin.size();
	}

	// get_end_position
	if (!sEnd.empty())
	{
		if ((nPosEnd=sTpl.find(sEnd, nPosBegin))==std::string::npos)
			return ECODE_FAIL;
	}
	else
	{
		nPosEnd = sTpl.size();
	}

	// output_to_the_stream
	if(!ostm.good())
	{
		ostm.clear();
	}
	ostm.write(sTpl.data()+nPosBegin, nPosEnd-nPosBegin);

	return ECODE_SUCC;
}

int CHtmlTpl::FillTplWithValue(int hTpl, std::ostream& ostm)
{
	if (hTpl<0 || hTpl>=(int)m_vtpl.size())
		return ECODE_NOTPL;

	std::string& sTpl = m_vtpl[hTpl];
	std::string::size_type nPosBegin = 0;
	std::string::size_type nPosEnd = 0;

	std::vector<std::string>::size_type nTokenNum = m_vToken.size();
	std::vector<std::string>::size_type nTokenPos = 0;
	std::string sStr="";

	// find_TOKENHEADER_until_reaching_the_end
	while (sTpl[nPosEnd] && (nPosEnd=sTpl.find(m_sTokenHead, nPosEnd))!=std::string::npos)
	{
		// check_if_is_the_TOKEN
		for (nTokenPos=0; nTokenPos<nTokenNum; ++nTokenPos)
		{
			// do not check with the std::string::compare() because of the COMPILER's compatibility and do not wish to use the #ifdef
			if (nPosEnd+m_vToken[nTokenPos].size()<=sTpl.size() && std::equal(m_vToken[nTokenPos].data(), m_vToken[nTokenPos].data()+m_vToken[nTokenPos].size(), sTpl.data()+nPosEnd))
			{
				//ostm.write(sTpl.data()+nPosBegin, nPosEnd-nPosBegin);
				//ostm.write(m_vValue[nTokenPos].data(), m_vValue[nTokenPos].size());
				sStr += sTpl.substr(nPosBegin, nPosEnd-nPosBegin) ;
				sStr +=  m_vValue[nTokenPos];	
				nPosBegin = nPosEnd += m_vToken[nTokenPos].size();
				break;
			}
		}
		// not_the_TOKEN_position
		if (nTokenPos==nTokenNum)
		{
			nPosEnd += 1;
		}
	}

	sStr += sTpl.substr(nPosBegin) ;
	// output_the_template_left
	if(!ostm.good())
	{
		ostm.clear();
	}
	
	//ostm.write(sTpl.data()+nPosBegin, sTpl.size()-nPosBegin);
	ostm.write(sStr.data(), sStr.size());

	return ECODE_SUCC;
}

int CHtmlTpl::NewValue(const std::string& sToken, const CCgiOutValue& stHtml)
{
	std::string  sTokenX = m_sTokenHead+sToken+m_sTokenTail;
	if (!sTokenX.empty())
	{
		m_vToken.push_back(sTokenX);
		m_vValue.push_back(stHtml.Data());
		return ECODE_SUCC;
	}
	return ECODE_FAIL;
}

int CHtmlTpl::ClnValue()
{
	m_vToken.clear();
	m_vValue.clear();

	return ECODE_SUCC;
}

int CHtmlTpl::ClnTpl()
{
	if (m_vtpl.size()>0)
	{
		m_vtpl.erase(m_vtpl.begin()+1, m_vtpl.end());
	}

	return ECODE_SUCC;
}

int CHtmlTpl::ReadFile()
{
	// not_allow_empty_file_name
	if (m_sfName.empty())
		return ECODE_FAIL;

	std::fstream fstm(m_sfName.c_str(), std::ios::in|std::ios::binary);
	if (!fstm)
	{
		fstm.close();
		return ECODE_FAIL;
	}

	// get_the_length_of_file
	fstm.seekg(0, std::ios::end);
	int nlen = fstm.tellg();

	if (m_vtpl.size()>0)
	{
		m_vtpl[0].resize(nlen);
	}
	else
	{
		m_vtpl.push_back(std::string());
		m_vtpl[0].resize(nlen);
	}

	// read_the_file_into_string_buffer
	if (nlen>=0)
	{
		fstm.seekg(0, std::ios::beg);
		fstm.read(const_cast<char *>(m_vtpl[0].data()), nlen);
	}

	fstm.close();
	return ECODE_SUCC;
}


/*!
 * CHtmlTplEx-Member-Function-Definition
*/

CHtmlTplEx::CHtmlTplEx (const std::string& sFileName, const std::string& sTokenHead, const std::string& sTokenTail)
	: CHtmlTpl (sFileName, sTokenHead, sTokenTail)
{
	m_strm.m_ptpl = this;
}

CHtmlTplEx::CHtmlTplEx (const CHtmlTplEx& tplInit)
	: CHtmlTpl(tplInit)
{
	m_strm.m_ptpl = this;
}

CHtmlTplEx& CHtmlTplEx::ISTRM::operator << (const CCgiOutValue& _oValue)
{
	m_ptpl->NewValue(*m_pToken, _oValue);
	return *m_ptpl;
}

CHtmlTplEx::ISTRM& CHtmlTplEx::ISTRM::operator = (const CHtmlTplEx::ISTRM&)
{
	return *this;	// 只指向一个对象,初始后不再改变
}

CHtmlTplEx::ISTRM& CHtmlTplEx::operator << (const std::string& sToken)
{
	m_strm.m_pToken = &sToken;
	return m_strm;
}

/************************************************************************/
