#!/usr/bin/python
# -*- coding: UTF-8 -*-
import re


class ListInt(list):
    def __init__(self, v):
        list.__init__(self)
        flag = '#'
        if re.match(r'((\w+)&(\w+))+', v):
            flag = '&'
        arr = v.split(flag)
        for i in arr:
            if re.match(r'.', i):
                self.append(int(float(i)))
            else:
                self.append(int(i))
