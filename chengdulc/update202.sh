#!/bin/bash

cd /home/mengrui/30server/202server/leiyangphz
kill -9 `cat conf/leiyangphz.pid`
rm log/*
cp /home/mengrui/30server/paohuzi/leiyangphz/leiyangphz ./ -f
./leiyangphz -f conf/leiyangphz.conf -D
sleep 1
ps -ef | grep leiyangphz
