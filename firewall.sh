#!/bin/bash
while read pkt
do
	if [ "$pkt" != "" ]; then
		readarray -d , tmp <<< "$1" 
	fi
	while read line
	do
		matched_packets=""
		line=` echo "$line" | sed 's/ //g' | cut -f1 -d  "#" `
		if [ "$line" == "" ];  then
			continue
		fi
		readarray -d , arr <<< "$line" 
		for i in "${arr[@]}"
		do
			matched_packets+=`echo "$pkt" | ./firewall.exe  "$i" ` 
			matched_packets+="\n"
		done
		list+=`echo -e "${matched_packets}"  |                             \
		sed '/^$/d' | sort | uniq -c |                                     \
		grep -E "^[ ]*${#arr[@]} " | sed -e "s/^[ ]*${#arr[@]} //"`
		list+="\n"
		if [ "$tmp" == "0" ]; then
			echo -e FAIL
		fi
	done < "$1" 
done
echo -e "${list}" | sed '/^$/d' | sed 's/ //g' | sort
