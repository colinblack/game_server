/*
 * NpcManager.cpp
 *
 *  Created on: 2018年7月31日
 *      Author: rein
 */

#include "NpcManager.h"

NpcManager::NpcManager() {
}

NpcManager::~NpcManager() {
}

bool NpcManager::GetNpc(uint32_t id, IBuffer *buffer) {
	if (!m_npc.count(id) && !LoadNpc(id)) {
		return false;
	}
	return Encode(m_npc[id], buffer);
}

bool NpcManager::LoadNpc(uint32_t id) {
	string path = Config::GetValue(CONFIG_NPC_PATH);
	if (path.empty()) {
		error_log("npc path empty id=%u", id);
		return false;
	}
	if (path[path.length() - 1] != '/') {
		path.append("/");
	}
	path.append(CTrans::ITOS(id)).append(".txt");
	string buff;
	int ret = File::Read(path, buff);
	if (ret != 0) {
		error_log("npc file read error id=%u path=%s", id, path.c_str());
		return false;
	}
	Json::Value value;
	Json::Reader reader;
	if (!reader.parse(buff, value)) {
		error_log("npc data parse error id=%u err=%s", id, reader.getFormatedErrorMessages().c_str());
		return false;
	}
	NpcInfo &npc = m_npc[id];
	for (size_t i = 0; i < value["troops"].size(); ++i) {
		TroopsInfo t;
		t.FromJson(value["troops"][i]);
		npc.troops.push_back(t);
	}
	for (size_t i = 0; i < value["soldier"].size(); ++i) {
		Soldier s;
		s.setData(Json::ToString(value["soldier"][i]));
		npc.soldier.push_back(s);
	}
	for (size_t i = 0; i < value["gem"].size(); ++i) {
		DataGemPoint s;
		Json::GetUInt(value["gem"][i], "id", s.id);
		Json::GetUInt(value["gem"][i]["point"], 0u, s.p1);
		Json::GetUInt(value["gem"][i]["point"], 1u, s.p2);
		Json::GetUInt(value["gem"][i]["point"], 2u, s.p3);
		Json::GetUInt(value["gem"][i]["point"], 3u, s.p4);
		npc.gem.push_back(s);
	}
	Json::GetString(value, "name", npc.name);
	return true;
}

string NpcManager::GetNpcName(uint32_t id) {
	if (!m_npc.count(id) && !LoadNpc(id)) {
		return "";
	}
	return m_npc[id].name;
}

bool NpcManager::Encode(NpcInfo &data, IBuffer *buffer) {
	CBufferWriter writer(buffer);
	writer.AppendUInt32(data.troops.size());
	vector<TroopsInfo>::iterator itr =  data.troops.begin();
	for (; itr != data.troops.end(); ++itr) {
		writer.AppendUInt32(itr->id);
		writer.AppendUInt32(itr->value);
	}

	writer.AppendUInt32(data.soldier.size());
	vector<Soldier>::iterator it = data.soldier.begin();
	for (; it != data.soldier.end(); ++it) {
		it->encode(buffer);
	}

	writer.AppendUInt32(data.gem.size()); // gem size
	vector<DataGemPoint>::iterator gitr = data.gem.begin();
	for (; gitr != data.gem.end(); ++gitr) {
		PACKET_ENCODE(UInt32, gitr->id);
		PACKET_ENCODE(UInt32, 4);
		PACKET_ENCODE(UInt32, gitr->p1);
		PACKET_ENCODE(UInt32, gitr->p2);
		PACKET_ENCODE(UInt32, gitr->p3);
		PACKET_ENCODE(UInt32, gitr->p4);
	}

	debug_log("troops size %u soldier size %u gem size %u", data.troops.size(), data.soldier.size(), data.gem.size());

	return true;
}
