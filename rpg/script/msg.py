#!/usr/bin/python
# -*- coding: UTF-8 -*-

import re
import json

pattern = r"\s+var\s(\w+).*\(function.*"


def _parse_value(t):
    v = t.strip()
    p = v.find(')')
    if p > 0:
        v = v[0:p]
    arr = v.split('.')
    if len(arr) == 0:
        return v
    v = None
    for i in arr:
        if i == 'Read':
            break
        if not v:
            v = i
        else:
            v += "::" + i
    return v


def _get_map(t):
    if len(t) < 2:
        return False
    k = _get_cpp_type(t[0].strip())
    if re.match(r'.*ReadMap.*', t[1]):
        return 'map<' + k + ', ' + _get_map(t[2:]) + '> '
    if re.match(r'.*ReadArray.*', t[1]):
        # print(t[2])
        return 'map<' + k + ', ' + _get_list(t[2:]) + '> '
    v = _parse_value(t[1])
    v = _get_cpp_type(v)
    return 'map<' + k + ', ' + v + '> '


def _get_list(t):
    v = _parse_value(t[0])
    v = _get_cpp_type(v)
    return 'vector<' + v + '> '


def _get_cpp_type(v):
    if v == 'gB':
        return 'bool'
    elif v == "ReadBool":
        return "bool"
    elif v == "gI1":
        return 'int8_t'
    elif v == "gI2":
        return 'int16_t'
    elif v == "gI4":
        return 'int32_t'
    elif v == "gI8":
        return 'int64_t'
    elif v == "gU1":
        return 'uint8_t'
    elif v == "gU2":
        return 'uint16_t'
    elif v == "gU4":
        return 'uint32_t'
    elif v == 'gU8':
        return 'uint64_t'
    elif v == "gDT":
        return 'int64_t'
    elif v == "gId":
        return 'Identity'
    elif v == "gIM":
        return 'Msg*'
    elif v == "gPt":
        return 'Point'
    elif v == "gS":
        return 'string'
    elif v == "ReadString":
        return 'string'
    elif v == 'ReadInt8':
        return 'int8_t'
    elif v == 'ReadInt16':
        return 'int16_t'
    elif v == 'ReadInt32':
        return 'int32_t'
    elif v == 'ReadInt64':
        return 'int64_t'
    elif v == 'ReadUInt8':
        return 'uint8_t'
    elif v == 'ReadUInt16':
        return 'uint16_t'
    elif v == 'ReadUInt32':
        return 'uint32_t'
    elif v == 'ReadUInt64':
        return 'uint64_t'
    elif v == 'ReadPoint':
        return 'Point'
    elif v == 'ReadIdentity':
        return 'Identity'
    elif v == 'ReadDateTime':
        return 'int64_t'
    elif v == 'ReadIMessage':
        return 'Msg*'
    else:
        return v


def _get_stype(t):
    v = t.strip()
    ret = re.findall(r'(DATA\.)?(\w+)\(.*\)', t)
    if len(ret) == 1:
        v = ret[0][1]
    return _get_cpp_type(v)


def _get_type(t):
    if re.match(r'ReadMap', t):
        arr = t.split(',')
        return _get_map(arr[1:])
    elif re.match(r'ReadArray', t):
        arr = t.split(',')
        return _get_list(arr[1:])
    else:
        return _get_stype(t)
    return t


if __name__ == "__main__":
    msg_name = None
    msg_read = None
    msg_cons = None
    msg_defs = None
    msg_endl = None
    msg_idx = {}
    msg_all = {}
    msg_all['msgs'] = list()
    msg_all['dbs'] = list()
    msg_all['apps'] = list()
    msg_all['oth'] = list()
    flag = 0
    index = 0
    msg_type = 'oth'

    fd = open("./message.js", "r")
    for line in fd.readlines():
        if re.match(r'.*\(function\s\(msgs\)\s\{.*', line):
            msg_type = 'msgs'
        if re.match(r'.*\(function\s\(dbs\)\s\{.*', line):
            msg_type = 'dbs'
        if re.match(r'.*\(function\s\(igameapp\)\s\{.*', line):
            msg_type = 'apps'
        if re.match(pattern, line):
            ret = re.findall(pattern, line)
            msg_name = ret[0]
            msg_cons = r'.*function\s' + msg_name + r'\(\)\s\{'
            msg_endl = r'\s+return\s' + msg_name + ';'
            msg_read = r'.*' + msg_name + r'\.prototype\.__read\s=\sfunction\s\(DATA\)\s\{.*'
            msg_item = {}
            msg_item['name'] = msg_name
            msg_item['extends'] = ''
            msg_all[msg_type].append(msg_item)
            msg_defs = {}
            msg_idx[msg_name] = len(msg_all[msg_type]) - 1

        if msg_name is None:
            continue

        ret = re.findall(msg_name + r'\.ID\s=\s(\d+);', line)
        if len(ret) == 1:
            idx = msg_idx[msg_name]
            msg_all[msg_type][idx]['id'] = ret[0]

        if re.match(msg_cons, line):
            flag = 2

        if re.match(msg_endl, line):
            flag = 3
            continue

        if re.match(msg_read, line):
            idx = msg_idx[msg_name]
            msg_all[msg_type][idx]['msg'] = list()
            flag = 1
            index = 1
            continue

        if flag == 1:
            if re.match(r'\s+\}', line):
                flag = 0
                continue
            if re.match(r'.*this\.\w+\s=\s.*', line):
                arr = line.split(r'=')
                k = arr[0].strip()
                arr1 = k.split(r'.')
                k = arr1[1]
                v = arr[1].strip()
                item = {}
                item['name'] = k + "_"
                item['id'] = index
                index += 1
                item['type'] = _get_type(v)
                idx = msg_idx[msg_name]
                msg_all[msg_type][idx]['msg'].append(item)
            elif re.match(r'\s+this\.\w+\.__read\(DATA\);', line):
                arr = line.split(".")
                k = arr[1]
                if not msg_defs or not msg_defs[k]:
                    print("===", msg_name, "====", k)
                    continue
                v = msg_defs[k]
                item = {}
                item['name'] = k + "_"
                item['id'] = index
                index += 1
                item['type'] = _get_type(v)
                idx = msg_idx[msg_name]
                msg_all[msg_type][idx]['msg'].append(item)

        if flag == 2:
            if re.match(r'\s+\}', line):
                flag = 0
                continue
            ret1 = re.findall(r'\s+_?this?\.(\w+)\s=\snew\s(.*)\(\);', line)
            if len(ret1) > 0:
                msg_defs[ret1[0][0]] = ret1[0][1].replace(".", "::")

        if flag == 3:
            flag = 0
            ret1 = re.findall(r'\}\((.+)\)\);', line)
            if len(ret1):
                idx = msg_idx[msg_name]
                msg_all[msg_type][idx]['extends'] = ret1[0].replace(".", "::")

    fd.close()

    fd = open('msgs.json', "w")
    json.dump(msg_all['msgs'], fd)
    fd.close()

    fd = open('dbs.json', "w")
    json.dump(msg_all['dbs'], fd)
    fd.close()

    fd = open('igameapp.json', "w")
    json.dump(msg_all['apps'], fd)
    fd.close()

    fd = open('oth.json', "w")
    json.dump(msg_all['oth'], fd)
    fd.close()