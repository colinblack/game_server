#!/bin/sh

if [ -z $2 ]; then
  echo "need act_name, true/false!"
  exit
fi

name=$1
all=$2

macro="CONFIG_$name"
macroline="#define $macro \"$name\""
sed -i "s/autolable1/autolable1\n$macroline/" kernel/AppDefine.h

nat="NAT_$macro"
num=`grep NAT_ kernel/AppDefine.h|grep =|awk -F'[=,]' '{a=$2}END{print a}'`
num=$((num+1))
natline="$nat			= $num,"
sed -i "s/NAT_MAX/$natline\nNAT_MAX/" kernel/AppDefine.h

timeline="$macro,"
sed -i "s/autolable2/autolable2\n$timeline/" logic/ActivityConfig.cpp

configline="CHARGE_DRAW_ACT_CONFIG($macro)"
sed -i "s/autolable3/autolable3\n$configline/" data/DataXML.h

getline="GET_CHARGE_DRAW_ACT_CONFIG($macro)"
sed -i "s/autolable4/autolable4\n$getline/" data/DataXML.h

initline="INIT_CHARGE_DRAW_ACT_CONFIG($macro)"
sed -i "s/autolable5/autolable5\n$initline/" data/DataXML2.cpp

drawline="CHARGE_DRAW_ACT($macro, $all)"
sed -i "s/autolable6/autolable6\n$drawline/" logic/LogicCmdUnits.h

actline="CHARGE_DRAW_ACT_ACTION_MAP($macro)"
sed -i "s/autolable7/autolable7\n$actline/" cgi/CgiSave.cpp

funcline="CHARGE_DRAW_ACT_ACTION_FUNCTION($macro)"
sed -i "s/autolable8/autolable8\n$funcline/" cgi/CgiSave.cpp
