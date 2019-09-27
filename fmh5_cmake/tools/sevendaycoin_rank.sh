#!/bin/bash
###########数据库信息################
#HOSTNAMES=("10.214.195.42" "10.214.194.181" "10.214.197.39" "10.214.194.72")
HOSTNAMES=("192.168.100.237")
PORT="3306"
USERNAME="root"
PASSWORD="1234"
DBNAME="sg17_s"


##########其它变量信息
#PERDBNUM=10
#DBNUM=40
PERDBNUM=3
DBNUM=3
LIMITNUM=100
sevenDayCoinRank="/data/release/sg17/s1/webroot/rankdata/sevendaycoin_rank.json"

###########################商店近七日金币收入排行#####################
##########获取昨日起始时间戳
MYDATE=$(date -d -7day +%Y%m%d);
STATICTS=$(date -d ${MYDATE} +%s)

##########连表统计
echo '{"rank":[' > ${sevenDayCoinRank}
count=0
for db in ${HOSTNAMES[@]};
do
	MYSQL="mysql -h${db}  -P${PORT}  -u${USERNAME} -p${PASSWORD}"
    for ((index=0;index<${PERDBNUM};index++))
    do
    	select_sql="select base.uid,base.level,data,base.accthumbsup from (select uid,sum(value) data from shopSellCoin where id >= ${STATICTS} group by uid order by data desc limit ${LIMITNUM})a join base on(a.uid=base.uid)"
    	dbnum=$[count*PERDBNUM+index];
    	result="$($MYSQL sg17_s$dbnum -e "$select_sql")"
		echo "serverid $dbnum $result" |  awk -F ' ' 'BEGIN{flag=0}{
							if($1=="serverid") {
								print "{"
								print        "\"serverid\":"$2 ","
								print        "\"sevendaycoin_rank\":["
							}
							else{
								if(flag==1)
									print ","
								print"{\"uid\":"$1 ",\"level\":"$2   ",\"sevendaycoin\":" $3  ",\"accthumbsup\":"$4 "}"
								flag=1;
							}
						}' >> ${sevenDayCoinRank} 
		if [ $dbnum == $[DBNUM - 1] ]; then
   			echo ']}' >> ${sevenDayCoinRank}
		else
    		echo ']},' >> ${sevenDayCoinRank}
		fi
    done
	count=$[count+1];
done
echo ']}' >>${sevenDayCoinRank}