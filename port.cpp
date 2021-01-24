#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cstring>
#include "port.h"

Port::Port(String pattern): Field(pattern, PORT){}

/**
 * this function determines the range of the leagal ports.
 */
bool Port::set_value(String val){
	String *str;
	size_t size = 0;

	val.split("-" , &str , &size);
	if(size != 2){
		delete[] str;
		return false;
	} else{
		range[0] = str[0].trim().to_integer();
		range[1] = str[1].trim().to_integer();
		delete[] str;
	}
	if(range[0] > range[1]){
		return false;
	} else{
		return true;
	}
}

/**
 * this function checks if the port in the given string has a legal value.
 */
bool Port::match_value(String val) const{
	int port_temp;
	port_temp = val.trim().to_integer();
	if(port_temp < range[0] || port_temp > range[1]){
		return false;
	} else{
		return true;
	}
}



