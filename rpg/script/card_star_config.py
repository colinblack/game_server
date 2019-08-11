#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import io
from lib.common import _parse_attribut, _parse_reward

def parse_card_star():
    fd = open("src/t_card_star.json", "r")
    data = json.load(fd)
    stars = {}
    stars["star"] = list()
    for i in data:
        item = {}
        item["attr"] = _parse_attribut(i[0])
        item["exp"] = int(i[1])
        item["color"] = int(i[2])
        item["level"] = int(i[3])
        stars["star"].append(item)
    fd.close()
    fd = open("tar/card_star.json", "w")
    json.dump(stars, fd, ensure_ascii=False, indent=2)

if __name__ == "__main__":
    parse_card_star()