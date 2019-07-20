/*
 * DataLocal.h
 *
 *  Created on: 2019年7月18日
 *      Author: Administrator
 */

#ifndef DATA_LOCAL_H_
#define DATA_LOCAL_H_

#include "Kernel.h"
#include <iostream>
#include <fstream>

template<typename T>
class DataLocal {
public:
	DataLocal() {
	}
	virtual ~DataLocal() {
	}
	virtual bool Init() {
		if (m_path.empty()) {
			error_log("not init");
			return false;
		}
		m_msg.Clear();
		fstream input(m_path.c_str(), ios::in | ios::binary);
		if (!input.good()) {
			return true;
		} else if (!m_msg.ParseFromIstream(&input)) {
			error_log("parse %s fail", m_path.c_str());
			return false;
		}
		if (!Parse()) {
			return false;
		}
		m_msg.Clear();
		return true;
	}
	virtual bool Save(void) {
		if (m_path.empty()) {
			error_log("not init");
			return false;
		}
		m_msg.Clear();
		if (!Serialize()) {
			error_log("serialize error");
			return false;
		}
		fstream output(m_path.c_str(), ios::out | ios::trunc | ios::binary);
		if (!output.good()) {
			error_log("open file error");
			return false;
		}
		if (!m_msg.SerializeToOstream(&output)) {
			error_log("serialize %s fail", m_path.c_str());
			return false;
		}
		m_msg.Clear();
		return true;
	}
	virtual bool Parse() = 0;
	virtual bool Serialize() = 0;
protected:
	T m_msg;
	string m_path;
};

#endif /* DATA_LOCAL_H_ */
