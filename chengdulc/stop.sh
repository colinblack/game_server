#!/bin/bash

kill -9 `ps -ef|grep luanchu |grep -v 'grep'|awk 'NR==1{print $2}'`
