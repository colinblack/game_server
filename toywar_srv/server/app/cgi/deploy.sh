#/bin/sh
dir=`dirname $0`
for cgi in `ls "$dir" | grep "Cgi[^\.]*$"`
	do cp "$dir/$cgi" /data/release/toywar/cgi/ -f
	echo "$dir/$cgi"
	done
cd /data/release/toywar/lighttpd/sbin
./restart.sh
cd -
