

#include <algorithm>

#include "paramparse.h"

#include "basic.h"

CParamParse::CParamParse()
{
	this->Parse("");
}

CParamParse::CParamParse(const std::string& sParam, const std::string& sDelimElem, const std::string& sDelimPair, bool bUnescape)
{
	this->Parse(sParam, sDelimElem, sDelimPair, bUnescape);
}

void CParamParse::Parse(const std::string& sParam, const std::string& sDelimElem, const std::string& sDelimPair, bool bUnescape)
{
	m_vData.clear();

	m_sDelimElem = sDelimElem;
	m_sDelimPair = sDelimPair;
	m_bEscape = bUnescape;

	if (!sParam.empty())
	{
		std::vector<std::string> vsElem;
		CBasic::StringSplit(sParam, sDelimElem, vsElem);

		for (std::vector<std::string>::iterator itItem=vsElem.begin(); itItem!=vsElem.end(); ++itItem)
		{
			std::string::size_type fpos = itItem->find(sDelimPair);
			if (std::string::npos == fpos)
			{
				TData stData;
				stData.sName = *itItem;
				m_vData.push_back(stData);
			}
			else
			{
				TData stData;
				stData.sName = itItem->substr(0, fpos);
				stData.sValue = itItem->substr(fpos+sDelimPair.size(), std::string::npos);
				if (bUnescape)
				{
					stData.sName = CBasic::unescape(stData.sName);
					stData.sValue = CBasic::unescape(stData.sValue);
				}
				m_vData.push_back(stData);
			}
		}
	}
	m_vData.push_back(TData());
}

const std::string& CParamParse::GetData(const std::string& sName)
{
	std::vector<TData>::reverse_iterator s_itRBegin = m_vData.rbegin();
	s_itRBegin->sName = sName;
	return std::find(m_vData.begin(), m_vData.end(), *s_itRBegin)->sValue;
}

std::vector<CParamParse::TData>::size_type CParamParse::GetSize() const
{
        return m_vData.size();
}

CParamParse& CParamParse::SetData(const std::string& sName, const std::string& sValue)
{
	std::vector<TData>::reverse_iterator s_itRBegin = m_vData.rbegin();
	s_itRBegin->sName = sName;
	std::vector<TData>::iterator itFind = std::find(m_vData.begin(), m_vData.end(), *s_itRBegin);
	itFind->sValue = sValue;
	if (&*itFind == &*s_itRBegin)
	{
		m_vData.push_back(TData());
	}
	return *this;
}

std::vector<std::string>& CParamParse::GetData(const std::string& sName, std::vector<std::string>& vData)
{
	vData.clear();
	std::vector<TData>::reverse_iterator s_itRBegin = m_vData.rbegin();
	s_itRBegin->sName = ("");
	std::vector<TData>::iterator bi = m_vData.begin();
	std::vector<TData>::iterator ei = m_vData.end();
	while ((bi=std::find(bi, ei, sName))!=ei)
	{
		vData.push_back(bi->sValue);
		++bi;
	}
	return vData;
}

std::string CParamParse::Construct(std::vector<TData>& vData, const std::string& sDelimElem, const std::string& sDelimPair, bool bEscape)
{
	std::vector<std::string> xData;
	for (std::vector<TData>::iterator itItem=vData.begin(); itItem!=vData.end(); ++itItem)
	{
		std::string sData(bEscape ? CBasic::escape(itItem->sName) : itItem->sName);
		sData += sDelimPair;
		sData += bEscape ? CBasic::escape(itItem->sValue) : itItem->sValue;
		xData.push_back(sData);
	}
	return CBasic::StringJoin(xData, sDelimElem);
}

CParamParse::operator std::string () const
{
	std::vector<std::string> xData;
	std::vector<TData>::const_iterator itEnd = m_vData.end();
	--itEnd;
	for (std::vector<TData>::const_iterator itItem=m_vData.begin(); itItem!=itEnd; ++itItem)
	{
		std::string sData(m_bEscape ? CBasic::escape(itItem->sName) : itItem->sName);
		sData += m_sDelimPair;
		sData += m_bEscape ? CBasic::escape(itItem->sValue) : itItem->sValue;
		xData.push_back(sData);
	}
	return CBasic::StringJoin(xData, m_sDelimElem);
}

std::string CParamParse::ToString()
{
	std::vector<std::string> xData;
	std::vector<TData>::const_iterator itEnd = m_vData.end();
	--itEnd;
	for (std::vector<TData>::const_iterator itItem=m_vData.begin(); itItem!=itEnd; ++itItem)
	{
		std::string sData(m_bEscape ? CBasic::escape(itItem->sName) : itItem->sName);
		sData += m_sDelimPair;
		sData += m_bEscape ? CBasic::escape(itItem->sValue) : itItem->sValue;
		xData.push_back(sData);
	}
	return CBasic::StringJoin(xData, m_sDelimElem);
}
