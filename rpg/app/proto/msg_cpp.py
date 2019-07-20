#!/usr/bin/python
# -*- coding: UTF-8 -*-

import json
import re
import sys


def _get_cpp_type(t):
    if t == 'int8_t':
        return 'Byte'
    elif t == 'int16_t':
        return 'Int16'
    elif t == 'int32_t':
        return 'Int32'
    elif t == 'int64_t':
        return 'Int64'
    elif t == 'uint8_t':
        return 'Byte'
    elif t == 'uint16_t':
        return 'UInt16'
    elif t == 'uint32_t':
        return 'UInt32'
    elif t == 'uint64_t':
        return 'UInt64'
    elif t == 'bool':
        return 'Bool'
    elif t == 'double':
        return 'Int64'
    elif t == 'string':
        return 'String'
    return None


def _get_map_value_decode(n, t, num):
    vt = _get_cpp_type(t)
    if vt:
        return "PACKET_DECODE(" + vt + "," + n + ");"
    vt = _get_map_decode(n, t, num + 1)
    if vt:
        return vt
    vt = _get_list_decode(n, t)
    if vt:
        return vt
    if t == "Msg*":
        return n + " = MsgPool::Instance()->DecodeMsg(reader);"
    return "if(!" + n + ".decode(reader)){return false;}"


def _get_map_decode(n, t, num=0):
    if not re.match(r'map<.*', t):
        return None
    pos = t.find(',')
    if pos == 0:
        return None
    k = t[0:pos]
    v = t[pos + 1:]
    k = k.strip()
    v = v.strip()
    k = k[4:]
    v = v[0:-1].strip()

    kn = ""
    vn = ""
    ln = ""
    idn = ""
    if num:
        kn = "k{0}".format(num)
        vn = "v{0}".format(num)
        ln = "len{0}".format(num)
        idn = "i{0}".format(num)
    else:
        kn = "k"
        vn = "v"
        ln = "len"
        idn = "i"
    cpp = "{uint32_t " + ln + "=0;"
    cpp += "PACKET_DECODE(UVar32," + ln + ");"

    cpp += "for(uint32_t " + idn + "=0;"
    cpp += idn + "<" + ln + ";++" + idn + "){"
    cpp += k + " " + kn + ";" + v + " " + vn + ";"
    kt = _get_cpp_type(k)
    if kt:
        cpp += "PACKET_DECODE(" + kt + "," + kn + ");"
    else:
        cpp += "if(!k.decode(reader)){return false;}"
    cpp += _get_map_value_decode(vn, v, num)
    cpp += n + "[" + kn + "] = " + vn + ";"
    cpp += "}"
    cpp += "}\n"
    return cpp


def _get_map_value_encode(n, t, num):
    vt = _get_cpp_type(t)
    if vt:
        return "PACKET_ENCODE(" + vt + "," + n + ");"
    vt = _get_map_encode(n, t, num + 1)
    if vt:
        return vt
    vt = _get_list_encode(n, t)
    if vt:
        return vt
    if t == "Msg*":
        cpp = "if(!MsgPool::Instance()->EncodeMsg(writer,"
        cpp += n + ")){return false;}"
        return cpp
    return "if(!" + n + ".encode(writer)){return false;}"


def _get_map_encode(n, t, num=0):
    if not re.match(r'map<.*', t):
        return None
    pos = t.find(',')
    if pos == 0:
        return None
    k = t[0:pos]
    v = t[pos + 1:]
    k = k.strip()
    v = v.strip()
    k = k[4:]
    v = v[0:-1].strip()
    ln = ""
    if num:
        ln = "it{0}".format(num)
    else:
        ln = "it"
    cpp = "PACKET_ENCODE(UVar32," + n + ".size());\n"
    cpp += "for(" + t + "::const_iterator " + ln + "=" + n + ".begin();"
    cpp += ln + "!=" + n + ".end();++" + ln + "){"
    kt = _get_cpp_type(k)
    if kt:
        cpp += "PACKET_ENCODE(" + kt + "," + ln + "->first);"
    else:
        cpp += "if(!" + ln + "->first.encode(writer)){return false;}"
    cpp += _get_map_value_encode(ln + "->second", v, num)
    cpp += "}\n"
    return cpp


def _get_list_encode(n, t, num=0):
    ret = re.findall(r'vector<(.*)>', t)
    if len(ret) == 0:
        return None
    vt = ret[0]
    ln = ""
    if num:
        ln = "vit{0}".format(num)
    else:
        ln = "vit"
    cpp = "PACKET_ENCODE(UVar32," + n + ".size());\n"
    cpp += "for(vector<" + vt + ">::const_iterator " + ln + "=" + n + ".begin();"
    cpp += ln + "!=" + n + ".end();++" + ln + "){"
    vtt = _get_cpp_type(vt)
    if vtt:
        cpp += "PACKET_ENCODE(" + vtt + ",*" + ln + ");"
    elif vt == "Msg*":
        cpp += "if(!MsgPool::Instance()->EncodeMsg(writer, *" + ln + "))"
        cpp += "{return false;}"
    else:
        cpp += "if(!" + ln + "->encode(writer)){return false;}"
    cpp += "}\n"
    return cpp


def _get_list_decode(n, t, num=0):
    ret = re.findall(r'vector<(.*)>', t)
    if len(ret) == 0:
        return None
    vt = ret[0]
    ln = ""
    vn = ""
    if num:
        ln = "vlen{0}".format(num)
        vn = "item{0}".format(num)
    else:
        ln = "vlen"
        vn = "item"
    cpp = "{uint32_t " + ln + "=0;PACKET_DECODE(UVar32," + ln + ");"
    cpp += vt + " " + vn + ";"
    cpp += "for(uint32_t vi=0;vi<" + ln + ";++vi){"
    vtt = _get_cpp_type(vt)
    if vtt:
        cpp += "PACKET_DECODE(" + vtt + "," + vn + ");"
    elif vt == "Msg*":
        cpp += vn + " = MsgPool::Instance()->DecodeMsg(reader);"
    else:
        cpp += "if(!" + vn + ".decode(reader)){return false;}"
    cpp += n + ".push_back(" + vn + ");}"
    cpp += "}\n"
    return cpp


if __name__ == "__main__":
    fn = sys.argv[1]
    fd = open(fn + '.json', 'rb')
    msgs = json.load(fd)

    fd_cpp = open(msgs['filename'] + '.cpp', 'w')
    fd_chh = open(msgs['filename'] + '.h', 'w')

    h_def = '_' + msgs['filename'].upper() + '_MSG_H_'

    cpps = list()
    chhs = list()
    chhs.append('#ifndef ' + h_def + "\n")
    chhs.append('#define ' + h_def + "\n")
    for inc in msgs['include']:
        chhs.append('#include "' + inc + '.h"\n')

    cpps.append('#include "' + msgs['filename'] + ".h\"\n")
    cpps.append('#include "MsgPool.h"\n')
    cpps.append('namespace ' + msgs['namespace'] + "{\n")
    chhs.append('namespace ' + msgs['namespace'] + "{\n")

    msg = msgs['msgs']
    for k in range(len(msg)):
        if len(msg[k].keys()) == 0  or r'msg' not in msg[k]:
            continue
        ext = "Msg"
        if r'extends' in msg[k] and msg[k]["extends"]:
            ext = msg[k]["extends"]
        chh = 'class ' + msg[k]['name'] + ': public ' + ext + ' {' + "\n"
        chh += "public:\n"
        for i in msg[k]['msg']:
            chh += i['type'].strip() + ' ' + i['name'] + ';' + "\n"
        chh += 'virtual inline int32_t msgId() const {return ' + msg[k][
            'id'] + ";}\n"
        chh += 'static int32_t MsgId() {return ' + msg[k][
            'id'] + ";}\n"
        chh += "virtual bool decode(CBufferReader &reader);\n"
        chh += "virtual bool encode(CBufferWriter &writer) const;\n"
        chh += "virtual void clear();\n"
        chh += "virtual Msg* New() const {return new " + msg[k]['name'] + "();}\n"
        chh += "};\n"
        chhs.append(chh)

        cpp = "bool " + msg[k]['name'] + "::decode(CBufferReader &reader) {\n"
        if ext != 'Msg':
            cpp += "if(!" + ext + "::decode(reader)){return false;}\n"
        for i in range(len(msg[k]['msg'])):
            for ii in msg[k]['msg']:
                if int(ii['id']) != i + 1:
                    continue
                mt = ii['type'].strip()
                t = _get_cpp_type(mt)
                if t:
                    cpp += 'PACKET_DECODE(' + t + ',' + ii['name'] + ");\n"
                    continue
                m = _get_map_decode(ii['name'], mt)
                if m:
                    cpp += m
                    continue
                v = _get_list_decode(ii['name'], mt)
                if v:
                    cpp += v
                    continue
                if mt == "Msg*":
                    cpp += ii['name']
                    cpp += " = MsgPool::Instance()->DecodeMsg(reader);\n"
                    continue

                cpp += "if(!" + ii['name']
                cpp += ".decode(reader)){return false;}\n"

        cpp += "return true;}\n"

        cpp += "bool " + msg[k]['name'] + "::encode(CBufferWriter &writer) const {\n"
        if ext != 'Msg':
            cpp += "if(!" + ext + "::encode(writer)){return false;}\n"
        for i in range(len(msg[k]['msg'])):
            for ii in msg[k]['msg']:
                if int(ii['id']) != i + 1:
                    continue
                mt = ii['type'].strip()
                t = _get_cpp_type(mt)
                if t:
                    cpp += 'PACKET_ENCODE(' + t + ',' + ii['name'] + ");\n"
                    continue
                m = _get_map_encode(ii['name'], mt)
                if m:
                    cpp += m
                    continue
                v = _get_list_encode(ii['name'], mt)
                if v:
                    cpp += v
                    continue
                if mt == "Msg*":
                    cpp += "if(!MsgPool::Instance()->EncodeMsg(writer, "
                    cpp += ii['name'] + ")){return false;}\n"
                    continue
                cpp += "if(!" + ii['name']
                cpp += ".encode(writer)){return false;}\n"
        cpp += "return true;}\n"

        cpp += "void " + msg[k]['name'] + "::clear(){\n"
        for i in msg[k]['msg']:
            if i['type'] == 'Msg*':
                cpp += i['name'] + ' = NULL;\n'
                continue
            t = _get_cpp_type(i['type'])
            if not t or t == "String":
                cpp += i['name'] + '.clear();\n'
            else:
                cpp += i['name'] + ' = 0;\n'
        cpp += "}\n"

        cpps.append(cpp)

    cpps.append('}')
    chhs.append('}\n\n')
    chhs.append('#endif')

    fd_cpp.writelines(cpps)
    fd_chh.writelines(chhs)
    fd_cpp.close()
    fd_chh.close()
