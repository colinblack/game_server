#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import io

def parse_shop_cell():
    fd = io.open("./src/t_shop_sell.json", "r", encoding="utf-8")
    data = json.load(fd)
    shop_cell = {}
    shop_cell["shop_cell"] = []
    for i in data:
        item = {}
        item['id'] = int(i[7])
        item['item_id'] = int(i[8])
        item['buy_limit'] = int(i[9])
        item['num'] = int(i[21])
        item['real_price'] = int(i[24])
        item['money_type'] = int(i[26])
        item['limit_type'] = int(i[10])
        shop_cell['shop_cell'].append(item)
    fd.close()
    fd = open('tar/shop_sell.json', 'w')
    json.dump(shop_cell, fd, ensure_ascii=False, indent=2)


if __name__ == "__main__":
    parse_shop_cell()