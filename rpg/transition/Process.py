#!/usr/bin/python
# -*- coding: UTF-8 -*-

import xlrd
from lib.Parser import SheetParser

if __name__ == "__main__":
    configs = xlrd.open_workbook(r'src/transition.xlsx')
    csheet = configs.sheet_by_name(r'configs')
    for i in range(csheet.nrows):
        if i < 1:
            continue
        xls_name = 'src/' + str(csheet.cell_value(i, 0))
        sheet_name = csheet.cell_value(i, 1)
        json_name = 'tar/' + str(csheet.cell_value(i, 2))
        cfg_name = str(csheet.cell_value(i, 3))
        if len(xls_name) == 0:
            continue

        print(xls_name, sheet_name, json_name)
        workbook = xlrd.open_workbook(xls_name)
        sheet = workbook.sheet_by_name(sheet_name)
        oo = SheetParser()
        oo.ParseKey(sheet)
        oo.ParseType(sheet)
        oo.ParseData(sheet)
        oo.Save(json_name, cfg_name)
