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
accthumbsupRank="/data/release/sg17/s1/webroot/rankdata/accthumbsup_rank.json"

###########################累积被点赞排行#####################
echo '{"rank":[' > ${accthumbsupRank}
count=0
for db in ${HOSTNAMES[@]};
do
	MYSQL="mysql -h${db}  -P${PORT}  -u${USERNAME} -p${PASSWORD}"
    for ((index=0;index<${PERDBNUM};index++))
    do
    	select_sql="select uid,level,accthumbsup from base where accthumbsup > 0 order by accthumbsup desc limit ${LIMITNUM}"
    	dbnum=$[count*PERDBNUM+index];
    	result="$($MYSQL sg17_s$dbnum -e "$select_sql")"
		echo "serverid $dbnum $result" |  awk -F ' ' 'BEGIN{flag=0}{
							if($1=="serverid") {
								print "{"
								print        "\"serverid\":"$2 ","
								print        "\"accthumbsup_rank\":["
							}
							else{
								if(flag==1)
									print ","
								print"{\"uid\":"$1 ",\"level\":"$2  ",\"accthumbsup\":"$3 "}"
								flag=1;
							}
						}' >> ${accthumbsupRank} 
		if [ $dbnum == $[DBNUM - 1] ]; then
   			echo ']}' >> ${accthumbsupRank}
		else
    		echo ']},' >> ${accthumbsupRank}
		fi
    done
	count=$[count+1];
done
echo ']}' >>${accthumbsupRank}