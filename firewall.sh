#!/bin/bash
while read line
do
	pkts=""
	line=` echo "$line" | tr -d ' ' | sed -e 's/#.*//' `
	if [ "$line" == "" ];  then
		continue
	fi
	readarray -d , arr <<< "$line" 
	for i in "${arr[@]}"
	do
		pkts+=`./firewall.exe  "$i" < $1 ` 
		pkts+="\n"
	done
	list+=`echo -e "${pkts}"  |                             \
	sed '/^$/d' | sort | uniq -c |                                     \
	grep -E "^[ ]*${#arr[@]} " | sed -e "s/^[ ]*${#arr[@]} //"`
	list+="\n"
done
echo -e "${list}" | sed '/^$/d' | tr -d ' ' | sort
