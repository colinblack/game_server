#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import io

def parse_item_money():
    fd = io.open("./src/t_item_money.json", "r", encoding="utf-8")
    data = json.load(fd)
    item_money = {}
    item_money["item_money"] = []
    for i in data:
        item = {}
        item['id'] = int(i[1])
        item['limit'] = int(i[9])
        item_money['item_money'].append(item)
    fd.close()
    fd = open('tar/item_money.json', 'w')
    json.dump(item_money, fd, ensure_ascii=False, indent=2)


if __name__ == "__main__":
    parse_item_money()