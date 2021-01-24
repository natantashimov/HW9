#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cstring>
#include <iostream>
#include "ip.h"

Ip::Ip(String pattern): Field(pattern, IP){}

/**
 * this function set the legal high and low addresses,
 * according to the given address
 */
bool Ip::set_value(String val){
	String* ip_temp;
	size_t size = 0;
	
	val.split("/", &ip_temp, &size);
	if(size == 2){
		int ip = ip_temp[0].trim().to_integer();
		int bit_num = ip_temp[1].trim().to_integer();
		delete[] ip_temp;

		if(bit_num > 32 || bit_num < 0){
			return false;
		}
		if(bit_num == 0){
			high = 0xFFFFFFFF;
			low = 0x00000000;
		} else{
			unsigned int temp = 0xFFFFFFFF << (32 - bit_num);
			high = ip | (~temp) ;
			low = ip & temp ;
		}
		return true;
	} else{
		if(size != 0){
			delete[] ip_temp;
		}
	}
	return false;
}

/**
 * this function checks if the ip in given string has a legal value.
 */
bool Ip::match_value(String val) const{
	int ip = val.trim().to_integer();
	if( ((unsigned int)ip < low) || ((unsigned int)ip > high) ){
		return false;
	} else{
		return true;
	}
}
