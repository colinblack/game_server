#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
from lib.common import _parse_attribut
import sys
reload(sys)
sys.setdefaultencoding('utf8')


def is_career_skill(i):
    if i[3] > 0 and i[3] < 4 and i[43] != 9 and i[43] != 55 and i[
            43] != 58 and i[43] != 56 and i[43] != 36:
        return True
    return False


def is_shenqi_skill(i):
    if i[43] == 7:
        return True
    return False


def is_suit_skill(i):
    if i[43] == 41:
        return True
    return False
    
def is_zhanling_skill(i):
    if i[43] == 4:
        return True
    return False

def is_advance_skill(i):
    if i[43] == 210 or i[43] == 211:
        return True
    return False

def parse_skill():
    fd = open("src/preloadData.json", "r")
    data = json.load(fd)
    base_skill = {}
    skills = {}
    skills["skills"] = list()
    for i in data["t_skill_base"]:
        base_skill[i[7]] = i[5]
    for i in data["t_skill"]:
        if is_career_skill(i) or is_shenqi_skill(i) or is_suit_skill(i) or is_zhanling_skill(i) or is_advance_skill(i):
            item = {}
            item["buff"] = i[0]
            item["career"] = i[3]
            item["serial"] = i[28]
            item["name"] = i[20]
            item["id"] = i[31]
            item["cd"] = i[24]
            item["range"] = i[8]
            item["range2"] = i[35]
            item["type"] = i[42]
            item["type2"] = i[43]
            item["hurt"] = i[11]
            try:
                item["hurtAdd"] = int(i[15])
            except:
                item["hurtAdd"] = 0
            item["level"] = i[32]
            item["unlock"] = i[16]
            item["cost"] = i[17]
            item["careerlevel"] = i[4]
            item["zhanlinghurt"] = i[19]
            attrs = list()
            attr = i[9].split(r'#')
            if len(attr) == 3:
                attrs.append(attr)
            item["attr"] = _parse_attribut(attrs)
            skills["skills"].append(item)
    fd.close()

    fd = open("tar/skills.json", "w")
    json.dump(skills, fd, ensure_ascii=False, indent=2)
    fd.close()


def parse_base():
    fd = open("src/preloadData.json", "r")
    data = json.load(fd)
    skills = {}
    skills["bases"] = list()
    for i in data["t_skill_base"]:
        item = {}
        item["cost"] = i[0]
        item["xishu"] = i[1]
        item["hurt"] = i[2]
        item["unlocklevel"] = i[3]
        item["hurtAdd"] = i[4]
        item["maxLevel"] = i[5]
        item["learnLevel"] = i[6]
        item["id"] = i[7]
        skills["bases"].append(item)
    fd.close()
    fd = open("tar/skill_bases.json", "w")
    json.dump(skills, fd, ensure_ascii=False, indent=2)
    fd.close()


def parse_monster_skill():
    fd = open("src/preloadData.json", "r")
    data = json.load(fd)
    skills = {}
    skills["skills"] = list()
    for i in data["t_skill_monster"]:
        item = {}
        item["buff"] = i[0]
        item["career"] = i[3]
        item["serial"] = i[28]
        item["name"] = i[20]
        item["id"] = i[31]
        item["cd"] = i[24]
        item["range"] = i[8]
        item["range2"] = i[35]
        item["type"] = i[42]
        item["type2"] = i[43]
        item["hurt"] = i[11]
        item["level"] = i[32]
        item["unlock"] = i[16]
        item["cost"] = i[17]
        skills["skills"].append(item)
    fd.close()
    fd = open("tar/skill_monsters.json", "w")
    json.dump(skills, fd, ensure_ascii=False, indent=2)
    fd.close()


if __name__ == "__main__":
    parse_skill()
    #parse_base()
    #parse_monster_skill()
