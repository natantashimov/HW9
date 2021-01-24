#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cstring>
#include <iostream>

#include "field.h"
#include "port.h"
#include "ip.h"



Field::Field(String pattern, field_type type):
pattern(pattern), type(type){}



Field::Field(String pattern): pattern(pattern){
	type = GENERIC;
}



Field::~Field(){
}


field_type Field::get_type() const{
	return type;
}



bool Field::set_value(String val){
	if(type == IP){
		return ((Ip*)this)->set_value(val);
	} else{
		if(type == PORT){
			return ((Port*)this)->set_value(val);
		}
	}
	return false;
}




bool Field::match_value(String val) const{
	if(type == IP){
		return ((Ip*)this)->match_value(val);
	} else{
		if(type == PORT){
			return ((Port*)this)->match_value(val);
		}
	}
	return false;
}






bool Field::match(String packet){
	String *packet_temp, *sub_packet;
	size_t packets_count = 0;
	size_t size = 0;
	bool is_match = false;
	
	packet.split(",", &packet_temp, &packets_count);
	if (!packets_count){
		return false;
	} 

	
	for(unsigned int i = 0; i < packets_count; i++){
		packet_temp[i].split("=", &sub_packet, &size);
		if (size == 2){
			if ( pattern.trim().equals(sub_packet[0].trim()) ){
				is_match = match_value(sub_packet[1].trim());
			}
		}else{
			if (size != 0){
			delete[] sub_packet;
			}
		}
		
	}
	delete[] packet_temp;
	return is_match;
}
