#!/bin/sh
cd `pwd`
protoc -I=. --cpp_out=. $1.proto
Proto2AS $1.proto
sed -i '3i\import com.sanguo.game.server.ServerManager;' *.as
sed -i '3s/^/	/' *.as
sed -i 's/message = root.lookup(PROTO)/message = ServerManager.getProtoMsg(PROTO)/g' *.as
mkdir $1
mv -f *.as $1
rm -rf ../as/$1
mv -f $1/ ../as
cp $1.proto ../as
