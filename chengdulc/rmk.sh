#!/bin/bash
./stop.sh
cd ./libphz/;make clean;make lib
cd ../protoco/;make clean;make cc
cd ../;make clean;make