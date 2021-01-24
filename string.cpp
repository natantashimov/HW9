#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cstring>
#include "string.h"

#define IP_SIZE 4
#define MAX_INT 255


/**
 * a non-parameteric constructor
 */
String::String(){
	data = NULL;
	length = 0;
}
/**
 * copy constructor
 */
String::String(const String &str){
	length = str.length;
	if(length == 0){
		data = NULL;
	} else{
		data = new char[length+1];
		strcpy(data , str.data);	
	}
}
/**
 * a parameteric constructor
 */
String::String(const char *str){
	if(str == NULL){  
		length = 0;
		data = NULL;
	} else{
		length = strlen(str);
		data = new char[length+1];
		strcpy(data , str);
	}
}

/**
 * destructor
 */
String::~String(){
	delete[] data;	
}

/**
 * apply operator
 */
String& String::operator=(const String &rhs){
	if (this == &rhs){
		return *this;
	}
	else{
		if(data != NULL){
				delete[] data;
		}
	}
	length = rhs.length;
	if(length == 0){
		data = NULL;
	} else{
		data = new char[length+1];
		strncpy(data , rhs.data, length+1);
	}
	return *this;
}

/**
 * apply operator
 */
String& String::operator=(const char *str){
	if(str == NULL){
		length = 0;
		data = NULL;
	} else{
		delete[] data;
		length = strlen(str);
		if(length == 0){
			data = NULL;
		} else{
			data = new char[length+1];
			strcpy(data , str);
		}
	}
	return *this;
}

/**
 * this function checks if the given string is equal to this.
 */

bool String::equals(const String &rhs) const{
	if(length != rhs.length){
		return false;
	} else{
		if(strcmp(data , rhs.data)){
			return false;
		} else{
			return true;
		}
	}
	return false;
}

/**
 * this function checks if the given char is equal to this.
 */
bool String::equals(const char *rhs) const {	
	if (!rhs){
		return false;
	}
	if (length != strlen(rhs)){
		return false;
	} else{
		if (strcmp(data , rhs)){
		return false;
		} else{
			return true;	
		}
	}	
}

/**
 * this function takes the data and split it according to the delimeters
 */
void String::split(const char *delimiters, String **output, size_t *size) const 
{	
	int sub_str=0,num_of_delimiters = 0;
	unsigned int  count=1,i=0 ; 
	char copy[length+1] = {0}, *token;
	num_of_delimiters = strlen(delimiters);
	if (data == NULL || size == NULL ){
		if (size != NULL){
			*size=0;
		}
		return;
	}
	strncpy(copy,data,length);
	copy[length] = '\0';
	for ( i = 0; i < length; i++)
		for (int j = 0; j < num_of_delimiters; j++){	
		{
			if (copy[i] == delimiters[j]){
				count++;
			}
		}	
	}
	*size = count;
	if(output != NULL){
		*output = new String[count];
		token=strtok(copy,delimiters);
    	 while (token!=NULL){
			(*output)[sub_str] = String(token);	
			sub_str++;
			token = strtok(NULL,delimiters);
		}
	return;
	}
}

/**
 * this function removes all the back-spaces from the string.
 */
String String::trim() const{
	if(data == NULL){
		return String();
	}
	int num = length;
	int count = 0;
	char str[length+1];
	for(int i = 0; i < num; i++){
		if(data[i] != ' '){
			str[count] = data[i];
			count++;
		}
	}
	str[count] = '\0';
	return String(str);
}



/**
 * this function classifing the data as an ip address or port number 
 * by using the delimiter ".", and making the covertion to integer 
 * in accordance.
 */
int String::to_integer() const{
	String *data_temp;
	size_t size = 0;
	int ret_val = 0;

	split(".", &data_temp, &size);

	if(size == IP_SIZE){
		for(int i = 0; i < IP_SIZE; i++){
			String str;
			str = data_temp[i].trim();
			int byte_i = atoi(str.data);
			if(byte_i > MAX_INT || byte_i < 0){
				delete[] data_temp;
				return 0;
			}
			ret_val |= byte_i << (24-(8*i));
		}
		delete[] data_temp;
		return ret_val;

	} else{
		ret_val = atoi(data);
		delete[] data_temp;
		return ret_val;
	}

	delete[] data_temp;
	return ret_val;
}






