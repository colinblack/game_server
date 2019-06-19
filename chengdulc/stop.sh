#!/bin/bash

kill -9 `ps -ef|grep leshaneqs|grep -v 'grep'|awk 'NR==1{print $2}'`
