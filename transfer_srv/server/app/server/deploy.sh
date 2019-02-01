#/bin/sh
dir=`dirname $0`
/data/release/toywar/server/StopServer.sh
sleep 1
cp "$dir/toyward" /data/release/toywar/server/
/data/release/toywar/server/toyward
