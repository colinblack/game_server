#!/bin/sh

if [ "X$1" == "X" ];
then
	for f in `ls *.proto`
	do
		fn=`echo $f | awk -F"." '{print $1}'`
		echo $fn
		protoc -I=. --cpp_out=. $fn.proto
		mv $fn.pb.cc $fn.pb.cpp
	done

else
	protoc -I=. --cpp_out=. $1.proto
	mv $1.pb.cc $1.pb.cpp
fi
