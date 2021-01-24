#include <iostream>
#include <cstring>
#include "ip.h"
#include "port.h"

extern int check_args(int, char**);
extern void parse_input(Field&);

int main(int argc, char** argv){
	if (check_args(argc, argv)) {
		return 1;
	}
	String rule(argv[1]);
	String *full_str;
	size_t size = 0;

	rule.split("=", &full_str, &size);

	if ( (full_str[0].trim().equals(String("src-ip"))) || 
		 (full_str[0].trim().equals(String("dst-ip"))) ) {
		Ip ip_type(full_str[0].trim());     	
		ip_type.set_value(full_str[1].trim());  
		parse_input(ip_type);  
	}
	if( (full_str[0].trim().equals(String("src-port"))) ||
	    (full_str[0].trim().equals(String("dst-port"))) ) {
		Port port_type(full_str[0].trim());
		port_type.set_value(full_str[1].trim());
		parse_input(port_type);
	}
	delete[] full_str;
}
	


