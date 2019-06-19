#!/bin/bash

count=0

while [ $count -lt 9 ];do
	echo "$count"
	./stop.sh
	sleep 2
	./start.sh
	sleep 4
	count=$(($count+1))
done
