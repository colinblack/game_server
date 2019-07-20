#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import io
from Attr import Attr
from Reward import Reward
from ListInt import ListInt
from StarRate import StarRate


class SheetParser(object):
    def __init__(self):
        self.__keys = {}
        self.__type = {}
        self.__data = list()

    def ParseKey(self, sheet):
        for i in range(sheet.ncols):
            v = sheet.cell_value(2, i)
            if v:
                self.__keys[i] = v

    def ParseType(self, sheet):
        for i in range(sheet.ncols):
            v = sheet.cell_value(1, i)
            if v:
                self.__type[i] = v

    def ParseData(self, sheet):
        for i in range(sheet.nrows):
            if i <= 3:
                continue
            item = {}
            for k in self.__keys.keys():
                t = self.__type[k]
                v = sheet.cell_value(i, k)
                n = self.__keys[k]
                item[n] = self.ParseValue(v, t)
            self.__data.append(item)

    def ParseValue(self, v, t):
        if t == 'int':
            return int(v)
        elif t == 'str':
            return str(v)
        elif t == 'attr':
            return Attr(str(v))
        elif t == 'reward':
            return Reward(str(v))
        elif t == 'listint':
            return ListInt(str(v))
        elif t == 'starrate':
            return StarRate(str(v))
        return 0

    def Save(self, f, c):
        data = {}
        data[c] = self.__data
        buff = json.dumps(data, ensure_ascii=False, indent=2)
        with io.open(f, 'w', encoding="utf-8") as outfile:
            outfile.write(unicode(buff))
